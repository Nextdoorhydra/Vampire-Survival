// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OrbitObject.h"
#include "SimpleOrbitObject.generated.h"

class UAttackBaseComponent;
class USphereComponent;

UCLASS()
class VAMPIRESURVIVAL_API ASimpleOrbitObject : public AOrbitObject
{
	GENERATED_BODY()

public:
	ASimpleOrbitObject();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Combat|Projectile")
	void OnOrbitOverlap(UPrimitiveComponent* OverlappedComponent,
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

private:

	UPROPERTY(EditAnywhere)
	float AttackInterval = 0.5f; // 동일 대상 공격 간격 (0.5초에 한 번)
};
