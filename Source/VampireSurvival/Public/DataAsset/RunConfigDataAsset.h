// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RunConfigDataAsset.generated.h"


class UWaveDataAsset;
/**
 * 
 */
UCLASS(BlueprintType)
class VAMPIRESURVIVAL_API URunConfigDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	// Debug 타임에 5분으로 설정
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Run")
	float DebugDurationSeconds = 300.f;
	
	// Production에서 30분 설정
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Run")
	float ProductionDurationSeconds = 1800.f;
	
	// 웨이브 에셋
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Run")
	TArray<TObjectPtr<UWaveDataAsset>> Waves;
};
