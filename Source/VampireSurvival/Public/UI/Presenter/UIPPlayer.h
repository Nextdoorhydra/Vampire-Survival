#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UIPPlayer.generated.h"

class AVampireSurvivalGamemode;
class APlayerCharacter;
class UUIPlayer;

UCLASS(BlueprintType)
class VAMPIRESURVIVAL_API UUIPPlayer : public UObject
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Model(Character)과 View(UI)를 바인딩합니다.
	 * @param InPlayer 데이터를 제공할 모델 객체
	 * @param InUI 데이터를 출력할 뷰 객체
	 */
	UFUNCTION(BlueprintCallable, Category = "Presenter")
	void Bind(APlayerCharacter* InPlayer, UUIPlayer* InUI);
	
private:
	UPROPERTY()
	TObjectPtr<AVampireSurvivalGamemode> VSGamemodeModel;
	
	UPROPERTY()
	TObjectPtr<APlayerCharacter> PlayerModel;

	UPROPERTY()
	TObjectPtr<UUIPlayer> PlayerView;
};