// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Entity/Character/Weapon/Base/ProjectileWeaponBase.h"
#include "ThrowingDagger.generated.h"

class UCurveVector;
class UCurveFloat;

UCLASS()
class VAMPIRESURVIVAL_API AThrowingDagger : public AProjectileWeaponBase
{
	GENERATED_BODY()
	
public:
	AThrowingDagger();

protected:
	virtual void OnAttacking() override;

	UPROPERTY(EditAnywhere, Category = "Weapon|Spawn")
	TObjectPtr<UCurveVector> SpawnLocationCurve;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Spawn")
	TObjectPtr<UCurveFloat> SpawnTimingCurve;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats")
	int32 DaggerCount = 1;

private:
	FTransform GetRandomSpawnTransform() const;
};
