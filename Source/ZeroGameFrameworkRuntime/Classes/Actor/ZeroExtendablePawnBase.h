// Copyright Zero Games. All Rights Reserved.

#pragma once

#include "ZeroPawnBase.h"

#include "ZeroExtendablePawnBase.generated.h"

UCLASS(Abstract)
class ZEROGAMEFRAMEWORKRUNTIME_API AZeroExtendablePawnBase : public AZeroPawnBase
{
	GENERATED_BODY()

protected:
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
	
};


