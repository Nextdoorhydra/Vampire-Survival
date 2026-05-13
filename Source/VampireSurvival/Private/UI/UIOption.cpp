#include "UI/UIOption.h"
#include "Components/Button.h"
#include "CommonInputModeTypes.h"

void UUIOption::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (Btn_Close)
	{
		Btn_Close->OnClicked.AddDynamic(this, &UUIOption::OnCloseClicked);
	}
}

void UUIOption::OnCloseClicked()
{
	CloseUI();
}


TOptional<FUIInputConfig> UUIOption::GetDesiredInputConfig() const
{
	// ECommonInputMode::Menu -> 게임 조작(뷰포트)을 무시
	return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
}