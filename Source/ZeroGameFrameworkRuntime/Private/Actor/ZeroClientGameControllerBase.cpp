// Copyright Zero Games. All Rights Reserved.

#include "Actor/ZeroClientGameControllerBase.h"

#include "ZActorExtensionHelper.h"
#include "Actor/ZeroClientGameControllerSubsystem.h"

void AZeroClientGameControllerBase::ZeroExtensionScope_RegisterExtender(UZeroExtenderBase* extender, FGameplayTag channel)
{
	ExtensionScope.RegisterExtender(extender, channel);
}

void AZeroClientGameControllerBase::ZeroExtensionScope_UnregisterExtender(UZeroExtenderBase* extender, FGameplayTag channel)
{
	ExtensionScope.UnregisterExtender(extender, channel);
}

void AZeroClientGameControllerBase::ZeroExtensionScope_RegisterExtendee(UObject* extendee, FGameplayTag channel)
{
	ExtensionScope.RegisterExtendee(extendee, channel);
}

void AZeroClientGameControllerBase::ZeroExtensionScope_UnregisterExtendee(UObject* extendee, bool destroying, FGameplayTag channel)
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

void AZeroClientGameControllerBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	ZGF::FZActorExtensionHelper::UnregisterOnEndPlay(this);

	ExtensionScope.Close();
	
	Super::EndPlay(endPlayReason);
}
