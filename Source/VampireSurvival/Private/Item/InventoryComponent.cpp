// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/InventoryComponent.h"
#include "Item/EquipDatabase.h"
#include "Item/EquipData.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::AddOrLevelUpEquip(UEquipData* EquipData)
{
	if (EquipData == nullptr)
		return;

	if (HasEquip(EquipData))
		LevelUpEquip(EquipData);
	else
		AddEquip(EquipData);
}

void UInventoryComponent::AddEquip(UEquipData* EquipData)
{
	if (EquipData == nullptr)
		return;
	FOwnedEquip NewEquipData;
	NewEquipData.EquipData = EquipData;
	NewEquipData.Level = 1;

	OwnedEquips.Add(NewEquipData);
	
	OnOwnedEquipChanged.Broadcast(EquipData, NewEquipData.Level);
}

void UInventoryComponent::LevelUpEquip(UEquipData* EquipData)
{
	if (EquipData == nullptr)
		return;

	for (FOwnedEquip& OwnedEquip : OwnedEquips)
	{
		if (OwnedEquip.EquipData == EquipData)
		{
			if (OwnedEquip.Level >= EquipData->MaxLevel)
				return;
			
			OwnedEquip.Level++;
			
			OnOwnedEquipChanged.Broadcast(EquipData, OwnedEquip.Level);
			
			return;
		}
	}
 
}

bool UInventoryComponent::HasEquip(UEquipData* EquipData) const
{
	if (EquipData == nullptr)
		return false;
	
	for (const FOwnedEquip& OwnedEquip : OwnedEquips)
	{
		if (OwnedEquip.EquipData == EquipData)
			return true;
	}
	return false;
}

int32 UInventoryComponent::GetEquipLevel(UEquipData* EquipData) const
{
	if (EquipData == nullptr)
		return 0;
	
	for (const FOwnedEquip& OwnedEquip : OwnedEquips)
	{
		if (OwnedEquip.EquipData == EquipData)
			return OwnedEquip.Level;
	}
	
	return 0;
}

TArray<UEquipData*> UInventoryComponent::GetRandomLevelUpOptions()
{
	TArray<UEquipData*> Candidates;
	TArray<UEquipData*> Result;

	if (EquipDatabase == nullptr)
	{
		OnGetRandomLevelUpOptions.Broadcast(Result);
		return Result;
	}

	for (UEquipData* EquipData : EquipDatabase->LevelUpEquipPool)
	{
		if (EquipData == nullptr)
			continue;

		if (!HasEquip(EquipData))
		{
			Candidates.Add(EquipData);
			continue;
		}

		if (!IsEquipMaxLevel(EquipData))
		{
			Candidates.Add(EquipData);
		}
	}

	while (Result.Num() < 3 && Candidates.Num() > 0)
	{
		const int32 RandomIndex = FMath::RandRange(0, Candidates.Num() - 1);

		Result.Add(Candidates[RandomIndex]);
		Candidates.RemoveAt(RandomIndex);
	}

	OnGetRandomLevelUpOptions.Broadcast(Result);

	return Result;
}

bool UInventoryComponent::IsEquipMaxLevel(UEquipData* EquipData) const
{
	if (EquipData == nullptr)
		return false;
	for (const FOwnedEquip& OwnedEquip : OwnedEquips)
	{
		if (OwnedEquip.EquipData == EquipData)
			return OwnedEquip.Level >= EquipData->MaxLevel;
	}
	return false;
}

const TArray<FOwnedEquip>& UInventoryComponent::GetOwnedEquips() const
{
	return OwnedEquips;
}

