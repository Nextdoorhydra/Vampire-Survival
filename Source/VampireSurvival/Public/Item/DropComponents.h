// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DropComponents.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VAMPIRESURVIVAL_API UDropComponents : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDropComponents();
	
public:
	UFUNCTION(BlueprintCallable)
	void TryDropItem();

protected:
	UPROPERTY(EditAnywhere, Category = "Drop")
	TSubclassOf<AActor> dropItemClass;
	
	UPROPERTY(editAnywhere, Category = "Drop", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float dropChance  = 0.3f;
};
