// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity/Character/PlayerData.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h" 
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnExpChangedDelegate, float, CurrentExp, float, MaxExp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUpDelegate, int, Level);

class UInputMappingContext;
class UInputAction;
class UPlayerCameraComponent;
class UCameraComponent; 

UCLASS()
class VAMPIRESURVIVAL_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void AddExp(float InExp);

protected:

	void LevelUp();

	UPROPERTY(BlueprintAssignable, Category = "Player|Events")
	FOnExpChangedDelegate OnExpChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Player|Events")
	FOnLevelUpDelegate OnLevelUpDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Stats")
	FPlayerData PlayerData;

	//임시
	int MaxExp = 100;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	// UInputAction* LookAction;

	void Move(const FInputActionValue& Value);
	// void Look(const FInputActionValue& Value);
	void LookAtMouse();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aim")
	FRotator AimRotation;
};