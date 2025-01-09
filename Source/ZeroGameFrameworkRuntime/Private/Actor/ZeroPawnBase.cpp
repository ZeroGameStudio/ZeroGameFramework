// Copyright Zero Games. All Rights Reserved.

#include "Actor/ZeroPawnBase.h"

#include "ZActorExtensionHelper.h"
#include "Scope/ZeroExtensionScope.h"

void AZeroPawnBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& outLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(outLifetimeProps);

	ZSharpReplicatedObject_GetLifetimeReplicatedProps(outLifetimeProps);
}

void AZeroPawnBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	ZGF::FZActorExtensionHelper::RegisterInitializeComponentsChannel(this);
}

void AZeroPawnBase::BeginPlay()
{
	Super::BeginPlay();

	ZGF::FZActorExtensionHelper::RegisterBeginPlayChannel(this);
}

void AZeroPawnBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	ZGF::FZActorExtensionHelper::UnregisterOnEndPlay(this);
	
	Super::EndPlay(endPlayReason);
}

void AZeroPawnBase::PossessedBy(AController* newController)
{
	Super::PossessedBy(newController);
	
	if (auto scope = Cast<IZeroExtensionScope>(Controller))
	{
		scope->ZeroExtensionScope_RegisterExtendee(this);
	}
}

void AZeroPawnBase::UnPossessed()
{
	if (!bPendingDestroy)
	{
		if (auto scope = Cast<IZeroExtensionScope>(Controller))
		{
			scope->ZeroExtensionScope_UnregisterExtendee(this, false);
		}
	}
	
	Super::UnPossessed();
}

void AZeroPawnBase::DetachFromControllerPendingDestroy()
{
	bPendingDestroy = true;

	if (auto scope = Cast<IZeroExtensionScope>(Controller))
	{
		scope->ZeroExtensionScope_UnregisterExtendee(this, true);
	}
	
	Super::DetachFromControllerPendingDestroy();
}


