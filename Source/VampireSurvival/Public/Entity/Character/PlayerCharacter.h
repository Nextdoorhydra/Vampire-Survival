// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/Character/PlayerData.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h" 
#include "Entity/IHitable.h"
#include "PlayerCharacter.generated.h"

class AWeaponBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnExpChangedDelegate, float, CurrentExp, float, MaxExp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUpDelegate, int, Level);

class UInputMappingContext;
class UInputAction;
class UPlayerCameraComponent;
class UCameraComponent; 
class UHitableComponent;
class UInventoryComponent;

UCLASS()
class VAMPIRESURVIVAL_API APlayerCharacter : public ACharacter, public IHitable
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void TakeDamage(float Damage_, AActor* Attacker) override;

	UFUNCTION()
	virtual void Death() override;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void AddExp(float InExp);

	UFUNCTION(BlueprintCallable)
	void AddWeapon(TSubclassOf<AWeaponBase> weapon);
	
	UPROPERTY(BlueprintAssignable, Category = "Player|Events")
	FOnExpChangedDelegate OnExpChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Player|Events")
	FOnLevelUpDelegate OnLevelUpDelegate;
	
	TObjectPtr<UHitableComponent> GetHitableComponent();
	TObjectPtr<UInventoryComponent> GetInventoryComponent();
	
protected:

	void LevelUp();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Stats")
	FPlayerData PlayerData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Component")
	TObjectPtr<UHitableComponent> HitableComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Component")
	TObjectPtr<UInventoryComponent> InventoryComponent;
	
	//임시
	int MaxExp = 100;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;
	
	void Move(const FInputActionValue& Value);
	void LookAtMouse();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aim")
	FRotator AimRotation;
};