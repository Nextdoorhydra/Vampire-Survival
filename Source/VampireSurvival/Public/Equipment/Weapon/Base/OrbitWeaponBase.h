// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "OrbitWeaponBase.generated.h"

class AOrbitObject;

UCLASS()
class VAMPIRESURVIVAL_API AOrbitWeaponBase : public AWeaponBase
{
	GENERATED_BODY()
	
protected:
	void CheckAndSpawnOrbitObject();
	void CreateOrbitObject();
	void SetOrbitObjectLocation();
	void SetDataToOrbitObject();
	void ToggleActiveOrbitObject(bool bInActive);

	TArray<TObjectPtr<AOrbitObject>> OrbitObjects;
    
	UPROPERTY(EditAnywhere, Category = "Weapon|Stats")
	TSubclassOf<AOrbitObject> OrbitClass;
	
	UPROPERTY(EditAnywhere, Category = "Weapon|Stats")
	int32 OrbitObjectCount = 3;
    
	UPROPERTY(EditAnywhere, Category = "Weapon|Stats")
	float OrbitFloatingDistance = 300;
};
