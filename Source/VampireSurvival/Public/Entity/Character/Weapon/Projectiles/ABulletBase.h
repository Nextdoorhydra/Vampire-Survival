// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABulletBase.generated.h"

UCLASS(Abstract)
class VAMPIRESURVIVAL_API ABulletBase : public AActor
{
	GENERATED_BODY()

public:
	ABulletBase();

	virtual void BulletSpawn(AActor* InOwner, float InDamage, float InKnockBack, float InLifeTime);
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	float LifeTime = 1.f;
	float Damage = 0;
	float KnockBack = 0;
};
