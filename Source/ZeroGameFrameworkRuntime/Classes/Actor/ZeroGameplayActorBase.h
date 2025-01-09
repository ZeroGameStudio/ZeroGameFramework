// Copyright Zero Games. All Rights Reserved.

#pragma once

#include "ZSharpReplicatedObject.h"

#include "ZeroGameplayActorBase.generated.h"

UCLASS(Abstract)
class ZEROGAMEFRAMEWORKRUNTIME_API AZeroGameplayActorBase : public AActor, public IZSharpReplicatedObject
{
	GENERATED_BODY()

public:
	AZeroGameplayActorBase();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& outLifetimeProps) const override;

protected:
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Extension")
	bool bExtendable;

private:
	bool bHasZSharpTick;
	
};


