#include "Entity/Enemy/EnemyBase.h"

#include "DataAsset/EnemyDataAsset.h"
#include "Component/HitableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	HitableComponent = CreateDefaultSubobject<UHitableComponent>(TEXT("HitableComponent"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	if (HitableComponent)
	{
		HitableComponent->Initialize(MaxHP);
		HitableComponent->OnDeathEvent.AddDynamic(this, &AEnemyBase::Death);
	}

	TargetActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetActor == nullptr)
	{
		return;
	}

	FVector Direction = TargetActor->GetActorLocation() - GetActorLocation();
	Direction.Z = 0.f;
	Direction = Direction.GetSafeNormal();

	if (!Direction.IsNearlyZero())
	{
		const FRotator TargetRotation = Direction.Rotation();
		SetActorRotation(FRotator(0.f, TargetRotation.Yaw, 0.f));
	}

	FVector NewLocation = GetActorLocation() + Direction * MoveSpeed * DeltaTime;
	SetActorLocation(NewLocation);
}

void AEnemyBase::TakeDamage(float Damage_, AActor* Attacker)
{
	// 피격시 넉백 처리 여기에 추가
	HitableComponent->AddHP(-Damage_);
}

void AEnemyBase::Death()
{
	Destroy();
}

void AEnemyBase::InitializeFromData(const UEnemyDataAsset* EnemyData)
{
	if (!EnemyData)
	{
		return;
	}

	EnemyName = EnemyData->DisplayName;
	MaxHP = EnemyData->BaseMaxHP;
	MoveSpeed = EnemyData->BaseMoveSpeed;
	ContactDamage = EnemyData->BaseDamage;

	if (HitableComponent)
	{
		HitableComponent->Initialize(MaxHP);
	}
	
}
