// Copyright Zero Games. All Rights Reserved.

#pragma once

#include "ZeroActorBase.h"

#include "ZeroExtendableActorBase.generated.h"

UCLASS(Abstract)
class ZEROGAMEFRAMEWORKRUNTIME_API AZeroExtendableActorBase : public AZeroActorBase
{
	GENERATED_BODY()

protected:
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
	
};


