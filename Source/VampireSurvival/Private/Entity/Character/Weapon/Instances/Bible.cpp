// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Character/Weapon/Instances/Bible.h"

#include "Components/TimelineComponent.h"
#include "Entity/Character/Weapon/OrbitObject/OrbitObject.h"
#include "Entity/Character/Weapon/OrbitObject/SimpleOrbitObject.h"


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
	if (InLevel >= 2) Damage = 3;
	if (InLevel >= 3) OrbitObjectCount = 2;
	if (InLevel >= 4) FireDelay = 0.5f;
	if (InLevel >= 5) OrbitObjectCount = 4;
}

void ABible::UpdateOrbitScale(float timelineElapse)
{
	SetActorScale3D(FVector(timelineElapse));
}

void ABible::UpdateOrbitRotation(float timelineElapse)
{
	SetActorRotation(FRotator(0.f, timelineElapse * RotationCount * 360.f, 0.f));
}


