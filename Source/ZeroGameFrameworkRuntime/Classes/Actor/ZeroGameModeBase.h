// Copyright Zero Games. All Rights Reserved.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "Scope/ZDeferredExtensionScope.h"
#include "Scope/ZeroExtensionScope.h"

#include "ZeroGameModeBase.generated.h"

class AZeroClientGameControllerBase;

UCLASS(Abstract)
class ZEROGAMEFRAMEWORKRUNTIME_API AZeroGameModeBase : public AGameModeBase, public IZeroExtensionScope
{
	GENERATED_BODY()

public:
	AZeroGameModeBase();

public:
	virtual void ZeroExtensionScope_RegisterExtender(UZeroExtenderBase* extender, FGameplayTag channel = FGameplayTag::EmptyTag) override;
	virtual void ZeroExtensionScope_UnregisterExtender(UZeroExtenderBase* extender, FGameplayTag channel = FGameplayTag::EmptyTag) override;
	
	virtual void ZeroExtensionScope_RegisterExtendee(UObject* extendee, FGameplayTag channel = FGameplayTag::EmptyTag) override;
	virtual void ZeroExtensionScope_UnregisterExtendee(UObject* extendee, bool destroying, FGameplayTag channel = FGameplayTag::EmptyTag) override;

private:
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes, meta = (AllowPrivateAccess))
	TSubclassOf<AZeroClientGameControllerBase> ClientGameControllerClass;

private:
	ZES::FZDeferredExtensionScope ExtensionScope;
	
};


