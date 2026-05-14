// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PoolableComponent.h"

// Sets default values for this component's properties
UPoolableComponent::UPoolableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


bool UPoolableComponent::GetPoolStatus() const
{
	return isIdle;
}

void UPoolableComponent::SetPoolStatus(bool Status)
{
	isIdle = Status;
}
