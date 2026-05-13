// Fill out your copyright notice in the Description page of Project Settings.

#include "Entity/Character/Weapon/Base/ProjectileWeaponBase.h"
#include "Entity/Character/Weapon/Projectiles/ABulletBase.h"


// Sets default values
AProjectileWeaponBase::AProjectileWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectileWeaponBase::RequestBulletSpawn(FTransform SpawnTransform)
{
	//TODO 오브젝트 풀링 추가
	if (!BulletClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("BulletClass가 지정되지 않았습니다!"));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;                         // 이 무기가 주인임
	SpawnParams.Instigator = GetInstigator();         // 무기를 든 캐릭터가 가해자임
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // 일단 무조건 스폰

	//ABulletBase* NewBullet = GetWorld()->SpawnActor<ABulletBase>(BulletClass, SpawnTransform);
	ABulletBase* NewBullet = GetWorld()->SpawnActorDeferred<ABulletBase>(BulletClass, SpawnTransform, this);

	if (!NewBullet) return;
	NewBullet->BulletSpawn(this, Damage, KnockBack, 1.f);
	NewBullet->FinishSpawning(SpawnTransform);
}


