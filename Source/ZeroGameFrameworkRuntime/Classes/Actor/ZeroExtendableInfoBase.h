// Copyright Zero Games. All Rights Reserved.

#pragma once

#include "ZeroInfoBase.h"

#include "ZeroExtendableInfoBase.generated.h"

UCLASS(Abstract)
class ZEROGAMEFRAMEWORKRUNTIME_API AZeroExtendableInfoBase : public AZeroInfoBase
{
	GENERATED_BODY()

protected:
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
	
};


