// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Character/Weapon/Instances/ThrowingDagger.h"
#include "Curves/CurveVector.h"


AThrowingDagger::AThrowingDagger()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AThrowingDagger::OnAttacking()
{
	if (!SpawnTimingCurve || DaggerCount <= 0)
	{
		FinishAttack();
		return;
	}

	const FRichCurve& RichCurve = SpawnTimingCurve->FloatCurve;
    
	const int32 TotalKeys = RichCurve.Keys.Num();
	const int32 SpawnCount = FMath::Min(TotalKeys, DaggerCount);

	
	for (int32 i = 0; i < SpawnCount; i++)
	{
		const FRichCurveKey& Key = RichCurve.Keys[i];

		// 최소 0.01초를 보장하여 0초 타이머 버그를 방지
		float SpawnDelay =FMath::Max(0.01f, Key.Time); 
        
		bool bIsLastKey = (i >= SpawnCount -1);

		FTimerHandle TempHandle;
		GetWorldTimerManager().SetTimer(TempHandle, [this, bIsLastKey]()
		{
			if (!IsValid(this)) return;
			RequestBulletSpawn(GetRandomSpawnTransform());
			if (bIsLastKey)
				this->FinishAttack();
			
		}, SpawnDelay, false);
	}
}

FTransform AThrowingDagger::GetRandomSpawnTransform() const
{
	if (!SpawnLocationCurve) return GetActorTransform();

	float RandomTime = FMath::FRand(); 

	FVector LocalOffset = SpawnLocationCurve->GetVectorValue(RandomTime);
	FTransform SpawnTM = GetActorTransform();
	FVector WorldLocation = SpawnTM.TransformPosition(LocalOffset);

	SpawnTM.SetLocation(WorldLocation);
	
	return SpawnTM;
}
