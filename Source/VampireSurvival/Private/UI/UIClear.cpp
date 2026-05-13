#include "UI/UIClear.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UUIClear::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Btn_ReturnToTitle)
	{
		Btn_ReturnToTitle->OnClicked.AddDynamic(this, &UUIClear::OnReturnToTitleClicked);
	}
}

void UUIClear::OnReturnToTitleClicked()
{
	// 타이틀 레벨(메인 메뉴)로 씬 전환
	UGameplayStatics::OpenLevel(this, FName("MainMenuLevel"));
}