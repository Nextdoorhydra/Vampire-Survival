// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABulletBase.h"
#include "Attack/AttackBaseComponent.h"
#include "Components/SphereComponent.h"

#include "GameFramework/Actor.h"
#include "SimpleBullet.generated.h"

UCLASS()
class VAMPIRESURVIVAL_API ASimpleBullet : public ABulletBase
{
	GENERATED_BODY()

public:
	ASimpleBullet();
	virtual void BeginPlay() override;

	virtual void BulletSpawn(AActor* InOwner, FVector InDirection, float Damage) override;
	UFUNCTION(BlueprintCallable, Category = "Combat|Projectile")
	void OnBulletOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	
	// 1. 충돌체
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> SphereComponent;

	// 2. 외형 (메쉬)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BulletMesh;
	
	// 3. 공격 로직 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UAttackBaseComponent> AttackBaseComponent;
};
