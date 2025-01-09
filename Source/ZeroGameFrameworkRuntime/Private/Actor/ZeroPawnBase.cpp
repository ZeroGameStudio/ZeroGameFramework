// Copyright Zero Games. All Rights Reserved.

#include "Actor/ZeroPawnBase.h"

#include "EnhancedInputComponent.h"
#include "ZActorExtensionHelper.h"
#include "Emit/IZSharpFieldRegistry.h"
#include "Scope/ZeroExtensionScope.h"

AZeroPawnBase::AZeroPawnBase()
	: bHasZSharpTick(ZSharp::IZSharpFieldRegistry::Get().IsZSharpClass(FindFunctionChecked(GET_FUNCTION_NAME_CHECKED(ThisClass, ReceiveTick))->GetOuterUClass()))
{
}

void AZeroPawnBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& outLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(outLifetimeProps);

	ZSharpReplicatedObject_GetLifetimeReplicatedProps(outLifetimeProps);
}

void AZeroPawnBase::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);

	if (auto component = CastChecked<UEnhancedInputComponent>(playerInputComponent))
	{
		ScriptSetupInputComponent(component);
	}
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

void AZeroPawnBase::Tick(float deltaSeconds)
{
	if (bHasZSharpTick)
	{
		ReceiveTick(deltaSeconds);

		// No need to process latent actions for native class.
	}
	
	Super::Tick(deltaSeconds);
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


