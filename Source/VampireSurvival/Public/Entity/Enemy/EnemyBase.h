#pragma once

#include "CoreMinimal.h"
#include "Entity/IHitable.h"
#include "GameFramework/Character.h"

#include "EnemyBase.generated.h"

class UHitableComponent;

UCLASS()
class VAMPIRESURVIVAL_API AEnemyBase : public ACharacter, public IHitable
{
	GENERATED_BODY()

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void TakeDamage(float Damage_, AActor* Attacker) override;
	virtual void Death() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|Component")
	TObjectPtr<UHitableComponent> HitableComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Stats")
	float MaxHP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Stats")
	float ContactDamage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Movement")
	float MoveSpeed = 300.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|Target")
	AActor* TargetActor = nullptr;
	
};
