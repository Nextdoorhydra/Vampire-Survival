// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Entity/Character/Weapon/Base/OrbitWeaponBase.h"
#include "Bible.generated.h"

class AOrbitObject;

UCLASS()
class VAMPIRESURVIVAL_API ABible : public AOrbitWeaponBase
{
	GENERATED_BODY()

public:
	ABible();

protected:
	virtual void BeginPlay() override;
	
	virtual void OnAttacking() override;
	virtual void FinishAttack() override;
	
	virtual void ApplyLevelSpec(int InLevel) override;
	
	UPROPERTY(VisibleAnywhere)
	class UTimelineComponent* OrbitTimeline;

	UPROPERTY(EditAnywhere, Category = "Weapon|Timeline")
	class UCurveFloat* OrbitRotationCurve;

	UPROPERTY(EditAnywhere, Category = "Weapon|Timeline")
	class UCurveFloat* OrbitScaleCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Stats")
	int32 RotationCount  = 3;
	
private:
	
	UFUNCTION()
	void UpdateOrbitScale(float timelineElapse);

	UFUNCTION()
	void UpdateOrbitRotation(float timelineElapse);
};
