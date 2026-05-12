// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerData.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnExpChangedDelegate, float, CurrentExp, float, MaxExp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUpDelegate, int, Level);

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

	//임시데이터
	int MaxExp = 100;
};
