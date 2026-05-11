// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Attack/AttackBaseComponent.h"

#include "Hitable/IHitable.h"


// Sets default values
UAttackBaseComponent::UAttackBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAttackBaseComponent::HandleAttackOverlap(float Damage, IHitable* Hitable, AActor* Attacker)
{
	if (!Hitable) return;
	// 데미지 적용
	Hitable->TakeDamage(Damage, Attacker);

	UE_LOG(LogTemp, Warning, TEXT("In Component"));
	// 피격 이펙트 등 추가 처리...
}
