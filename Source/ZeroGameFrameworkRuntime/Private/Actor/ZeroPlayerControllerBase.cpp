// Copyright Zero Games. All Rights Reserved.

#include "Actor/ZeroPlayerControllerBase.h"

#include "EnhancedInputComponent.h"
#include "ZActorExtensionHelper.h"
#include "Emit/IZSharpFieldRegistry.h"

AZeroPlayerControllerBase::AZeroPlayerControllerBase()
	: bHasZSharpTick(ZSharp::IZSharpFieldRegistry::Get().IsZSharpClass(FindFunctionChecked(GET_FUNCTION_NAME_CHECKED(ThisClass, ReceiveTick))->GetOuterUClass()))
{
}

void AZeroPlayerControllerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& outLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(outLifetimeProps);

	ZSharpReplicatedObject_GetLifetimeReplicatedProps(outLifetimeProps);
}

void AZeroPlayerControllerBase::ExtensionScope_RegisterExtender(UZExtenderBase* extender, FGameplayTag channel)
{
	ExtensionScope.RegisterExtender(extender, channel);
}

void AZeroPlayerControllerBase::ExtensionScope_UnregisterExtender(UZExtenderBase* extender, FGameplayTag channel)
{
	ExtensionScope.UnregisterExtender(extender, channel);
}

void AZeroPlayerControllerBase::ExtensionScope_RegisterExtendee(UObject* extendee, FGameplayTag channel)
{
	ExtensionScope.RegisterExtendee(extendee, channel);
}

void AZeroPlayerControllerBase::ExtensionScope_UnregisterExtendee(UObject* extendee, bool destroying, FGameplayTag channel)
{
	ExtensionScope.UnregisterExtendee(extendee, destroying, channel);
}

void AZeroPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (auto component = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		ScriptSetupInputComponent(component);
	}
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

void AZeroPlayerControllerBase::Tick(float deltaSeconds)
{
	if (bHasZSharpTick)
	{
		ReceiveTick(deltaSeconds);

		// No need to process latent actions for native class.
	}
	
	Super::Tick(deltaSeconds);
}

void AZeroPlayerControllerBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	ZGF::FZActorExtensionHelper::UnregisterOnEndPlay(this);
	
	ExtensionScope.Close();
	
	Super::EndPlay(endPlayReason);
}


