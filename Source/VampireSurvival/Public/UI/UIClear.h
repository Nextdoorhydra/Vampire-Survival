#pragma once
#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "UIClear.generated.h"

class UButton;

UCLASS()
class VAMPIRESURVIVAL_API UUIClear : public UUIBase
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn_ReturnToTitle;

private:	
	UFUNCTION() // OnClicked가 Dynamic delegate여서 매크로 붙임
	void OnReturnToTitleClicked();
};