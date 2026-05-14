// Fill out your copyright notice in the Description page of Project Settings.



// #include "Weapon/ProjectileObject/SimpleBullet.h"
//
// #include "Attack/SimpleAttackComponent.h"
#include "Equipment/Weapon/ProjectileObject/SimpleBullet.h"


#include "Component/SimpleAttackComponent.h"
#include "Components/SphereComponent.h"
#include "Entity/IHitable.h"


ASimpleBullet::ASimpleBullet()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComponent->SetupAttachment(RootComponent); 
	
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(RootComponent); 

	AttackBaseComponent = CreateDefaultSubobject<USimpleAttackComponent>(TEXT("AttackComp"));

	PrimaryActorTick.bCanEverTick = true;
}

void ASimpleBullet::BeginPlay()
{
	Super::BeginPlay();

	// 충돌 이벤트 바인딩
	if (SphereComponent)
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASimpleBullet::OnBulletOverlap);
}

void ASimpleBullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
                                    bool bFromSweep, const FHitResult& SweepResult)
{
	auto hitable = Cast<IHitable>(OtherActor);
	if (AttackBaseComponent == nullptr || hitable == nullptr) return;

	AttackBaseComponent->HandleAttackOverlap(Damage, hitable, this);
	Destroy();
}
