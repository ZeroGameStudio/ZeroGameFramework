// Copyright Zero Games. All Rights Reserved.

#include "Actor/ZeroGameStateBase.h"

#include "ZActorExtensionHelper.h"
#include "Emit/IZSharpFieldRegistry.h"

AZeroGameStateBase::AZeroGameStateBase()
	: bHasZSharpTick(ZSharp::IZSharpFieldRegistry::Get().IsZSharpClass(FindFunctionChecked(GET_FUNCTION_NAME_CHECKED(ThisClass, ReceiveTick))->GetOuterUClass()))
{
}

void AZeroGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& outLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(outLifetimeProps);

	ZSharpReplicatedObject_GetLifetimeReplicatedProps(outLifetimeProps);
}

void AZeroGameStateBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	ZGF::FZActorExtensionHelper::RegisterInitializeComponentsChannel(this);
}

void AZeroGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	ZGF::FZActorExtensionHelper::RegisterBeginPlayChannel(this);
}

void AZeroGameStateBase::Tick(float deltaSeconds)
{
	if (bHasZSharpTick)
	{
		ReceiveTick(deltaSeconds);

		// No need to process latent actions for native class.
	}
	
	Super::Tick(deltaSeconds);
}

void AZeroGameStateBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	ZGF::FZActorExtensionHelper::UnregisterOnEndPlay(this);
	
	Super::EndPlay(endPlayReason);
}


