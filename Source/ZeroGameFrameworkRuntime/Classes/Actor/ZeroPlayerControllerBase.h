// Copyright Zero Games. All Rights Reserved.

#pragma once

#include "ZSharpReplicatedObject.h"
#include "Scope/ZExtensionScope.h"
#include "Scope/ZDeferredExtensionScope.h"

#include "ZeroPlayerControllerBase.generated.h"

UCLASS(Abstract)
class ZEROGAMEFRAMEWORKRUNTIME_API AZeroPlayerControllerBase : public APlayerController, public IZSharpReplicatedObject, public IZExtensionScope
{
	GENERATED_BODY()

public:
	AZeroPlayerControllerBase();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& outLifetimeProps) const override;

	virtual void ExtensionScope_RegisterExtender(UZExtenderBase* extender, FGameplayTag channel = FGameplayTag::EmptyTag) override;
	virtual void ExtensionScope_UnregisterExtender(UZExtenderBase* extender, FGameplayTag channel = FGameplayTag::EmptyTag) override;
	
	virtual void ExtensionScope_RegisterExtendee(UObject* extendee, FGameplayTag channel = FGameplayTag::EmptyTag) override;
	virtual void ExtensionScope_UnregisterExtendee(UObject* extendee, bool destroying, FGameplayTag channel = FGameplayTag::EmptyTag) override;
	
protected:
	virtual void SetupInputComponent() override;
	
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void ScriptSetupInputComponent(UEnhancedInputComponent* component);

private:
	bool bHasZSharpTick;
	
	ZES::FZDeferredExtensionScope ExtensionScope;
	
};


