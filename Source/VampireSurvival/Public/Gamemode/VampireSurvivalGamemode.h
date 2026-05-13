// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VampireSurvivalGamemode.generated.h"

class UWaveDataAsset;
class URunConfigDataAsset;
class AEnemySpawner;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRunElapsedTimeChanged, float, ElapsedTime);

UCLASS()
class VAMPIRESURVIVAL_API AVampireSurvivalGamemode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AVampireSurvivalGamemode();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InGamemode|Run")
	TObjectPtr<URunConfigDataAsset> RunConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InGamemode|Run")
	bool bUseDebugDuration = true;

	UPROPERTY(BlueprintReadOnly, Category = "InGamemode|Run")
	float ElapsedTime = 0.f;

	UPROPERTY(BlueprintAssignable, Category = "InGamemode|Run")
	FOnRunElapsedTimeChanged OnRunElapsedTimeChanged;

	UPROPERTY(BlueprintReadOnly, Category = "InGamemode|Run")
	float RunDurationSeconds = 300.f;

	UPROPERTY(BlueprintReadOnly, Category = "InGamemode|Wave")
	TObjectPtr<UWaveDataAsset> CurrentWave;

	UPROPERTY(BlueprintReadOnly, Category = "InGamemode|Wave")
	int32 CurrentWaveIndex = INDEX_NONE;

	UPROPERTY()
	TObjectPtr<AEnemySpawner> EnemySpawner;

	FTimerHandle RunTimerHandler;

	void StartRun();
	void UpdateRunTime();
	void EndRun();

	UWaveDataAsset* FindWaveForElapsedTime(float InElapsedTime) const;
	void SetCurrentWave(UWaveDataAsset* NewWave);
};
