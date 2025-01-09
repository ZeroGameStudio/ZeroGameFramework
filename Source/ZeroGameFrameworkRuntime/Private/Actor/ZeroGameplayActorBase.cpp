// Copyright Zero Games. All Rights Reserved.

#include "Actor/ZeroGameplayActorBase.h"

#include "Actor/ZActorExtensionHelper.h"

void AZeroGameplayActorBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& outLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(outLifetimeProps);

	ZSharpReplicatedObject_GetLifetimeReplicatedProps(outLifetimeProps);
}

void AZeroGameplayActorBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	if (bExtendable)
	{
		ZGF::FZActorExtensionHelper::RegisterInitializeComponentsChannel(this);
	}
}

void AZeroGameplayActorBase::BeginPlay()
{
	Super::BeginPlay();

	if (bExtendable)
	{
		ZGF::FZActorExtensionHelper::RegisterBeginPlayChannel(this);
	}
}

void AZeroGameplayActorBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	if (bExtendable)
	{
		ZGF::FZActorExtensionHelper::UnregisterOnEndPlay(this);
	}
	
	Super::EndPlay(endPlayReason);
}


