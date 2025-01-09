﻿// Copyright Zero Games. All Rights Reserved.

#include "Actor/ZeroPlayerControllerBase.h"

#include "ZActorExtensionHelper.h"

void AZeroPlayerControllerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& outLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(outLifetimeProps);

	ZSharpReplicatedObject_GetLifetimeReplicatedProps(outLifetimeProps);
}

void AZeroPlayerControllerBase::ZeroExtensionScope_RegisterExtender(UZeroExtenderBase* extender, FGameplayTag channel)
{
	ExtensionScope.RegisterExtender(extender, channel);
}

void AZeroPlayerControllerBase::ZeroExtensionScope_UnregisterExtender(UZeroExtenderBase* extender, FGameplayTag channel)
{
	ExtensionScope.UnregisterExtender(extender, channel);
}

void AZeroPlayerControllerBase::ZeroExtensionScope_RegisterExtendee(UObject* extendee, FGameplayTag channel)
{
	ExtensionScope.RegisterExtendee(extendee, channel);
}

void AZeroPlayerControllerBase::ZeroExtensionScope_UnregisterExtendee(UObject* extendee, bool destroying, FGameplayTag channel)
{
	ExtensionScope.UnregisterExtendee(extendee, destroying, channel);
}

void AZeroPlayerControllerBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	ZGF::FZActorExtensionHelper::RegisterInitializeComponentsChannel(this);
}

void AZeroPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	if (world && world->IsGameWorld())
	{
		FString name = "ZeroPlayerControllerExtensionScope - ";
		name.Append(GetName());
		ExtensionScope.Open(Create(this, FName { name }));
	}

	ZGF::FZActorExtensionHelper::RegisterBeginPlayChannel(this);
}

void AZeroPlayerControllerBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	ZGF::FZActorExtensionHelper::UnregisterOnEndPlay(this);
	
	ExtensionScope.Close();
	
	Super::EndPlay(endPlayReason);
}


