// Copyright Zero Games. All Rights Reserved.

#include "Actor/ZeroGameplayInfoBase.h"

#include "Actor/ZActorExtensionHelper.h"
#include "Emit/IZSharpFieldRegistry.h"

AZeroGameplayInfoBase::AZeroGameplayInfoBase()
	: bHasZSharpTick(ZSharp::IZSharpFieldRegistry::Get().IsZSharpClass(FindFunctionChecked(GET_FUNCTION_NAME_CHECKED(ThisClass, ReceiveTick))->GetOuterUClass()))
{
}

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

void AZeroGameplayInfoBase::Tick(float deltaSeconds)
{
	if (bHasZSharpTick)
	{
		ReceiveTick(deltaSeconds);

		// No need to process latent actions for native class.
	}
	
	Super::Tick(deltaSeconds);
}

void AZeroGameplayInfoBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	if (bExtendable)
	{
		ZGF::FZActorExtensionHelper::UnregisterOnEndPlay(this);
	}
	
	Super::EndPlay(endPlayReason);
}


