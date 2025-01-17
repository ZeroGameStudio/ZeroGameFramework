// Copyright Zero Games. All Rights Reserved.

#include "Actor/ZeroExtendablePawnBase.h"

#include "ZActorExtensionHelper.h"

void AZeroExtendablePawnBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	ZGF::FZActorExtensionHelper::RegisterInitializeComponentsChannel(this);
}

void AZeroExtendablePawnBase::BeginPlay()
{
	Super::BeginPlay();

	ZGF::FZActorExtensionHelper::RegisterBeginPlayChannel(this);
}

void AZeroExtendablePawnBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	ZGF::FZActorExtensionHelper::UnregisterOnEndPlay(this);
	
	Super::EndPlay(endPlayReason);
}


