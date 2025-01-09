// Copyright Zero Games. All Rights Reserved.

#pragma once

#include "Scope/ZeroExtensionScope.h"
#include "Scope/ZDeferredExtensionScope.h"

#include "ZeroClientGameControllerBase.generated.h"

UCLASS(Abstract, Blueprintable)
class ZEROGAMEFRAMEWORKRUNTIME_API AZeroClientGameControllerBase : public AInfo, public IZeroExtensionScope
{
	GENERATED_BODY()

public:
	AZeroClientGameControllerBase();

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


