// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity/Character/PlayerCharacter.h"
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void APlayerCharacter::AddExp(float InExp)
{
	PlayerData.Exp += InExp;
	OnExpChangedDelegate.Broadcast(PlayerData.Exp, MaxExp);
	if (PlayerData.Exp < MaxExp) return;

	//경험치 한번에 많이 들어왔을때 로직 수정 필요
	
	LevelUp();
	PlayerData.Exp -= MaxExp;
	OnExpChangedDelegate.Broadcast(PlayerData.Exp, MaxExp);
}

void APlayerCharacter::LevelUp()
{
	PlayerData.Level += 1;
	OnLevelUpDelegate.Broadcast(PlayerData.Level);
}
