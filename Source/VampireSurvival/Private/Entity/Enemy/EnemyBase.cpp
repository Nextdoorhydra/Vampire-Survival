#include "Entity/Enemy/EnemyBase.h"

#include "DataAsset/EnemyDataAsset.h"
#include "Component/HitableComponent.h"
#include "Component/SimpleAttackComponent.h"
#include "Components/SphereComponent.h"
#include "Entity/IHitable.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Collision sphere used to detect contact damage targets
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("EnemyAttackCol"));
	SphereComponent->SetupAttachment(RootComponent); 

	// Component that manages HP and death events
	HitableComponent = CreateDefaultSubobject<UHitableComponent>(TEXT("HitableComponent"));
	// Component that handles attack logic
	AttackComponent = CreateDefaultSubobject<USimpleAttackComponent>(TEXT("AttackComponent"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (SphereComponent)
	{
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnAttackBeginOverlap);
		SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AEnemyBase::OnAttackEndOverlap);
	}
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

	ApplyContactDamage(DeltaTime);

	if (TargetActor == nullptr)
	{
		return;
	}
	
	// Calculate movement direction toward the target
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

void AEnemyBase::OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this)
	{
		return;
	}

	if (!Cast<IHitable>(OtherActor))
	{
		return;
	}

	ContactDamageTargets.AddUnique(OtherActor);
}

void AEnemyBase::OnAttackEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ContactDamageTargets.Remove(OtherActor);
}

void AEnemyBase::ApplyContactDamage(float DeltaTime)
{
	if (!AttackComponent || ContactDamage <= 0.f || DeltaTime <= 0.f)
	{
		return;
	}

	// Apply damage over time to all overlapping valid targets
	for (int32 Index = ContactDamageTargets.Num() - 1; Index >= 0; --Index)
	{
		AActor* Target = ContactDamageTargets[Index];
		IHitable* Hitable = Cast<IHitable>(Target);
		if (!IsValid(Target) || !Hitable)
		{
			ContactDamageTargets.RemoveAtSwap(Index);
			continue;
		}

		AttackComponent->HandleAttackOverlap(ContactDamage * DeltaTime, Hitable, this);
	}
}
