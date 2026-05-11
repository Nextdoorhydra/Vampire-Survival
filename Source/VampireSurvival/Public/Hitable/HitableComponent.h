// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HitableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHPChangedDelegate, float, CurrentHP, float, MaxHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VAMPIRESURVIVAL_API UHitableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHitableComponent();
	
	virtual void Initialize(float InMaxHP);
	
	//getter setter
	float GetMaxHP() const { return MaxHP; }
	void SetMaxHP(float Amount);
	virtual void AddMaxHP(float Amount);
	float GetHP() const { return CurrentHP; }
	void SetHP(float Amount);
	void AddHP(float Amount);
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHPChangedDelegate OnHPChangedEvent; // 체력 변경시 호출될 이벤트
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDeathDelegate OnDeathEvent; // 사망 시 호출될 이벤트
	
protected:
	void OnHPChanged();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Stats")
	float MaxHP = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|Stats")
	float CurrentHP = 100.f;
};
