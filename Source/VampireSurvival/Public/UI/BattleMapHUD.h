#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameplayTagContainer.h"
#include "BattleMapHUD.generated.h"

class UUIRoot;
class UCommonActivatableWidget;

UCLASS()
class VAMPIRESURVIVAL_API ABattleMapHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "UI|Classes")
	TSubclassOf<UUIRoot> BattleRootClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI|Classes")
	TSubclassOf<UCommonActivatableWidget> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI|Tags")
	FGameplayTag MenuLayerTag;

	UPROPERTY(EditDefaultsOnly, Category = "UI|Classes")
	TSubclassOf<UCommonActivatableWidget> GameClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI|Tags")
	FGameplayTag GameLayerTag;
};