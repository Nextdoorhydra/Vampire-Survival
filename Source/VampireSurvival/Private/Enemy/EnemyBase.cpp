#include "Enemy/EnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentHP = MaxHP; // 체력초기화

	TargetActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);  // 플레이어 찾기
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsDead)
	{
		return;
	}
	
	if (TargetActor == nullptr)
	{
		return;
	}
	
	FVector Direction = TargetActor->GetActorLocation() - GetActorLocation();
	Direction.Z = 0.f;
	Direction = Direction.GetSafeNormal();
	
	FVector NewLocation = GetActorLocation() + Direction * MoveSpeed * DeltaTime;
	SetActorLocation(NewLocation);
}

float AEnemyBase::TakeDamage(
	float DamageAmount,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser
)
{
	if (bIsDead)
	{
		return 0.f;
	}

	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage <= 0.f)
	{
		return 0.f;
	}

	CurrentHP -= ActualDamage;

	if (CurrentHP <= 0.f)
	{
		CurrentHP = 0.f;
		Die();
	}

	return ActualDamage;
}

void AEnemyBase::Die()
{
	if (bIsDead)
	{
		return;
	}

	bIsDead = true;

	Destroy();
}