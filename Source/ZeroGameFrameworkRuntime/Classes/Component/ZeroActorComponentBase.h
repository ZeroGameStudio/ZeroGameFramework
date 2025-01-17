// Copyright Zero Games. All Rights Reserved.

#pragma once

#include "ZSharpReplicatedObject.h"

#include "ZeroActorComponentBase.generated.h"

UCLASS(Abstract, Blueprintable)
class ZEROGAMEFRAMEWORKRUNTIME_API UZeroActorComponentBase : public UActorComponent, public IZSharpReplicatedObject
{
	GENERATED_BODY()

public:
	UZeroActorComponentBase();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& outLifetimeProps) const override;

public:
	UFUNCTION(BlueprintPure, Category = "Replication")
	ENetRole GetLocalRole() const;

	UFUNCTION(BlueprintPure, Category = "Replication")
	ENetRole GetRemoteRole() const;

	UFUNCTION(BlueprintPure, Category = "Replication")
	bool HasAuthority() const;

protected:
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
	
	virtual void Activate(bool reset = false) override;
	virtual void Deactivate() override;
	
	virtual void TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveInitialize();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveUninitialize();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveRegister();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveUnregister();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveActivate();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveDeactivate();
	
private:
	bool bIsZSharpClass;
	bool bHasZSharpTick;
	
};


