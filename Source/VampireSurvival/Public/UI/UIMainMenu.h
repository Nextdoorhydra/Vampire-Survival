#pragma once
#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "UIMainMenu.generated.h"

class UButton;

UCLASS()
class VAMPIRESURVIVAL_API UUIMainMenu : public UUIBase
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn_StartGame;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn_Option;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn_Quit;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UCommonActivatableWidget> OptionWidgetClass;
	
private:
	// 버튼 클릭 이벤트 바인딩을 위해 반드시 UFUNCTION() 필요
	UFUNCTION()
	void OnStartGameClicked();

	UFUNCTION()
	void OnOptionClicked();

	UFUNCTION()
	void OnQuitClicked();
};