// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PoolSubsystem.generated.h"


USTRUCT(BlueprintType)
struct FPoolPrewarmConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> ActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Count = 0;
};

USTRUCT()
struct FActorPool
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<TObjectPtr<AActor>> IdlePool;
};

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVAL_API UPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category="Pool")
	void PrewarmPool(TSubclassOf<AActor> ActorClass, int32 Count);

	UFUNCTION(BlueprintCallable, Category="Pool")
	void PrewarmPools(const TArray<FPoolPrewarmConfig>& PrewarmConfigs);

	UFUNCTION(BlueprintCallable, Category="Pool")
	AActor* GetActorFromPool(TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform);

	UFUNCTION(BlueprintCallable, Category="Pool")
	void ReturnActorToPool(AActor* Actor);

private:
	UPROPERTY()
	TMap<TSubclassOf<AActor>, FActorPool> IdlePools;


	void PrepareActorForPool(AActor* Actor);
	void PrepareActorForUse(AActor* Actor, const FTransform& SpawnTransform);
};
