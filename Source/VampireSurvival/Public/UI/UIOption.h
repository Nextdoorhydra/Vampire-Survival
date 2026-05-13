#pragma once
#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "UIOption.generated.h"

class UButton;

UCLASS()
class VAMPIRESURVIVAL_API UUIOption : public UUIBase
{
	GENERATED_BODY()
public:
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	
protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn_Close;	
	
private:
	UFUNCTION()
	void OnCloseClicked();
};