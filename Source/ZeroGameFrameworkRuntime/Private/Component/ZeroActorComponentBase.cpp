// Copyright Zero Games. All Rights Reserved.

#include "Component/ZeroActorComponentBase.h"

#include "Emit/IZSharpFieldRegistry.h"

UZeroActorComponentBase::UZeroActorComponentBase()
	: bIsZSharpClass(ZSharp::IZSharpFieldRegistry::Get().IsZSharpClass(GetClass()))
	, bHasZSharpTick(ZSharp::IZSharpFieldRegistry::Get().IsZSharpClass(FindFunctionChecked(GET_FUNCTION_NAME_CHECKED(ThisClass, ReceiveTick))->GetOuterUClass()))
{
	bWantsInitializeComponent = true;
}

void UZeroActorComponentBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& outLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(outLifetimeProps);

	ZSharpReplicatedObject_GetLifetimeReplicatedProps(outLifetimeProps);
}

ENetRole UZeroActorComponentBase::GetLocalRole() const
{
	const AActor* owner = GetOwner();
	return owner ? owner->GetLocalRole() : ROLE_None;
}

ENetRole UZeroActorComponentBase::GetRemoteRole() const
{
	const AActor* owner = GetOwner();
	return owner ? owner->GetRemoteRole() : ROLE_None;
}

bool UZeroActorComponentBase::HasAuthority() const
{
	const AActor* owner = GetOwner();
	return owner && owner->HasAuthority();
}

void UZeroActorComponentBase::InitializeComponent()
{
	Super::InitializeComponent();

	ReceiveInitialize();
}

void UZeroActorComponentBase::UninitializeComponent()
{
	ReceiveUninitialize();
	
	Super::UninitializeComponent();
}

void UZeroActorComponentBase::OnRegister()
{
	Super::OnRegister();

	ReceiveRegister();
}

void UZeroActorComponentBase::OnUnregister()
{
	ReceiveUnregister();
	
	Super::OnUnregister();
}

void UZeroActorComponentBase::BeginPlay()
{
	if (bIsZSharpClass)
	{
		ReceiveBeginPlay();
	}
	
	Super::BeginPlay();
}

void UZeroActorComponentBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	if (!HasAnyFlags(RF_BeginDestroyed) && !IsUnreachable() && bIsZSharpClass)
	{
		ReceiveEndPlay(endPlayReason);
	}
	
	Super::EndPlay(endPlayReason);
}

void UZeroActorComponentBase::Activate(bool reset)
{
	// We want to call ReceiveActivate() between SetActiveFlag() and OnComponentActivated so we directly rewrite this function.
	if (reset || ShouldActivate())
	{
		SetComponentTickEnabled(true);
		SetActiveFlag(true);

		ReceiveActivate();

		OnComponentActivated.Broadcast(this, reset);
	}
}

void UZeroActorComponentBase::Deactivate()
{
	// We want to call ReceiveDeactivate() between SetActiveFlag() and OnComponentDeactivated so we directly rewrite this function.
	if (ShouldActivate())
	{
		SetComponentTickEnabled(false);
		SetActiveFlag(false);

		ReceiveDeactivate();

		OnComponentDeactivated.Broadcast(this);
	}
}

void UZeroActorComponentBase::TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction)
{
	if (bIsZSharpClass && bHasZSharpTick)
	{
		ReceiveTick(deltaTime);

		// No need to process latent actions for native class.
	}
	
	Super::TickComponent(deltaTime, tickType, thisTickFunction);
}


