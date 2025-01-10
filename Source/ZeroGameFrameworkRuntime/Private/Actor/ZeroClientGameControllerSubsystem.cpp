// Copyright Zero Games. All Rights Reserved.

#include "Actor/ZeroClientGameControllerSubsystem.h"

#include "ZeroGameFrameworkRuntimeLogChannels.h"
#include "Actor/ZeroClientGameControllerBase.h"

ZGF::ZeroClientGameControllerSubsystem_Private::FZSetController::FZSetController(AZeroClientGameControllerBase* controller)
{
	UWorld* world = controller->GetWorld();
	if (!world)
	{
		return;
	}

	auto subsystem = world->GetSubsystem<UZeroClientGameControllerSubsystem>();
	if (!subsystem)
	{
		return;
	}

	subsystem->SetController(controller);
}

void UZeroClientGameControllerSubsystem::ExtensionScope_RegisterExtender(UZExtenderBaseInterface* extender, FGameplayTag channel)
{
	ExtensionScope.RegisterExtender(extender, channel);
}

void UZeroClientGameControllerSubsystem::ExtensionScope_UnregisterExtender(UZExtenderBaseInterface* extender, FGameplayTag channel)
{
	ExtensionScope.UnregisterExtender(extender, channel);
}

void UZeroClientGameControllerSubsystem::ExtensionScope_RegisterExtendee(UObject* extendee, FGameplayTag channel)
{
	ExtensionScope.RegisterExtendee(extendee, channel);
}

void UZeroClientGameControllerSubsystem::ExtensionScope_UnregisterExtendee(UObject* extendee, bool destroying, FGameplayTag channel)
{
	ExtensionScope.UnregisterExtendee(extendee, destroying, channel);
}

bool UZeroClientGameControllerSubsystem::ShouldCreateSubsystem(UObject* outer) const
{
	if (IsRunningDedicatedServer())
	{
		return false;
	}

	auto world = CastChecked<UWorld>(outer);
	return world->IsGameWorld();
}

void UZeroClientGameControllerSubsystem::Initialize(FSubsystemCollectionBase& collection)
{
	Super::Initialize(collection);
}

void UZeroClientGameControllerSubsystem::Deinitialize()
{
	ExtensionScope.Close();
	
	Super::Deinitialize();
}

void UZeroClientGameControllerSubsystem::SetController(AZeroClientGameControllerBase* controller)
{
	if (!ensure(!Controller))
	{
		UE_LOG(LogZeroGameFrameworkRuntime, Error, TEXT("[UZeroClientGameControllerSubsystem::SetController] Duplicated ClientGameController instance!"));
		return;
	}
	
	Controller = controller;
	ExtensionScope.Open(Controller.Get());
}


