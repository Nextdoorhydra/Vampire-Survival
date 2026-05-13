// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Character/Weapon/ProjectileObject/ABulletBase.h"

ABulletBase::ABulletBase()
{
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
}

void ABulletBase::BulletSpawn(AActor* InOwner, float InDamage, float InKnockBack, float InLifeTime)
{
	Damage = InDamage;
	KnockBack = InKnockBack;
	
	SetLifeSpan(InLifeTime);
}

