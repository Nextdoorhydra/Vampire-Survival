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

	virtual void BulletSpawn(AActor* InOwner, FVector InDirection, float Damage){}
	
protected:
	//life time
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> DefaultSceneRoot;
};
