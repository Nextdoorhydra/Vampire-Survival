#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UEquipData;

USTRUCT(BlueprintType)
struct FOwnedEquip
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UEquipData* EquipData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Level = 1;
};

class UEquipDatabase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VAMPIRESURVIVAL_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	void AddOrLevelUpEquip(UEquipData* EquipData);

	bool HasEquip(UEquipData* EquipData) const;
	int32 GetEquipLevel(UEquipData* EquipData) const;
	bool IsEquipMaxLevel(UEquipData* EquipData) const;

	const TArray<FOwnedEquip>& GetOwnedEquips() const;
	TArray<UEquipData*> GetRandomLevelUpOptions() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<FOwnedEquip> OwnedEquips;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UEquipDatabase* EquipDatabase = nullptr;
	
	void AddEquip(UEquipData* EquipData);
	void LevelUpEquip(UEquipData* EquipData);
};