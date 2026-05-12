// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Character/Weapon/WeaponBase.h"
// Sets default values
AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	//액터가 액터에 Attach 되나? ChildActor 써야하나?
	//TODO Attach to player
}


void AWeaponBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	ChangeWeaponState(EWeaponState::Idle);
}


void AWeaponBase::HandleIdleState()
{
	GetWorldTimerManager()
	.SetTimer(StateTimerHandle,
		FTimerDelegate::CreateUObject(this,
			&AWeaponBase::ChangeWeaponState, EWeaponState::Attacking), FireDelay, false);
}

void AWeaponBase::HandleAttackingState()
{
	OnAttacking();
}

void AWeaponBase::HandleDelayState()
{
	GetWorldTimerManager()
	.SetTimer(StateTimerHandle,
		FTimerDelegate::CreateUObject(this,
			&AWeaponBase::ChangeWeaponState, EWeaponState::Attacking), FireDelay, false);
}

void AWeaponBase::FinishAttack()
{
	ChangeWeaponState(EWeaponState::Delay);
}

void AWeaponBase::ChangeWeaponState(const EWeaponState NewState)
{
	// 기존에 돌아가던 타이머가 있다면 중단 (중복 실행 방지)
	GetWorldTimerManager().ClearTimer(StateTimerHandle);
	
	CurrentState = NewState;

	switch (CurrentState)
	{
	case EWeaponState::Idle:
		UE_LOG(LogTemp, Warning, TEXT("IDLE "));
		HandleIdleState();
		break;
	case EWeaponState::Attacking:
		UE_LOG(LogTemp, Warning, TEXT("ATTACKING "));
		HandleAttackingState();
		break;
	case EWeaponState::Delay:
		UE_LOG(LogTemp, Warning, TEXT("DELAY "));
		HandleDelayState();
		break;
	}
}