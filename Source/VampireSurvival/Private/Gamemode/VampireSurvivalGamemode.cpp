#include "Gamemode/VampireSurvivalGamemode.h"

#include "EngineUtils.h"
#include "DataAsset/RunConfigDataAsset.h"
#include "DataAsset/WaveDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "Spawner/EnemySpawner.h"

AVampireSurvivalGamemode::AVampireSurvivalGamemode()
{
}

void AVampireSurvivalGamemode::BeginPlay()
{
	Super::BeginPlay();


	for (TActorIterator<AEnemySpawner> It(GetWorld()); It; ++It)
	{
		EnemySpawner = *It;
		break;
	}

	StartRun();
}

void AVampireSurvivalGamemode::StartRun()
{
	if (!RunConfig)
	{
		UE_LOG(LogTemp, Warning, TEXT("RunConfig is not set."));
		return;
	}

	//Debug, Production duration set 및 판단
	RunDurationSeconds = bUseDebugDuration
		                     ? RunConfig->DebugDurationSeconds
		                     : RunConfig->ProductionDurationSeconds;

	ElapsedTime = 0.f;
	CurrentWave = nullptr;
	CurrentWaveIndex = INDEX_NONE;

	SetCurrentWave(FindWaveForElapsedTime(ElapsedTime));

	GetWorldTimerManager().SetTimer(
		RunTimerHandler,
		this,
		&AVampireSurvivalGamemode::UpdateRunTime,
		1.f,
		true
	);
}

void AVampireSurvivalGamemode::UpdateRunTime()
{
	ElapsedTime += 1.f;

	if (ElapsedTime >= RunDurationSeconds)
	{
		EndRun();
		return;
	}

	SetCurrentWave(FindWaveForElapsedTime(ElapsedTime));

	// 보스 스폰 판단
	// Spawner가 CurrentWave + ElapsedTime 처리
}

void AVampireSurvivalGamemode::EndRun()
{
	GetWorldTimerManager().ClearTimer(RunTimerHandler);

	if (EnemySpawner)
	{
		EnemySpawner->StopSpawning();
	}

	UE_LOG(LogTemp, Warning, TEXT("Run ended."));
}

UWaveDataAsset* AVampireSurvivalGamemode::FindWaveForElapsedTime(float InElapsedTime) const
{
	if (!RunConfig)
	{
		return nullptr;
	}

	for (UWaveDataAsset* Wave : RunConfig->Waves)
	{
		if (!Wave)
		{
			continue;
		}

		if (InElapsedTime >= Wave->StartTime && InElapsedTime < Wave->EndTime)
		{
			return Wave;
		}
	}

	return nullptr;
}

void AVampireSurvivalGamemode::SetCurrentWave(UWaveDataAsset* NewWave)
{
	if (CurrentWave == NewWave)
	{
		return;
	}

	CurrentWave = NewWave;

	if (!CurrentWave)
	{
		return;
	}

	CurrentWaveIndex = CurrentWave->WaveIndex;

	UE_LOG(LogTemp, Warning, TEXT("Wave changed: %d"), CurrentWaveIndex);

	if (EnemySpawner)
	{
		EnemySpawner->SetElapsedTime(ElapsedTime);
		EnemySpawner->SetWaveData(CurrentWave);
		EnemySpawner->StartSpawning();
	}
}
