// Copyright Zero Games. All Rights Reserved.

#include "Component/ZeroGameplayComponentBase.h"

#include "Emit/IZSharpFieldRegistry.h"

UZeroGameplayComponentBase::UZeroGameplayComponentBase()
	: bIsZSharpClass(ZSharp::IZSharpFieldRegistry::Get().IsZSharpClass(GetClass()))
	, bHasZSharpTick(ZSharp::IZSharpFieldRegistry::Get().IsZSharpClass(FindFunctionChecked(GET_FUNCTION_NAME_CHECKED(ThisClass, ReceiveTick))->GetOuterUClass()))
{

}

void UZeroGameplayComponentBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& outLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(outLifetimeProps);

	ZSharpReplicatedObject_GetLifetimeReplicatedProps(outLifetimeProps);
}

ENetRole UZeroGameplayComponentBase::GetLocalRole() const
{
	const AActor* owner = GetOwner();
	return owner ? owner->GetLocalRole() : ROLE_None;
}

ENetRole UZeroGameplayComponentBase::GetRemoteRole() const
{
	const AActor* owner = GetOwner();
	return owner ? owner->GetRemoteRole() : ROLE_None;
}

bool UZeroGameplayComponentBase::HasAuthority() const
{
	const AActor* owner = GetOwner();
	return owner && owner->HasAuthority();
}

void UZeroGameplayComponentBase::BeginPlay()
{
	if (bIsZSharpClass)
	{
		ReceiveBeginPlay();
	}
	
	Super::BeginPlay();
}

void UZeroGameplayComponentBase::TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction)
{
	if (bIsZSharpClass && bHasZSharpTick)
	{
		ReceiveTick(deltaTime);

		// No need to process latent actions for native class.
	}
	
	Super::TickComponent(deltaTime, tickType, thisTickFunction);
}

void UZeroGameplayComponentBase::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	if (!HasAnyFlags(RF_BeginDestroyed) && !IsUnreachable() && bIsZSharpClass)
	{
		ReceiveEndPlay(endPlayReason);
	}
	
	Super::EndPlay(endPlayReason);
}


