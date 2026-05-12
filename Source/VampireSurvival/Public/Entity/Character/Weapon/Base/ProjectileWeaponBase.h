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

	//TODO : 마우스 방향으로 바라보게 할 필요 있음.
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Bullet")
	TSubclassOf<ABulletBase> BulletClass; 
};
