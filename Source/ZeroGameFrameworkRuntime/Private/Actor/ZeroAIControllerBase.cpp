// Copyright Zero Games. All Rights Reserved.

#include "Actor/ZeroAIControllerBase.h"

#include "ZActorExtensionHelper.h"
#include "Emit/IZSharpFieldRegistry.h"

AZeroAIControllerBase::AZeroAIControllerBase()
	: bHasZSharpTick(ZSharp::IZSharpFieldRegistry::Get().IsZSharpClass(FindFunctionChecked(GET_FUNCTION_NAME_CHECKED(ThisClass, ReceiveTick))->GetOuterUClass()))
{
}

void AZeroAIControllerBase::ExtensionScope_RegisterExtender(UZExtenderBaseInterface* extender)
{
	ExtensionScope.RegisterExtender(extender);
}

void AZeroAIControllerBase::ExtensionScope_UnregisterExtender(UZExtenderBaseInterface* extender)
{
	ExtensionScope.UnregisterExtender(extender);
}

void AZeroAIControllerBase::ExtensionScope_RegisterExtendee(UObject* extendee, FGameplayTag channel)
{
	ExtensionScope.RegisterExtendee(extendee, channel);
}

void AZeroAIControllerBase::ExtensionScope_UnregisterExtendee(UObject* extendee, bool destroying, FGameplayTag channel)
{
	ExtensionScope.UnregisterExtendee(extendee, destroying, channel);
}

void AZeroAIControllerBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	ZGF::FZActorExtensionHelper::RegisterInitializeComponentsChannel(this);
}

void AZeroAIControllerBase::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	if (world && world->IsGameWorld())
	{
		FString name = "ZeroAIControllerExtensionScope - ";
		name.Append(GetName());
		ExtensionScope.Open(Create(this, FName { name }));
	}

	ZGF::FZActorExtensionHelper::RegisterBeginPlayChannel(this);
}

void AZeroAIControllerBase::Tick(float deltaSeconds)
{
	if (bHasZSharpTick)
	{
		ReceiveTick(deltaSeconds);

		// No need to process latent actions for native class.
	}
	
	Super::Tick(deltaSeconds);
}

void AZeroAIControllerBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	ZGF::FZActorExtensionHelper::UnregisterOnEndPlay(this);
	
	ExtensionScope.Close();
	
	Super::EndPlay(endPlayReason);
}


