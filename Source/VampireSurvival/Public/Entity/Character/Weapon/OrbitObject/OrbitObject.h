// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OrbitObject.generated.h"

/*
 * 사용하는 클래스 안에서 피격되었던 객체 리스트를 초기화 해주는 함수를 실행시켜주면 좋다.
 */

class UAttackBaseComponent;

UCLASS(Abstract)
class VAMPIRESURVIVAL_API AOrbitObject : public AActor
{
	GENERATED_BODY()

public:
	AOrbitObject();

	//활성 비활성 필요
	
	virtual void InjectData(float InDamage, float InKnockBack);
	void ClearHitCooldown();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY()
	TMap<AActor*, float> HitCooldownMap; // 대상 액터와 다음 공격 가능 시간을 저장

	float Damage = 0;
	float KnockBack = 0;
};
