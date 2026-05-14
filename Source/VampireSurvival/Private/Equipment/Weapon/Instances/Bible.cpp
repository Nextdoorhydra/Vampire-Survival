// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Weapon/Instances/Bible.h"

#include "Components/TimelineComponent.h"
#include "DataAsset/EquipData.h"


// Sets default values
ABible::ABible()
{
	PrimaryActorTick.bCanEverTick = true;

	OrbitTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("OrbitTimeline"));
}

void ABible::BeginPlay()
{
	Super::BeginPlay();

	//커브 있는지 확인 필요
	if (OrbitTimeline && OrbitRotationCurve && OrbitScaleCurve)
	{
		FOnTimelineFloat UpdateScaleEvent;
		FOnTimelineFloat UpdateRotationEvent;
		FOnTimelineEvent FinishedEvent;

		UpdateScaleEvent.BindUFunction(this, FName("UpdateOrbitScale"));
		UpdateRotationEvent.BindUFunction(this, FName("UpdateOrbitRotation"));
		FinishedEvent.BindUFunction(this, FName("FinishAttack"));
		
		OrbitTimeline->AddInterpFloat(OrbitScaleCurve, UpdateScaleEvent);
		OrbitTimeline->AddInterpFloat(OrbitRotationCurve, UpdateRotationEvent);
		OrbitTimeline->SetTimelineFinishedFunc(FinishedEvent);
		OrbitTimeline->SetLooping(false);
	}
}

void ABible::OnAttacking()
{
	CheckAndSpawnOrbitObject();
	OrbitTimeline->PlayFromStart();
}

void ABible::FinishAttack()
{
	Super::FinishAttack();
	ToggleActiveOrbitObject(false);
}

void ABible::ApplyLevelSpec(int InLevel)
{
	if (InLevel < 1 || EquipData->LevelDataList.Num() >= InLevel) return;
	auto levelPower = EquipData->LevelDataList[InLevel].AttackPowerIncrease; 
	switch (InLevel)
	{
	case 2: Damage += levelPower; break; 
	case 3: OrbitObjectCount += levelPower; break; 
	case 4: FireDelay *= (1.0f - (levelPower / 100.f)); break;
	case 5: Damage += levelPower; break;
	}
}

void ABible::UpdateOrbitScale(float timelineElapse)
{
	SetActorScale3D(FVector(timelineElapse));
}

void ABible::UpdateOrbitRotation(float timelineElapse)
{
	SetActorRotation(FRotator(0.f, timelineElapse * RotationCount * 360.f, 0.f));
}


