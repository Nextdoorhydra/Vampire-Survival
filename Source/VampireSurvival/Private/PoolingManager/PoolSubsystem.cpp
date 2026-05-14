// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolingManager/PoolSubsystem.h"

#include "Entity/IPoolable.h"

void UPoolSubsystem::Deinitialize()
{
	IdlePools.Empty();

	Super::Deinitialize();
}

void UPoolSubsystem::PrewarmPool(TSubclassOf<AActor> ActorClass, int32 Count)
{
	if (!ActorClass || Count <= 0 || !GetWorld())
	{
		return;
	}

	FActorPool& Pool = IdlePools.FindOrAdd(ActorClass);


	for (int32 i = 0; i < Count; ++i)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* Actor = GetWorld()->SpawnActor<AActor>(
			ActorClass,
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			SpawnParams
		);

		if (!Actor)
		{
			// 풀링체크용
			UE_LOG(LogTemp, Warning, TEXT("[Pool] Prewarm spawn failed: %s"), *ActorClass->GetName());
			continue;
		}

		PrepareActorForPool(Actor);
		Pool.IdlePool.Add(Actor);
	}

	// 풀링체크용
	UE_LOG(LogTemp, Warning, TEXT("[Pool] Prewarm %s / Available: %d"),
	       *ActorClass->GetName(),
	       Pool.IdlePool.Num());
}

void UPoolSubsystem::PrewarmPools(const TArray<FPoolPrewarmConfig>& PrewarmConfigs)
{
	for (const FPoolPrewarmConfig& Config : PrewarmConfigs)
	{
		PrewarmPool(Config.ActorClass, Config.Count);
	}
}

AActor* UPoolSubsystem::GetActorFromPool(TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform)
{
	if (!ActorClass || !GetWorld())
	{
		return nullptr;
	}

	FActorPool& Pool = IdlePools.FindOrAdd(ActorClass);

	AActor* Actor = nullptr;

	while (Pool.IdlePool.Num() > 0)
	{
		Actor = Pool.IdlePool.Pop();

		if (IsValid(Actor))
		{
			break;
		}

		Actor = nullptr;
	}

	if (!Actor)
	{
		Actor = GetWorld()->SpawnActor<AActor>(ActorClass, SpawnTransform);
	}

	if (!Actor)
	{
		return nullptr;
	}

	PrepareActorForUse(Actor, SpawnTransform);


	// 풀링체크용
	UE_LOG(LogTemp, Warning, TEXT("[Pool] Get %s / Available: %d / Active: %d"),
	       *ActorClass->GetName(),
	       Pool.IdlePool.Num(),
	       IdlePools.Num());

	return Actor;
}

void UPoolSubsystem::ReturnActorToPool(AActor* Actor)
{
	if (!IsValid(Actor))
	{
		return;
	}

	PrepareActorForPool(Actor);

	IdlePools.FindOrAdd(Actor->GetClass()).IdlePool.Add(Actor);
}

void UPoolSubsystem::PrepareActorForPool(AActor* Actor)
{
	if (!IsValid(Actor))
	{
		return;
	}

	if (IPoolable* Poolable = Cast<IPoolable>(Actor))
	{
		//ReturnToPool은 순수함수라 
		Poolable->ReturnToPool();
	}

	Actor->SetActorHiddenInGame(true);
	Actor->SetActorEnableCollision(false);
	Actor->SetActorTickEnabled(false);
}

void UPoolSubsystem::PrepareActorForUse(AActor* Actor, const FTransform& SpawnTransform)
{
	if (!IsValid(Actor))
	{
		return;
	}

	Actor->SetActorTransform(SpawnTransform);
	Actor->SetActorHiddenInGame(false);
	Actor->SetActorEnableCollision(true);
	Actor->SetActorTickEnabled(true);

	if (IPoolable* Poolable = Cast<IPoolable>(Actor))
	{
		Poolable->GetFromPool();
	}
}
