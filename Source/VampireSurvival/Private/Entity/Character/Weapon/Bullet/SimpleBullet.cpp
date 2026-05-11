// Fill out your copyright notice in the Description page of Project Settings.



// #include "Weapon/Bullet/SimpleBullet.h"
//
// #include "Attack/SimpleAttackComponent.h"
#include "Entity/Character/Weapon/Bullet/SimpleBullet.h"


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

	UE_LOG(LogTemp, Warning, TEXT("Bullet Ready"));

}

void ASimpleBullet::BulletSpawn(AActor* InOwner, FVector InDirection, float Damage)
{
	Super::BulletSpawn(InOwner, InDirection, Damage);
	
}

//TODO Owner 만들기


void ASimpleBullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
								   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
								   bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("bullet triggered"));

	
	if (OtherActor && OtherActor != GetInstigator() && OtherActor != this)
	{
		auto hitable = Cast<IHitable>(OtherActor);
		if (AttackBaseComponent == nullptr && hitable != nullptr)
		{
			AttackBaseComponent->HandleAttackOverlap(10, hitable, this);

			UE_LOG(LogTemp, Warning, TEXT("Bullet Overlap"));
			//TODO 관통처리?
			//삭제처리
			//Destroy();
		}
	}
}