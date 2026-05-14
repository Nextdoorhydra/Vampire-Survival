// Fill out your copyright notice in the Description page of Project Settings.

#include "Equipment/Weapon/Base/OrbitWeaponBase.h"
#include "Equipment/Weapon/OrbitObject/OrbitObject.h"


void AOrbitWeaponBase::CheckAndSpawnOrbitObject()
{
	//필요한 만큼 생성
	auto requireSpawnCount = OrbitObjectCount - OrbitObjects.Num();

	if (requireSpawnCount > 0)
	{
		for (auto i = 0; i < requireSpawnCount; i++)
			CreateOrbitObject();
		SetOrbitObjectLocation();
	}
	
	SetDataToOrbitObject();
	ToggleActiveOrbitObject(true);
}

void AOrbitWeaponBase::CreateOrbitObject()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;                         // 이 무기가 주인임
	SpawnParams.Instigator = GetInstigator();         
	SpawnParams.SpawnCollisionHandlingOverride
		= ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // 일단 무조건 스폰

	auto NewOrbit = GetWorld()->SpawnActorDeferred<AOrbitObject>
		(OrbitClass, GetActorTransform(), this);

	if (!NewOrbit) return;
	NewOrbit->InjectData(Damage, KnockBack);
	NewOrbit->FinishSpawning(GetActorTransform());

	FAttachmentTransformRules AttachRules(
	EAttachmentRule::KeepRelative, 
	EAttachmentRule::KeepWorld,    
	EAttachmentRule::KeepWorld,    
	false                          
	);
	NewOrbit->AttachToActor(this, AttachRules);
	OrbitObjects.Add(NewOrbit);
}

void AOrbitWeaponBase::SetOrbitObjectLocation()
{
	if (OrbitObjectCount <= 0) return;

	// 1. 위성 간의 간격 각도 계산
	float AngleStep = 360.0f / OrbitObjects.Num();

	for (int32 i = 0; i < OrbitObjects.Num(); i++)
	{
		if (OrbitObjects[i] == nullptr) continue;

		float CurrentAngle = AngleStep * i;

		float Radians = FMath::DegreesToRadians(CurrentAngle);

		float X = FMath::Cos(Radians) * OrbitFloatingDistance;
		float Y = FMath::Sin(Radians) * OrbitFloatingDistance;

		FVector RelativeLocation = FVector(X, Y, 0.0f);
        
		OrbitObjects[i]->SetActorRelativeLocation(RelativeLocation);
	}
}

void AOrbitWeaponBase::SetDataToOrbitObject()
{
	for (auto OrbitObject : OrbitObjects)
		OrbitObject->InjectData(Damage, KnockBack);
}

void AOrbitWeaponBase::ToggleActiveOrbitObject(bool bInActive)
{
	for (auto OrbitObject : OrbitObjects)
	{
		if (!OrbitObject) continue;
		OrbitObject->SetActorHiddenInGame(!bInActive);
		OrbitObject->SetActorEnableCollision(bInActive);
		OrbitObject->SetActorTickEnabled(bInActive);
		
		if (!bInActive)
			OrbitObject->ClearHitCooldown();
	}
}
