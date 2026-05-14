// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Weapon/Base/WeaponBase.h"
// Sets default values
AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	DefaultSceneRoot->SetUsingAbsoluteRotation(true);
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

void AWeaponBase::Spawn(AActor* InOwner)
{
	FAttachmentTransformRules AttachRules(
		EAttachmentRule::KeepRelative, 
		EAttachmentRule::KeepWorld,    
		EAttachmentRule::KeepWorld,    
		false                          
	);
	
	SetOwner(InOwner);
	AttachToActor(InOwner, AttachRules);
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

void AWeaponBase::ApplyLevelSpec(int InLevel)
{
}

void AWeaponBase::ChangeWeaponState(const EWeaponState NewState)
{
	// 기존에 돌아가던 타이머가 있다면 중단 (중복 실행 방지)
	GetWorldTimerManager().ClearTimer(StateTimerHandle);
	
	CurrentState = NewState;

	switch (CurrentState)
	{
	case EWeaponState::Idle:
		HandleIdleState();
		break;
	case EWeaponState::Attacking:
		HandleAttackingState();
		break;
	case EWeaponState::Delay:
		HandleDelayState();
		break;
	}
}
