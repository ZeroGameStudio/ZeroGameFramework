// Copyright Zero Games. All Rights Reserved.

#include "Actor/ZeroPawnBase.h"

#include "EnhancedInputComponent.h"
#include "ZActorExtensionHelper.h"
#include "Emit/IZSharpFieldRegistry.h"
#include "Scope/ZExtensionScope.h"
#include "Scope/ZPlayerExtensionScope.h"

AZeroPawnBase::AZeroPawnBase()
	: bHasZSharpTick(ZSharp::IZSharpFieldRegistry::Get().IsZSharpClass(FindFunctionChecked(GET_FUNCTION_NAME_CHECKED(ThisClass, ReceiveTick))->GetOuterUClass()))
	, bPendingDestroy(false)
{
}

void AZeroPawnBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& outLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(outLifetimeProps);

	ZSharpReplicatedObject_GetLifetimeReplicatedProps(outLifetimeProps);
}

void AZeroPawnBase::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);

	if (auto component = CastChecked<UEnhancedInputComponent>(playerInputComponent))
	{
		ScriptSetupInputComponent(component);
	}
}

void AZeroPawnBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	ZGF::FZActorExtensionHelper::RegisterInitializeComponentsChannel(this);
}

void AZeroPawnBase::BeginPlay()
{
	Super::BeginPlay();

	ZGF::FZActorExtensionHelper::RegisterBeginPlayChannel(this);
}

void AZeroPawnBase::Tick(float deltaSeconds)
{
	if (bHasZSharpTick)
	{
		ReceiveTick(deltaSeconds);

		// No need to process latent actions for native class.
	}
	
	Super::Tick(deltaSeconds);
}

void AZeroPawnBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	ZGF::FZActorExtensionHelper::UnregisterOnEndPlay(this);
	
	Super::EndPlay(endPlayReason);
}

void AZeroPawnBase::PossessedBy(AController* newController)
{
	Super::PossessedBy(newController);

	if (auto pc = Cast<APlayerController>(newController))
	{
		if (ULocalPlayer* player = pc->GetLocalPlayer())
		{
			if (auto playerScope = player->GetSubsystem<UZPlayerExtensionScope>())
			{
				playerScope->ExtensionScope_RegisterExtendee(this);
			}
		}
	}
	
	if (auto controllerScope = Cast<IZExtensionScope>(newController))
	{
		controllerScope->ExtensionScope_RegisterExtendee(this);
	}
}

void AZeroPawnBase::UnPossessed()
{
	if (!bPendingDestroy)
	{
		// IMPORTANT: This must be done before we call super because we need pointer to old controller.
		UnregisterExtendeeFromController(false);
	}

	Super::UnPossessed();
}

void AZeroPawnBase::DetachFromControllerPendingDestroy()
{
	if (!bPendingDestroy)
	{
		bPendingDestroy = true;

		// IMPORTANT: This must be done before we call super because we need pointer to old controller.
		UnregisterExtendeeFromController(true);
	}
	
	Super::DetachFromControllerPendingDestroy();
}

void AZeroPawnBase::UnregisterExtendeeFromController(bool destroying)
{
	if (auto controllerScope = Cast<IZExtensionScope>(Controller))
	{
		controllerScope->ExtensionScope_UnregisterExtendee(this, destroying);
	}
	
	if (auto pc = Cast<APlayerController>(Controller))
	{
		if (ULocalPlayer* player = pc->GetLocalPlayer())
		{
			if (auto playerScope = player->GetSubsystem<UZPlayerExtensionScope>())
			{
				playerScope->ExtensionScope_UnregisterExtendee(this, destroying);
			}
		}
	}
}


