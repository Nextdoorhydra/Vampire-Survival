#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameplayTagContainer.h"
#include "MainMenuHUD.generated.h"

class UUIRoot;
class UCommonActivatableWidget;

UCLASS()
class VAMPIRESURVIVAL_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	// 블루프린트에서 WBP_TitleRoot 할당
	UPROPERTY(EditDefaultsOnly, Category = "UI|Classes")
	TSubclassOf<UUIRoot> TitleRootClass;

	// 블루프린트에서 WBP_MainMenu 할당
	UPROPERTY(EditDefaultsOnly, Category = "UI|Classes")
	TSubclassOf<UCommonActivatableWidget> MainMenuClass;

	// 메인 메뉴를 띄울 대상 레이어 태그 (UI.Layer.Menu)
	UPROPERTY(EditDefaultsOnly, Category = "UI|Tags")
	FGameplayTag MenuLayerTag;
};