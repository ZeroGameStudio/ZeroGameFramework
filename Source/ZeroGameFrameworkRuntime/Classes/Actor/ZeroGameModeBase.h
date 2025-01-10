// Copyright Zero Games. All Rights Reserved.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "Scope/ZDeferredExtensionScope.h"
#include "Scope/ZExtensionScope.h"

#include "ZeroGameModeBase.generated.h"

class AZeroClientGameControllerBase;

UCLASS(Abstract)
class ZEROGAMEFRAMEWORKRUNTIME_API AZeroGameModeBase : public AGameModeBase, public IZExtensionScope
{
	GENERATED_BODY()

public:
	AZeroGameModeBase();

public:
	virtual void ExtensionScope_RegisterExtender(UZExtenderBaseInterface* extender, FGameplayTag channel = FGameplayTag::EmptyTag) override;
	virtual void ExtensionScope_UnregisterExtender(UZExtenderBaseInterface* extender, FGameplayTag channel = FGameplayTag::EmptyTag) override;
	
	virtual void ExtensionScope_RegisterExtendee(UObject* extendee, FGameplayTag channel = FGameplayTag::EmptyTag) override;
	virtual void ExtensionScope_UnregisterExtendee(UObject* extendee, bool destroying, FGameplayTag channel = FGameplayTag::EmptyTag) override;

protected:
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes, meta = (AllowPrivateAccess))
	TSubclassOf<AZeroClientGameControllerBase> ClientGameControllerClass;

private:
	bool bHasZSharpTick;
	
	ZES::FZDeferredExtensionScope ExtensionScope;
	
};


