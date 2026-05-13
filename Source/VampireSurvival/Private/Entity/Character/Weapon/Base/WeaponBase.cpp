// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Character/Weapon/Base/WeaponBase.h"
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
		EAttachmentRule::KeepRelative, // Location: 부모를 따라다님 (상대 거리 유지)
		EAttachmentRule::KeepWorld,    // Rotation: 부모가 회전해도 무기는 회전하지 않음
		EAttachmentRule::KeepWorld,    // Scale: 부모 크기가 커져도 무기는 그대로
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