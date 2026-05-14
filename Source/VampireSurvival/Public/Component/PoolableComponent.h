// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PoolableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VAMPIRESURVIVAL_API UPoolableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPoolableComponent();
	void SetPoolStatus(bool Status);
	bool GetPoolStatus() const;
	
protected:
	bool isIdle = true;
};
