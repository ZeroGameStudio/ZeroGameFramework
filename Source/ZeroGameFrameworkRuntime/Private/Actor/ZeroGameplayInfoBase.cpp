// Copyright Zero Games. All Rights Reserved.

#include "Actor/ZeroGameplayInfoBase.h"

#include "Actor/ZActorExtensionHelper.h"

void AZeroGameplayInfoBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& outLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(outLifetimeProps);

	ZSharpReplicatedObject_GetLifetimeReplicatedProps(outLifetimeProps);
}

void AZeroGameplayInfoBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	if (bExtendable)
	{
		ZGF::FZActorExtensionHelper::RegisterInitializeComponentsChannel(this);
	}
}

void AZeroGameplayInfoBase::BeginPlay()
{
	Super::BeginPlay();

	if (bExtendable)
	{
		ZGF::FZActorExtensionHelper::RegisterBeginPlayChannel(this);
	}
}

void AZeroGameplayInfoBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	if (bExtendable)
	{
		ZGF::FZActorExtensionHelper::UnregisterOnEndPlay(this);
	}
	
	Super::EndPlay(endPlayReason);
}


