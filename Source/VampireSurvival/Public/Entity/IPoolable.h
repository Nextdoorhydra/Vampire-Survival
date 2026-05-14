// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPoolable.generated.h"
/**
 * 
 */

UINTERFACE(MinimalAPI)

class UPoolable : public UInterface
{
	GENERATED_BODY()
};

class VAMPIRESURVIVAL_API IPoolable
{
	GENERATED_BODY()
	
public:
	virtual void GetFromPool()
		PURE_VIRTUAL(IPoolable::GetFromPool,);
	virtual void ReturnToPool()
		PURE_VIRTUAL(IPoolable::ReturnToPool,);
};
