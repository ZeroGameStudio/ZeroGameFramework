// Copyright Zero Games. All Rights Reserved.

#pragma once

#include "ZSharpReplicatedObject.h"
#include "GameFramework/GameStateBase.h"

#include "ZeroGameStateBase.generated.h"

UCLASS(Abstract)
class ZEROGAMEFRAMEWORKRUNTIME_API AZeroGameStateBase : public AGameStateBase, public IZSharpReplicatedObject
{
	GENERATED_BODY()

public:
	AZeroGameStateBase();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& outLifetimeProps) const override;

protected:
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

private:
	bool bHasZSharpTick;
	
};
