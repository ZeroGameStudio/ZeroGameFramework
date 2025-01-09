// Copyright Zero Games. All Rights Reserved.

#pragma once

#include "ZSharpReplicatedObject.h"

#include "ZeroPawnBase.generated.h"

UCLASS(Abstract)
class ZEROGAMEFRAMEWORKRUNTIME_API AZeroPawnBase : public APawn, public IZSharpReplicatedObject
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& outLifetimeProps) const override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void ScriptSetupInputComponent(UEnhancedInputComponent* component);

private:
	virtual void SetupPlayerInputComponent(UInputComponent* playerInputComponent) override;
	
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

	virtual void PossessedBy(AController* newController) override;
	virtual void UnPossessed() override;
	virtual void DetachFromControllerPendingDestroy() override;

private:
	bool bPendingDestroy;
	
};


