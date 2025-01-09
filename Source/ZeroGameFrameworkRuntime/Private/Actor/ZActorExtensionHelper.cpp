// Copyright Zero Games. All Rights Reserved.

#include "ZActorExtensionHelper.h"

#include "GameFramework/GameModeBase.h"
#include "Actor/ZeroClientGameControllerSubsystem.h"
#include "Extension/ZeroGameExtensionChannels.h"
#include "Scope/ZeroExtensionSubsystem.h"

void ZGF::FZActorExtensionHelper::RegisterInitializeComponentsChannel(AActor* extendee)
{
	UWorld* world;
	if (!IsGameActor(extendee, world))
	{
		return;
	}

	RegisterExtendee(extendee, TAG_ExtensionChannel_ActorInitializeComponents, world);
}

void ZGF::FZActorExtensionHelper::RegisterBeginPlayChannel(AActor* extendee)
{
	UWorld* world;
	if (!IsGameActor(extendee, world))
	{
		return;
	}

	RegisterExtendee(extendee, TAG_ExtensionChannel_ActorBeginPlay, world);
}

void ZGF::FZActorExtensionHelper::UnregisterOnEndPlay(AActor* extendee)
{
	UWorld* world;
	if (!IsGameActor(extendee, world))
	{
		return;
	}

	if (auto clientGameControllerScope = world->GetSubsystem<UZeroClientGameControllerSubsystem>())
	{
		clientGameControllerScope->ZeroExtensionScope_UnregisterExtendee(extendee, true, TAG_ExtensionChannel_ActorBeginPlay);
		clientGameControllerScope->ZeroExtensionScope_UnregisterExtendee(extendee, true, TAG_ExtensionChannel_ActorInitializeComponents);
	}
	
	if (auto gameModeScope = Cast<IZeroExtensionScope>(world->GetAuthGameMode()))
	{
		gameModeScope->ZeroExtensionScope_UnregisterExtendee(extendee, true, TAG_ExtensionChannel_ActorBeginPlay);
		gameModeScope->ZeroExtensionScope_UnregisterExtendee(extendee, true, TAG_ExtensionChannel_ActorInitializeComponents);
	}

	UZeroExtensionSubsystem::Get().ZeroExtensionScope_UnregisterExtendee(extendee, true, TAG_ExtensionChannel_ActorBeginPlay);
	UZeroExtensionSubsystem::Get().ZeroExtensionScope_UnregisterExtendee(extendee, true, TAG_ExtensionChannel_ActorInitializeComponents);
}

bool ZGF::FZActorExtensionHelper::IsGameActor(AActor* extendee, UWorld*& world)
{
	if (extendee->IsTemplate())
	{
		return false;
	}
	
	world = extendee->GetWorld();
	if (!world || !world->IsGameWorld())
	{
		return false;
	}

	return true;
}

void ZGF::FZActorExtensionHelper::RegisterExtendee(AActor* extendee, FGameplayTag channel, UWorld* world)
{
	UZeroExtensionSubsystem::Get().ZeroExtensionScope_RegisterExtendee(extendee, channel);

	if (auto gameModeScope = Cast<IZeroExtensionScope>(world->GetAuthGameMode()))
	{
		gameModeScope->ZeroExtensionScope_RegisterExtendee(extendee, channel);
	}

	if (auto clientGameControllerScope = world->GetSubsystem<UZeroClientGameControllerSubsystem>())
	{
		clientGameControllerScope->ZeroExtensionScope_RegisterExtendee(extendee, channel);
	}
}


