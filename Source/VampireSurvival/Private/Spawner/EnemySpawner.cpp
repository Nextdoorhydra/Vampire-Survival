// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner/EnemySpawner.h"

#include "NavigationSystem.h"
#include "Entity/Character/PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "DataAsset/EnemyDataAsset.h"
#include "DataAsset/WaveDataAsset.h"
#include "Entity/Enemy/EnemyBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	CachedPlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (!CachedPlayerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("Player character not found"));
	}
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!bIsSpawning || !CurrentWaveData)
	{
		return;
	}
	
	WaveElapsedTime += DeltaTime;
	TimeSinceLastSpawn += DeltaTime;
	
	const FSpawnSegment* CurrentSegment = FindCurrentSpawnSegment();
	
	if (!CurrentSegment)
	{
		return;
	}
	
	if (TimeSinceLastSpawn >= CurrentSegment->SpawnInterval)
	{
		TimeSinceLastSpawn = 0.f;
		
		if (const FEnemySpawnGroup* SpawnGroup = SelectEnemySpawnGroup(*CurrentSegment))
		{
			SpawnEnemyFromGroup(*SpawnGroup);
		}
	}
	
	if (!bBossSpawned && CurrentWaveData->BossEnemyDataAsset && WaveElapsedTime >= CurrentWaveData->BossSpawnTime)
	{
		bBossSpawned = true;
		SpawnBoss();
	}
}

void AEnemySpawner::SetWaveData(UWaveDataAsset* NewWaveData)
{
	CurrentWaveData = NewWaveData;
	WaveElapsedTime = 0.f;
	TimeSinceLastSpawn = 0.f;
	bBossSpawned = false;
	
	if (CurrentWaveData)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemySpawner: Wave data set. WaveIndex=%d"), CurrentWaveData->WaveIndex);
	}
}

FVector AEnemySpawner::GetPlayerLocation() const
{
	if (!CachedPlayerCharacter)
	{
		return FVector::ZeroVector;
	}

	return CachedPlayerCharacter->GetActorLocation();
}

void AEnemySpawner::StartSpawning()
{
	bIsSpawning = true;
	
	TimeSinceLastSpawn = 0.f;
}

void AEnemySpawner::StopSpawning()
{
	bIsSpawning = false;
}

const FSpawnSegment* AEnemySpawner::FindCurrentSpawnSegment() const
{
	if (!CurrentWaveData)
	{
		return nullptr;
	}

	for (const FSpawnSegment& Segment : CurrentWaveData->SpawnSegments)
	{
		if (WaveElapsedTime >= Segment.StartTime && WaveElapsedTime < Segment.EndTime)
		{
			return &Segment;
		}
	}
	
	return nullptr;
}

const FEnemySpawnGroup* AEnemySpawner::SelectEnemySpawnGroup(const FSpawnSegment& Segment) const
{
	float totalWeight = 0.f;
	
	for (const FEnemySpawnGroup& Group : Segment.EnemyGroups)
	{
		if (Group.EnemyData && Group.SpawnWeight > 0.f)
		{
			totalWeight += Group.SpawnWeight;
		}
	}
	
	if (totalWeight <= 0.f)
	{
		return nullptr;
	}
	
	float randValue = FMath::FRandRange(0.f, totalWeight);
	
	for (const FEnemySpawnGroup& Group : Segment.EnemyGroups)
	{
		if (!Group.EnemyData || Group.SpawnWeight <= 0.f)
		{
			continue;
		}
		
		randValue -= Group.SpawnWeight;
		if (randValue <= 0.f)
		{
			return &Group;
		}
	}
	
	return nullptr;
}

void AEnemySpawner::SpawnEnemyFromGroup(const FEnemySpawnGroup& SpawnGroup)
{
	SpawnEnemyFromData(
		SpawnGroup.EnemyData,
		SpawnGroup.CountPerSpawn
		);
}

void AEnemySpawner::SpawnEnemyFromData(class UEnemyDataAsset* EnemyData, int32 Count)
{
	if (!EnemyData || !EnemyData->EnemyClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemySpawner: Invalid EnemyData"));
		return;
	}
	
	CleanupInvalidEnemies();
	
	for (int32 i=0; i < Count; ++i)
	{
		FVector SpawnLocation;
		if (!FindSpawnLocation(SpawnLocation))
		{
			UE_LOG(LogTemp, Warning, TEXT("EnemySpawner: FindSpawnLocation failed"));
			continue;
		}
		
		AEnemyBase* DefaultEnemy = EnemyData->EnemyClass->GetDefaultObject<AEnemyBase>();
		if (DefaultEnemy && DefaultEnemy->GetCapsuleComponent())
		{
			SpawnLocation.Z = DefaultEnemy->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		}
		
		FActorSpawnParameters SpawnParams;
		
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		
		AEnemyBase* SpawnedEnemy = GetWorld()->SpawnActor<AEnemyBase>(
			EnemyData->EnemyClass,
			SpawnLocation,
			FRotator::ZeroRotator,
			SpawnParams
		);
		
		if (SpawnedEnemy)
		{
			SpawnedEnemy->InitializeFromData(EnemyData);
			SpawnedEnemiesList.Add(SpawnedEnemy);
		}
	}
}

void AEnemySpawner::SpawnBoss()
{
	if (!CurrentWaveData || !CurrentWaveData->BossEnemyDataAsset)
	{
		return;
	}
	
	SpawnEnemyFromData(CurrentWaveData->BossEnemyDataAsset, 1);
}


bool AEnemySpawner::FindSpawnLocation(FVector& SpawnLocation) const
{
	const float angle = FMath::FRandRange(0.f, 2.f * PI);

	FVector direction(
		FMath::Cos(angle),
		FMath::Sin(angle),
		0.f
	);

	const float distance = FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);

	const FVector candidateLocation = GetPlayerLocation() + direction * distance;


	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSystem)
	{
		return false;
	}

	FNavLocation navLocation;

	// candidateLocation이 정확히 NavMesh 위가 아닐 수도 있음
	// xyz 5미터 탐색지역 생성
	const FVector QueryExtent(500.f, 500.f, 500.f);

	// candidateLocation 주변 QueryExtent 내에서 Nav Mesh 탐색
	// ProjectPointToNavigation = 입력위치를 navigation data위로 투영 > FNavLocation return
	const bool bProjected = NavSystem->ProjectPointToNavigation(
		candidateLocation,
		navLocation,
		QueryExtent
	);

	if (!bProjected)
	{
		return false;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Spawned"));

	SpawnLocation = navLocation.Location;
	return true;
}

void AEnemySpawner::CleanupInvalidEnemies()
{
	SpawnedEnemiesList.RemoveAll([](const TObjectPtr<AActor>& Enemy)
	{
		return !IsValid(Enemy);
	});
}
