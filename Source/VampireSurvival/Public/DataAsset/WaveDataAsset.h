// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WaveDataAsset.generated.h"


class UEnemyDataAsset;

USTRUCT(BlueprintType)
struct FEnemySpawnGroup
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	TObjectPtr<UEnemyDataAsset> EnemyData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	float SpawnWeight = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	float HPScale = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	int32 CountPerSpawn = 1;
};

USTRUCT(BlueprintType)
struct FSpawnSegment
{
	GENERATED_BODY()
	;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	float StartTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	float EndTime = 60.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	float SpawnInterval = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	TArray<FEnemySpawnGroup> EnemyGroups;
};

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVAL_API UWaveDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 WaveIndex = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	float StartTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	float EndTime = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	TArray<FSpawnSegment> SpawnSegments;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boss")
	TObjectPtr<UEnemyDataAsset> BossEnemyDataAsset;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boss")
	float BossSpawnTime = 300.f;
};
