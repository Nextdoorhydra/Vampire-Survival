// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Character/Weapon/Bullet/ABulletBase.h"

ABulletBase::ABulletBase()
{
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
}

