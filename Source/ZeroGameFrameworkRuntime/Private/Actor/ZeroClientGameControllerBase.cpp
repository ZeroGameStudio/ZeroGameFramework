// Copyright Zero Games. All Rights Reserved.

#include "Actor/ZeroClientGameControllerBase.h"

#include "ZActorExtensionHelper.h"
#include "Actor/ZeroClientGameControllerSubsystem.h"
#include "Emit/IZSharpFieldRegistry.h"

AZeroClientGameControllerBase::AZeroClientGameControllerBase()
	: bHasZSharpTick(ZSharp::IZSharpFieldRegistry::Get().IsZSharpClass(FindFunctionChecked(GET_FUNCTION_NAME_CHECKED(ThisClass, ReceiveTick))->GetOuterUClass()))
{
}

void AZeroClientGameControllerBase::ExtensionScope_RegisterExtender(UZExtenderBaseInterface* extender)
{
	ExtensionScope.RegisterExtender(extender);
}

void AZeroClientGameControllerBase::ExtensionScope_UnregisterExtender(UZExtenderBaseInterface* extender)
{
	ExtensionScope.UnregisterExtender(extender);
}

void AZeroClientGameControllerBase::ExtensionScope_RegisterExtendee(UObject* extendee, FGameplayTag channel)
{
	ExtensionScope.RegisterExtendee(extendee, channel);
}

void AZeroClientGameControllerBase::ExtensionScope_UnregisterExtendee(UObject* extendee, bool destroying, FGameplayTag channel)
{
	ExtensionScope.UnregisterExtendee(extendee, destroying, channel);
}

void AZeroClientGameControllerBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	
	ZGF::FZActorExtensionHelper::RegisterInitializeComponentsChannel(this);
}

void AZeroClientGameControllerBase::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	if (world && world->IsGameWorld())
	{
		ExtensionScope.Open(Create(this, "ZeroClientGameControllerExtensionScope"));
		ZGF::ZeroClientGameControllerSubsystem_Private::FZSetController { this };
	}

	ZGF::FZActorExtensionHelper::RegisterBeginPlayChannel(this);
}

void AZeroClientGameControllerBase::Tick(float deltaSeconds)
{
	if (bHasZSharpTick)
	{
		ReceiveTick(deltaSeconds);

		// No need to process latent actions for native class.
	}
	
	Super::Tick(deltaSeconds);
}

void AZeroClientGameControllerBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	ZGF::FZActorExtensionHelper::UnregisterOnEndPlay(this);

	ExtensionScope.Close();
	
	Super::EndPlay(endPlayReason);
}
