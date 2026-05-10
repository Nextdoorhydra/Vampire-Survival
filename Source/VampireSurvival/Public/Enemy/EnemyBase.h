#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class VAMPIRESURVIVAL_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Stats")
	float MaxHP = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|Stats")
	float CurrentHP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Stats")
	float ContactDamage = 10.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|State")
	bool bIsDead = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Movement")
	float MoveSpeed = 300.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|Target")
	AActor* TargetActor = nullptr;

protected:
	void Die();
};