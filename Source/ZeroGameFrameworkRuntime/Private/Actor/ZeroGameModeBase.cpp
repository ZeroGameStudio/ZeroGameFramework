// Copyright Zero Games. All Rights Reserved.

#include "Actor/ZeroGameModeBase.h"

#include "ZActorExtensionHelper.h"
#include "Actor/ZeroClientGameController.h"
#include "Emit/IZSharpFieldRegistry.h"

AZeroGameModeBase::AZeroGameModeBase()
	: ClientGameControllerClass(AZeroClientGameController::StaticClass())
	, bHasZSharpTick(ZSharp::IZSharpFieldRegistry::Get().IsZSharpClass(FindFunctionChecked(GET_FUNCTION_NAME_CHECKED(ThisClass, ReceiveTick))->GetOuterUClass()))
{

}

void AZeroGameModeBase::ExtensionScope_RegisterExtender(UZExtenderBase* extender, FGameplayTag channel)
{
	ExtensionScope.RegisterExtender(extender, channel);
}

void AZeroGameModeBase::ExtensionScope_UnregisterExtender(UZExtenderBase* extender, FGameplayTag channel)
{
	ExtensionScope.UnregisterExtender(extender, channel);
}

void AZeroGameModeBase::ExtensionScope_RegisterExtendee(UObject* extendee, FGameplayTag channel)
{
	ExtensionScope.RegisterExtendee(extendee, channel);
}

void AZeroGameModeBase::ExtensionScope_UnregisterExtendee(UObject* extendee, bool destroying, FGameplayTag channel)
{
	ExtensionScope.UnregisterExtendee(extendee, destroying, channel);
}

void AZeroGameModeBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	ZGF::FZActorExtensionHelper::RegisterInitializeComponentsChannel(this);
}

void AZeroGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	if (world && world->IsGameWorld())
	{
		ExtensionScope.Open(Create(this, "ZeroGameModeExtensionScope"));
	}

	ZGF::FZActorExtensionHelper::RegisterBeginPlayChannel(this);
}

void AZeroGameModeBase::Tick(float deltaSeconds)
{
	if (bHasZSharpTick)
	{
		ReceiveTick(deltaSeconds);

		// No need to process latent actions for native class.
	}
	
	Super::Tick(deltaSeconds);
}

void AZeroGameModeBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	ZGF::FZActorExtensionHelper::UnregisterOnEndPlay(this);

	ExtensionScope.Close();
	
	Super::EndPlay(endPlayReason);
}


