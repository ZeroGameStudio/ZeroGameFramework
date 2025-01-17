// Copyright Zero Games. All Rights Reserved.

#pragma once

#include "ZSharpReplicatedObject.h"

#include "ZeroActorBase.generated.h"

UCLASS(Abstract)
class ZEROGAMEFRAMEWORKRUNTIME_API AZeroActorBase : public AActor, public IZSharpReplicatedObject
{
	GENERATED_BODY()

public:
	AZeroActorBase();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& outLifetimeProps) const override;

protected:
	virtual void Tick(float deltaSeconds) override;

private:
	bool bHasZSharpTick;
	
};


