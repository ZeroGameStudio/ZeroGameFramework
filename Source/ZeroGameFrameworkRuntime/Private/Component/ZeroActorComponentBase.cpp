// Copyright Zero Games. All Rights Reserved.

#include "Component/ZeroActorComponentBase.h"

#include "Emit/IZSharpFieldRegistry.h"

UZeroActorComponentBase::UZeroActorComponentBase()
	: bIsZSharpClass(ZSharp::IZSharpFieldRegistry::Get().IsZSharpClass(GetClass()))
	, bHasZSharpTick(ZSharp::IZSharpFieldRegistry::Get().IsZSharpClass(FindFunctionChecked(GET_FUNCTION_NAME_CHECKED(ThisClass, ReceiveTick))->GetOuterUClass()))
{

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

void UZeroActorComponentBase::BeginPlay()
{
	if (bIsZSharpClass)
	{
		ReceiveBeginPlay();
	}
	
	Super::BeginPlay();
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

void UZeroActorComponentBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	if (!HasAnyFlags(RF_BeginDestroyed) && !IsUnreachable() && bIsZSharpClass)
	{
		ReceiveEndPlay(endPlayReason);
	}
	
	Super::EndPlay(endPlayReason);
}


