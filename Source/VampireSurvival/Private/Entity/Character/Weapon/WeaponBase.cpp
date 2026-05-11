// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Character/Weapon/WeaponBase.h"
// Sets default values
AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	//액터가 액터에 Attach 되나? ChildActor 써야하나?
	//TODO Attach to player
}

void AWeaponBase::Fire(FVector Direction)
{
	
}

void AWeaponBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (CurrentState)
	{
	case EWeaponState::Idle: OnIdle(DeltaSeconds); break;
	case EWeaponState::Attacking: OnAttacking(DeltaSeconds); break;
	case EWeaponState::Delay: OnDelay(DeltaSeconds); break;
	}
}


void AWeaponBase::OnIdle(float DeltaSeconds)
{
	//TODO : 임시로 비동기 처리를 핸들러로 구성함
	GetWorldTimerManager()
	.SetTimer(StateTimerHandle,
		FTimerDelegate::CreateUObject(this,
			&AWeaponBase::ChangeWeaponState, EWeaponState::Attacking), Delay, false);
}
void AWeaponBase::OnAttacking(float DeltaSeconds)
{
	GetWorldTimerManager()
	.SetTimer(StateTimerHandle,
		FTimerDelegate::CreateUObject(this,
			&AWeaponBase::ChangeWeaponState, EWeaponState::Delay), FireDelay, false);
}

void AWeaponBase::OnDelay(float DeltaSeconds)
{
	//비동기 함수
	GetWorldTimerManager()
	.SetTimer(StateTimerHandle,
		FTimerDelegate::CreateUObject(this,
			&AWeaponBase::ChangeWeaponState, EWeaponState::Attacking), Delay, false);
}

void AWeaponBase::ChangeWeaponState(const EWeaponState NewState)
{
	CurrentState = NewState;
}