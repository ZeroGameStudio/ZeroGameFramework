// Copyright Zero Games. All Rights Reserved.

#pragma once

#include "ZSharpReplicatedObject.h"
#include "GameFramework/PlayerState.h"

#include "ZeroPlayerStateBase.generated.h"

UCLASS(Abstract)
class ZEROGAMEFRAMEWORKRUNTIME_API AZeroPlayerStateBase : public APlayerState, public IZSharpReplicatedObject
{
	GENERATED_BODY()

public:
	AZeroPlayerStateBase();

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


