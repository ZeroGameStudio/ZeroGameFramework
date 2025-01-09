// Copyright Zero Games. All Rights Reserved.

#pragma once

#include "ZSharpReplicatedObject.h"
#include "Scope/ZeroExtensionScope.h"
#include "Scope/ZDeferredExtensionScope.h"

#include "ZeroPlayerControllerBase.generated.h"

UCLASS(Abstract)
class ZEROGAMEFRAMEWORKRUNTIME_API AZeroPlayerControllerBase : public APlayerController, public IZSharpReplicatedObject, public IZeroExtensionScope
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& outLifetimeProps) const override;

	virtual void ZeroExtensionScope_RegisterExtender(UZeroExtenderBase* extender, FGameplayTag channel = FGameplayTag::EmptyTag) override;
	virtual void ZeroExtensionScope_UnregisterExtender(UZeroExtenderBase* extender, FGameplayTag channel = FGameplayTag::EmptyTag) override;
	
	virtual void ZeroExtensionScope_RegisterExtendee(UObject* extendee, FGameplayTag channel = FGameplayTag::EmptyTag) override;
	virtual void ZeroExtensionScope_UnregisterExtendee(UObject* extendee, bool destroying, FGameplayTag channel = FGameplayTag::EmptyTag) override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void ScriptSetupInputComponent(UEnhancedInputComponent* component);
	
private:
	virtual void SetupInputComponent() override;
	
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

private:
	ZES::FZDeferredExtensionScope ExtensionScope;
	
};


