// Copyright Zero Games. All Rights Reserved.

#include "ZActorExtensionHelper.h"

#include "GameFramework/GameModeBase.h"
#include "Actor/ZeroClientGameControllerSubsystem.h"
#include "Extension/ZeroGameFrameworkExtensionChannels.h"
#include "Scope/ZEngineExtensionScope.h"
#include "Scope/ZGameExtensionScope.h"
#include "Scope/ZWorldExtensionScope.h"

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
		clientGameControllerScope->ExtensionScope_UnregisterExtendee(extendee, true, TAG_ExtensionChannel_ActorBeginPlay);
		clientGameControllerScope->ExtensionScope_UnregisterExtendee(extendee, true, TAG_ExtensionChannel_ActorInitializeComponents);
	}
	
	if (auto gameModeScope = Cast<IZExtensionScope>(world->GetAuthGameMode()))
	{
		gameModeScope->ExtensionScope_UnregisterExtendee(extendee, true, TAG_ExtensionChannel_ActorBeginPlay);
		gameModeScope->ExtensionScope_UnregisterExtendee(extendee, true, TAG_ExtensionChannel_ActorInitializeComponents);
	}

	if (auto worldScope = world->GetSubsystem<UZWorldExtensionScope>())
	{
		worldScope->ExtensionScope_UnregisterExtendee(extendee, true, TAG_ExtensionChannel_ActorBeginPlay);
		worldScope->ExtensionScope_UnregisterExtendee(extendee, true, TAG_ExtensionChannel_ActorInitializeComponents);
	}

	UZGameExtensionScope::Get(world->GetGameInstance()).ExtensionScope_UnregisterExtendee(extendee, true, TAG_ExtensionChannel_ActorBeginPlay);
	UZGameExtensionScope::Get(world->GetGameInstance()).ExtensionScope_UnregisterExtendee(extendee, true, TAG_ExtensionChannel_ActorInitializeComponents);

	UZEngineExtensionScope::Get().ExtensionScope_UnregisterExtendee(extendee, true, TAG_ExtensionChannel_ActorBeginPlay);
	UZEngineExtensionScope::Get().ExtensionScope_UnregisterExtendee(extendee, true, TAG_ExtensionChannel_ActorInitializeComponents);
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
	UZEngineExtensionScope::Get().ExtensionScope_RegisterExtendee(extendee, channel);
	UZGameExtensionScope::Get(world->GetGameInstance()).ExtensionScope_RegisterExtendee(extendee, channel);

	if (auto worldScope = world->GetSubsystem<UZWorldExtensionScope>())
	{
		worldScope->ExtensionScope_RegisterExtendee(extendee, channel);
	}
	
	if (auto gameModeScope = Cast<IZExtensionScope>(world->GetAuthGameMode()))
	{
		gameModeScope->ExtensionScope_RegisterExtendee(extendee, channel);
	}

	if (auto clientGameControllerScope = world->GetSubsystem<UZeroClientGameControllerSubsystem>())
	{
		clientGameControllerScope->ExtensionScope_RegisterExtendee(extendee, channel);
	}
}


