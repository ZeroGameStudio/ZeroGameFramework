// Copyright Zero Games. All Rights Reserved.

#pragma once

#include "ZSharpReplicatedObject.h"

#include "ZeroGameplayComponentBase.generated.h"

UCLASS(Abstract, Blueprintable)
class ZEROGAMEFRAMEWORKRUNTIME_API UZeroGameplayComponentBase : public UActorComponent, public IZSharpReplicatedObject
{
	GENERATED_BODY()

public:
	UZeroGameplayComponentBase();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& outLifetimeProps) const override;

public:
	UFUNCTION(BlueprintPure, Category = "Replication")
	ENetRole GetLocalRole() const;

	UFUNCTION(BlueprintPure, Category = "Replication")
	ENetRole GetRemoteRole() const;

	UFUNCTION(BlueprintPure, Category = "Replication")
	bool HasAuthority() const;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

private:
	bool bIsZSharpClass;
	bool bHasZSharpTick;
	
};


