// Copyright Zero Games. All Rights Reserved.

#include "Actor/ZeroPlayerStateBase.h"

#include "ZActorExtensionHelper.h"
#include "Emit/IZSharpFieldRegistry.h"

AZeroPlayerStateBase::AZeroPlayerStateBase()
	: bHasZSharpTick(ZSharp::IZSharpFieldRegistry::Get().IsZSharpClass(FindFunctionChecked(GET_FUNCTION_NAME_CHECKED(ThisClass, ReceiveTick))->GetOuterUClass()))
{
}

void AZeroPlayerStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& outLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(outLifetimeProps);

	ZSharpReplicatedObject_GetLifetimeReplicatedProps(outLifetimeProps);
}

void AZeroPlayerStateBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	
	ZGF::FZActorExtensionHelper::RegisterInitializeComponentsChannel(this);
}

void AZeroPlayerStateBase::BeginPlay()
{
	Super::BeginPlay();

	ZGF::FZActorExtensionHelper::RegisterBeginPlayChannel(this);
}

void AZeroPlayerStateBase::Tick(float deltaSeconds)
{
	if (bHasZSharpTick)
	{
		ReceiveTick(deltaSeconds);

		// No need to process latent actions for native class.
	}
	
	Super::Tick(deltaSeconds);
}

void AZeroPlayerStateBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	ZGF::FZActorExtensionHelper::UnregisterOnEndPlay(this);
	
	Super::EndPlay(endPlayReason);
}


