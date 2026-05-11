// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class ACharacter;
class APlayerCharacter;
class AEnemyBase;
class UWaveDataAsset;
struct FSpawnSegment;
struct FEnemySpawnGroup;

UCLASS()
class VAMPIRESURVIVAL_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	FVector GetPlayerLocation() const;

public:
	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void StartSpawning();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void StopSpawning();
	
	// 웨이브 설정 셋
	void SetWaveData(UWaveDataAsset* NewWaveData);
	
	void SpawnBoss();

private:
	APlayerCharacter* CachedPlayerCharacter;
	
	// Spawn할 현재 Wave 데이터
	TObjectPtr<UWaveDataAsset> CurrentWaveData;
	
	// Spawn된 Enemy class 기반 객체 리스트
	UPROPERTY()
	TArray<TObjectPtr<AActor>> SpawnedEnemiesList;
	
	// Spawner 필요 요소
	// 1. 스폰 주기 (World timer 연동 해야하나?)
	// 2. 스폰 반경 (플레이어 반경 n미터 내, 너무 가까운 곳은 X)
	// 3. 스폰 조건 (navmesh 상 존재하는 location인지?)
	// 4. 타이머 핸들러

	// 스폰 주기
	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnInterval = 3.f;

	// 스폰 반경
	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnRadius = 1200.f;
	
	// 스폰 위치
	UPROPERTY(EditAnywhere, Category = "Spawner")
	float MinSpawnDistance = 2000.f;
	UPROPERTY(EditAnywhere, Category = "Spawner")
	float MaxSpawnDistance = 3000.f;
	
	float bIsSpawning = false;
	float bBossSpawned = false;
	
	float WaveElapsedTime = 0.f;
	float TimeSinceLastSpawn = 0.f;
	
	const FSpawnSegment* FindCurrentSpawnSegment() const;
	const FEnemySpawnGroup* SelectEnemySpawnGroup(const FSpawnSegment& Segment) const;
	
	void SpawnEnemyFromGroup(const FEnemySpawnGroup& SpawnGroup);
	void SpawnEnemyFromData(class UEnemyDataAsset* EnemyData, int32 Count);
	
	// Spawn 가능한지 체크
	bool FindSpawnLocation(FVector& SpawnLocation) const;

	// Enemy class cleanup
	void CleanupInvalidEnemies();
	

	// 타이머 핸들러
	FTimerHandle SpawnTimerHandler;
};
