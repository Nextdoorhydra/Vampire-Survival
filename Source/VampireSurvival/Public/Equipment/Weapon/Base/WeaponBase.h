// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8 
{
	Idle        UMETA(DisplayName = "Idle"),
	Attacking   UMETA(DisplayName = "Attacking"),
	Delay       UMETA(DisplayName = "Delay"),
};

UCLASS(Abstract)
class VAMPIRESURVIVAL_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void Spawn(AActor* InOwner);

	//무기 kill count 올리려면?
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats")
	TObjectPtr<class UEquipData> EquipData;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|State")
	EWeaponState CurrentState = EWeaponState::Idle;

	FTimerHandle StateTimerHandle;

	virtual void OnAttacking(){}

	UFUNCTION()
	virtual void FinishAttack();
	
	virtual void ApplyLevelSpec(int InLevel);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Stats")
	float FireDelay = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Stats")
	float Damage = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Stats")
	float KnockBack = 1.f;

private:
	void ChangeWeaponState(EWeaponState NewState);
	void HandleDelayState();
	void HandleIdleState();
	void HandleAttackingState();
};
