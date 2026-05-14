#pragma once

#include "CoreMinimal.h"
#include "Entity/IHitable.h"
#include "Entity/IPoolable.h"
#include "GameFramework/Character.h"

#include "EnemyBase.generated.h"

class UEnemyDataAsset;
class UHitableComponent;
class UAttackBaseComponent;
class UPrimitiveComponent;
class USphereComponent;
class UPoolableComponent;

UCLASS()
class VAMPIRESURVIVAL_API AEnemyBase : public ACharacter, public IHitable, public IPoolable
{
	GENERATED_BODY()

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void TakeDamage(float Damage_, AActor* Attacker) override;

	UFUNCTION()
	virtual void Death() override;

	void InitializeFromData(const UEnemyDataAsset* EnemyData);
	
	
	// Pooling
	virtual void ReturnToPool() override;
	virtual void GetFromPool() override;

protected:
	UFUNCTION()
	void OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnAttackEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ApplyContactDamage(float DeltaTime);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|Component")
	TObjectPtr<UHitableComponent> HitableComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|Component")
	TObjectPtr<UAttackBaseComponent> AttackComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|Component")
	TObjectPtr<UPoolableComponent> PoolableComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|Component")
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|Data")
	FText EnemyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Stats")
	float MaxHP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Stats")
	float ContactDamage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy|Movement")
	float MoveSpeed = 300.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy|Target")
	AActor* TargetActor = nullptr;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> ContactDamageTargets;
	
};
