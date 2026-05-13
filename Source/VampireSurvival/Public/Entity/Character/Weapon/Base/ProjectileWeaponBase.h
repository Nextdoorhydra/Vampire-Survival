// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "ProjectileWeaponBase.generated.h"

class ABulletBase;

UCLASS(Abstract)
class VAMPIRESURVIVAL_API AProjectileWeaponBase : public AWeaponBase
{
	GENERATED_BODY()

public:
	AProjectileWeaponBase();
	
	void RequestBulletSpawn(FTransform SpawnTransform);
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Bullet")
	TSubclassOf<ABulletBase> BulletClass;

	virtual void LookAt(){}

};
