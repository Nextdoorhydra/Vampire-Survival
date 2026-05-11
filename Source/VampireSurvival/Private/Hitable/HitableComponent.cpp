// Fill out your copyright notice in the Description page of Project Settings.


#include "Hitable/HitableComponent.h"


// Sets default values for this component's properties
UHitableComponent::UHitableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHitableComponent::Initialize(float InMaxHP)
{
	SetMaxHP(InMaxHP);
	CurrentHP = InMaxHP;
}

void UHitableComponent::SetMaxHP(float Amount)
{
	MaxHP = Amount; 
	OnHPChanged();
}

//TODO 최대체력 오를때, 현재 체력도 같이 올라야하나?
void UHitableComponent::AddMaxHP(float Amount)
{
	MaxHP += Amount; 
	OnHPChanged();
}


void UHitableComponent::SetHP(float Amount)
{
	CurrentHP = Amount;
	OnHPChanged();
}

void UHitableComponent::AddHP(float Amount)
{
	CurrentHP -= Amount;
	OnHPChanged();
}

void UHitableComponent::OnHPChanged()
{
	OnHPChangedEvent.Broadcast(CurrentHP, MaxHP);
	if (CurrentHP > MaxHP) CurrentHP = MaxHP;
	if (CurrentHP <= 0.0f) OnDeathEvent.Broadcast();
}




