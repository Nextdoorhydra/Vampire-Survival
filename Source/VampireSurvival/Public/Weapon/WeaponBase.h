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

//플레이어로 부터 Tick 을 받아오게 함

UCLASS(Abstract)
class VAMPIRESURVIVAL_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();

	virtual void Fire(FVector Direction);
	virtual void Tick(float DeltaSeconds) override;

	//On Kill 콜백 필요
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float Delay = 1.0f;

	//TODO 분리 필요
	float FireDelay = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	EWeaponState CurrentState = EWeaponState::Idle;

	FTimerHandle StateTimerHandle;

	void OnDelay(float DeltaSeconds);
	void OnIdle(float DeltaSeconds);
	virtual void OnAttacking(float DeltaSeconds);

	void ChangeWeaponState(EWeaponState NewState);

};
