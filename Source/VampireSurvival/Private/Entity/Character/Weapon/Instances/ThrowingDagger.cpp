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
	//TODO 데이터 에셋 받아서 증가량 적용
	if (InLevel >= 2) Damage = 3;
	if (InLevel >= 3) DaggerCount = 2;
	if (InLevel >= 4) FireDelay = 0.5f;
	if (InLevel >= 5) DaggerCount = 4;
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
