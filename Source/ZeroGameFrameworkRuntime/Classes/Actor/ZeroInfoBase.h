// Copyright Zero Games. All Rights Reserved.

#pragma once

#include "ZSharpReplicatedObject.h"

#include "ZeroInfoBase.generated.h"

UCLASS(Abstract, Blueprintable)
class ZEROGAMEFRAMEWORKRUNTIME_API AZeroInfoBase : public AInfo, public IZSharpReplicatedObject
{
	GENERATED_BODY()

public:
	AZeroInfoBase();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& outLifetimeProps) const override;

protected:
	virtual void Tick(float deltaSeconds) override;

private:
	bool bHasZSharpTick;
	
};


