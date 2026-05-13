// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Character/Weapon/OrbitObject/SimpleOrbitObject.h"

#include "Component/SimpleAttackComponent.h"
#include "Components/SphereComponent.h"
#include "Entity/IHitable.h"

ASimpleOrbitObject::ASimpleOrbitObject()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetCollisionProfileName("P_Player_Attack");
	
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(RootComponent); 

	AttackBaseComponent = CreateDefaultSubobject<USimpleAttackComponent>(TEXT("AttackComp"));
	
	PrimaryActorTick.bCanEverTick = true;
}

void ASimpleOrbitObject::BeginPlay()
{
	Super::BeginPlay();

	// 충돌 이벤트 바인딩
	if (SphereComponent)
		SphereComponent->OnComponentBeginOverlap
			.AddDynamic(this, &ASimpleOrbitObject::OnOrbitOverlap);

	DefaultSceneRoot->SetUsingAbsoluteScale(true);
	DefaultSceneRoot->SetUsingAbsoluteRotation(true);
}

void ASimpleOrbitObject::OnOrbitOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Hitable = Cast<IHitable>(OtherActor);
	if (!AttackBaseComponent || !Hitable) return;

	float CurrentTime = GetWorld()->GetTimeSeconds();

	//피격 쿨타임 확인
	if (HitCooldownMap.Contains(OtherActor)
		&& CurrentTime < HitCooldownMap[OtherActor])
		return;
	//수정필요

	HitCooldownMap.Add(OtherActor, CurrentTime + AttackInterval);
	AttackBaseComponent->HandleAttackOverlap(Damage, Hitable, this);
}




