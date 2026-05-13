// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/DropComponents.h"

// Sets default values for this component's properties
UDropComponents::UDropComponents()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UDropComponents::TryDropItem()
{
	if (dropItemClass == nullptr)
	{
		return;
	}

	AActor* Owner = GetOwner();

	if (Owner == nullptr)
	{
		return;
	}

	float RandomValue = FMath::FRand();

	if (RandomValue > dropChance)
	{
		return;
	}

	FVector spawnLocation = Owner->GetActorLocation();
	FRotator spawnRotation = FRotator::ZeroRotator;

	GetWorld()->SpawnActor<AActor>(
		dropItemClass,
		spawnLocation,
		spawnRotation
	);
}


