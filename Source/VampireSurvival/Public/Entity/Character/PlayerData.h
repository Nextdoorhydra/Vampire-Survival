#pragma once
#include "CoreMinimal.h" 
#include "PlayerData.generated.h"

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Stats")
	float MaxHP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Stats")
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Stats")
	float AttackSpeed = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Stats")
	float Knockback = 10.f; 


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Stats")
	float ItemMagnetRange = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Stats")
	float Exp = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|Stats")
	float Level = 1.f;
};
