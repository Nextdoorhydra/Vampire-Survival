// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EquipDatabase.generated.h"

class UEquipData;

UCLASS(BlueprintType)
class VAMPIRESURVIVAL_API UEquipDatabase : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equip")
	TArray<UEquipData*> LevelUpEquipPool;
	
};
