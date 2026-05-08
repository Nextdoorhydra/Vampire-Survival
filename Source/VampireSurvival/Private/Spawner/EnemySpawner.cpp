// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner/EnemySpawner.h"

#include "NavigationSystem.h"
#include "Character/PlayerCharacter.h"
#include "GameFramework/Character.h"
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
	if (!GetWorld())
	{
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandler,
		this,
		&AEnemySpawner::SpawnEnemy,
		SpawnInterval,
		true,
		-1
	);
}

void AEnemySpawner::StopSpawning()
{
	if (!GetWorld())
	{
		return;
	}

	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandler);
}

void AEnemySpawner::SpawnEnemy()
{
	if (!EnemyClass)
	{
		return;
	}
	CleanupInvalidEnemies();

	// 스폰 위치 선언
	FVector SpawnLocation;

	// spawn location 체크결과 false일 경우 return
	if (!FindSpawnLocation(SpawnLocation))
	{
	}
}

bool AEnemySpawner::FindSpawnLocation(FVector& SpawnLocation) const
{
	// 플레이어 기준 랜덤 방향
	// 최소 20m ~ 최대 30m
	constexpr float minSpawnDistance = 2000.f;
	constexpr float maxSpawnDistance = 3000.f;

	const float angle = FMath::FRandRange(0.f, 2.f * PI);

	FVector direction(
		FMath::Cos(angle),
		FMath::Sin(angle),
		0.f
	);

	const float distance = FMath::FRandRange(minSpawnDistance, maxSpawnDistance);

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

	SpawnLocation = navLocation.Location;
	return true;
}
