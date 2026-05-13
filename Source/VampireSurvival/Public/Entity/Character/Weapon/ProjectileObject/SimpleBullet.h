// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABulletBase.h"

#include "GameFramework/Actor.h"
#include "SimpleBullet.generated.h"

class UAttackBaseComponent;
class USphereComponent;

UCLASS()
class VAMPIRESURVIVAL_API ASimpleBullet : public ABulletBase
{
	GENERATED_BODY()

public:
	ASimpleBullet();
	virtual void BeginPlay() override;
	
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
