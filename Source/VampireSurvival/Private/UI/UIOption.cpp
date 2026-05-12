#include "UI/UIOption.h"
#include "Components/Button.h"

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