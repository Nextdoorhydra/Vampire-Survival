// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Weapon/Instances/ThrowingDagger.h"
#include "Curves/CurveVector.h"
#include "DataAsset/EquipData.h"


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

	LookAt();

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
		TWeakObjectPtr WeakThis(this);
		GetWorldTimerManager().SetTimer(TempHandle, [WeakThis, bIsLastKey]()
		{
			
			if (!WeakThis.IsValid()) return;
			WeakThis->RequestBulletSpawn(WeakThis->GetRandomSpawnTransform());
			if (bIsLastKey)
				WeakThis->FinishAttack();
			
		}, SpawnDelay, false);
	}
}

void AThrowingDagger::ApplyLevelSpec(int InLevel)
{
	if (InLevel < 1 || EquipData->LevelDataList.Num() >= InLevel) return;
	auto levelPower = EquipData->LevelDataList[InLevel].AttackPowerIncrease; 
	switch (InLevel)
	{
	case 2: Damage += levelPower; break; 
	case 3: DaggerCount += levelPower; break; 
	case 4: FireDelay *= (1.0f - (levelPower / 100.f)); break;
	case 5: Damage += levelPower; break;
	}
}

void AThrowingDagger::LookAt()
{
	Super::LookAt();
	if (!GetOwner()) return;
	
	SetActorRotation(GetOwner()->GetActorRotation());

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
