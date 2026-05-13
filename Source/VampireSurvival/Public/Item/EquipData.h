#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EquipData.generated.h"

UENUM(BlueprintType)
enum class EEquipType : uint8
{
	Weapon,
	Passive
};

USTRUCT(BlueprintType)
struct FEquipLevelData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equip")
	int32 AttackPowerIncrease = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equip")
	FText Description;
};

UCLASS(BlueprintType)
class VAMPIRESURVIVAL_API UEquipData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equip")
	FName EquipId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equip")
	FText EquipName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equip")
	EEquipType EquipType = EEquipType::Passive;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equip")
	int32 MaxLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equip")
	TArray<FEquipLevelData> LevelDataList;
	
};
