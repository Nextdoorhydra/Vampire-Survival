// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AttackBaseComponent.generated.h"

class IHitable;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackDelegate, float, Damage);

UCLASS(Abstract)
class VAMPIRESURVIVAL_API UAttackBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAttackBaseComponent();

	void HandleAttackOverlap(float Damage, IHitable* Hitable, AActor* Attacker);
	
};
