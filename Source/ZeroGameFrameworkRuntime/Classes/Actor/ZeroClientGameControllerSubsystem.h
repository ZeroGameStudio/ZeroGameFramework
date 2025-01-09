// Copyright Zero Games. All Rights Reserved.

#pragma once

#include "Scope/ZeroExtensionScope.h"
#include "Scope/ZDeferredExtensionScope.h"

#include "ZeroClientGameControllerSubsystem.generated.h"

class AZeroClientGameControllerBase;

namespace ZGF::ZeroClientGameControllerSubsystem_Private
{
	struct FZSetController
	{
		friend class AZeroClientGameControllerBase;
	private:
		FZSetController(AZeroClientGameControllerBase* controller);
	};
}

UCLASS(NotBlueprintable)
class ZEROGAMEFRAMEWORKRUNTIME_API UZeroClientGameControllerSubsystem final : public UWorldSubsystem, public IZeroExtensionScope
{
	GENERATED_BODY()

	friend ZGF::ZeroClientGameControllerSubsystem_Private::FZSetController;

public:
	virtual void ZeroExtensionScope_RegisterExtender(UZeroExtenderBase* extender, FGameplayTag channel = FGameplayTag::EmptyTag) override;
	virtual void ZeroExtensionScope_UnregisterExtender(UZeroExtenderBase* extender, FGameplayTag channel = FGameplayTag::EmptyTag) override;
	virtual void ZeroExtensionScope_RegisterExtendee(UObject* extendee, FGameplayTag channel = FGameplayTag::EmptyTag) override;
	virtual void ZeroExtensionScope_UnregisterExtendee(UObject* extendee, bool destroying, FGameplayTag channel = FGameplayTag::EmptyTag) override;

public:
	UFUNCTION(BlueprintPure)
	AZeroClientGameControllerBase* GetController() const { return Controller; }

private:
	virtual bool ShouldCreateSubsystem(UObject* outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& collection) override;
	virtual void Deinitialize() override;

private:
	void SetController(AZeroClientGameControllerBase* controller);

private:
	UPROPERTY()
	TObjectPtr<AZeroClientGameControllerBase> Controller;

private:
	ZES::FZDeferredExtensionScope ExtensionScope;
	
};


