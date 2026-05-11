// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyDataAsset.generated.h"

/**
 * 
 */

class AEnemyBase;

UCLASS(BlueprintType)
class VAMPIRESURVIVAL_API UEnemyDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy")
	TSubclassOf<AEnemyBase> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy|Stats")
	float BaseMaxHP = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy|Stats")
	float BaseMoveSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy|Stats")
	float BaseDamage = 5.f;

	// 경험치
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy|Reward")
	int32 ExpReward = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy")
	bool bIsBoss = false;
};
