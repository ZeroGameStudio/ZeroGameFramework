// Copyright Zero Games. All Rights Reserved.

#include "Actor/ZeroGameplayActorBase.h"

#include "Actor/ZActorExtensionHelper.h"
#include "Emit/IZSharpFieldRegistry.h"

AZeroGameplayActorBase::AZeroGameplayActorBase()
	: bHasZSharpTick(ZSharp::IZSharpFieldRegistry::Get().IsZSharpClass(FindFunctionChecked(GET_FUNCTION_NAME_CHECKED(ThisClass, ReceiveTick))->GetOuterUClass()))
{
}

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

void AZeroGameplayActorBase::Tick(float deltaSeconds)
{
	if (bHasZSharpTick)
	{
		ReceiveTick(deltaSeconds);

		// No need to process latent actions for native class.
	}
	
	Super::Tick(deltaSeconds);
}

void AZeroGameplayActorBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	if (bExtendable)
	{
		ZGF::FZActorExtensionHelper::UnregisterOnEndPlay(this);
	}
	
	Super::EndPlay(endPlayReason);
}


