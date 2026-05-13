#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UEquipData;
class UEquipDatabase;

USTRUCT(BlueprintType)
struct FOwnedEquip
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UEquipData* EquipData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Level = 1;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnGetRandomLevelUpOptions,
	const TArray<UEquipData*>&,
	Options
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnOwnedEquipChanged,
	UEquipData*,
	EquipData,
	int32,
	NewLevel
);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VAMPIRESURVIVAL_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddOrLevelUpEquip(UEquipData* EquipData);

	bool HasEquip(UEquipData* EquipData) const;
	int32 GetEquipLevel(UEquipData* EquipData) const;
	bool IsEquipMaxLevel(UEquipData* EquipData) const;

	const TArray<FOwnedEquip>& GetOwnedEquips() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<UEquipData*> GetRandomLevelUpOptions();

	UPROPERTY(BlueprintAssignable, Category = "Inventory|Event")
	FOnGetRandomLevelUpOptions OnGetRandomLevelUpOptions;

	UPROPERTY(BlueprintAssignable, Category = "Inventory|Event")
	FOnOwnedEquipChanged OnOwnedEquipChanged;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TArray<FOwnedEquip> OwnedEquips;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UEquipDatabase* EquipDatabase = nullptr;
	
	void AddEquip(UEquipData* EquipData);
	void LevelUpEquip(UEquipData* EquipData);
};