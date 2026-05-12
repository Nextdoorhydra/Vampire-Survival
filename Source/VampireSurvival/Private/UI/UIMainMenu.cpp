#include "UI/UIMainMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h" 
#include "UI/UIManager.h"
#include "UI/UIOption.h"
#include "Engine/LocalPlayer.h"
#include "GameplayTagContainer.h" 

void UUIMainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Btn_StartGame) Btn_StartGame->OnClicked.AddDynamic(this, &UUIMainMenu::OnStartGameClicked);
	if (Btn_Option) Btn_Option->OnClicked.AddDynamic(this, &UUIMainMenu::OnOptionClicked);
	if (Btn_Quit) Btn_Quit->OnClicked.AddDynamic(this, &UUIMainMenu::OnQuitClicked);
}

void UUIMainMenu::OnStartGameClicked()
{
	// 인게임 레벨로 씬 전환 (맵 이름은 실제 프로젝트에 맞게 수정)
	UGameplayStatics::OpenLevel(this, FName("BattleMapLevel"));
}

void UUIMainMenu::OnOptionClicked()
{
	// 에디터에서 위젯이 잘 할당되었는지 확인
	if (!OptionWidgetClass) return;

	if (UUIManager* UIManager = GetOwningLocalPlayer()->GetSubsystem<UUIManager>())
	{
		FGameplayTag PopupTag = FGameplayTag::RequestGameplayTag(FName("UI.Layer.Popup"));
		UIManager->PushWidget(PopupTag, OptionWidgetClass);
	}
}

void UUIMainMenu::OnQuitClicked()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}