// Copyright Zero Games. All Rights Reserved.

#pragma once

#include "AIController.h"
#include "Scope/ZeroExtensionScope.h"
#include "Scope/ZDeferredExtensionScope.h"

#include "ZeroAIControllerBase.generated.h"

UCLASS(Abstract)
class ZEROGAMEFRAMEWORKRUNTIME_API AZeroAIControllerBase : public AAIController, public IZeroExtensionScope
{
	GENERATED_BODY()

public:
	AZeroAIControllerBase();

public:
	virtual void ZeroExtensionScope_RegisterExtender(UZeroExtenderBase* extender, FGameplayTag channel = FGameplayTag::EmptyTag) override;
	virtual void ZeroExtensionScope_UnregisterExtender(UZeroExtenderBase* extender, FGameplayTag channel = FGameplayTag::EmptyTag) override;
	
	virtual void ZeroExtensionScope_RegisterExtendee(UObject* extendee, FGameplayTag channel = FGameplayTag::EmptyTag) override;
	virtual void ZeroExtensionScope_UnregisterExtendee(UObject* extendee, bool destroying, FGameplayTag channel = FGameplayTag::EmptyTag) override;

protected:
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

private:
	bool bHasZSharpTick;
	
	ZES::FZDeferredExtensionScope ExtensionScope;
	
};


