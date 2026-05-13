#include "UI/UIMainMenu.h"
#include "CommonInputModeTypes.h"
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

void UUIMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	// 초기에 UI에 포커스 고정
	// NativeOnInitialized ->  AddToViewport -> NativeConstruct
	if (Btn_StartGame)
		SetFocus();
	
	// // 최후의 수단 InputMode 쓰기
	// APlayerController* PC = GetOwningPlayer();
	// if (PC)
	// {
	// 	FInputModeUIOnly InputMode;
	// 	InputMode.SetWidgetToFocus(TakeWidget());
	// 	PC->SetInputMode(InputMode);
	// 	PC->bShowMouseCursor = true;
	// }
}

UWidget* UUIMainMenu::NativeGetDesiredFocusTarget() const
{	
	if (Btn_StartGame)
		return Btn_StartGame;
	else
	{
		return Super::NativeGetDesiredFocusTarget();
	}
}

TOptional<FUIInputConfig> UUIMainMenu::GetDesiredInputConfig() const
{
	// ECommonInputMode::Menu -> 게임 조작(뷰포트)을 무시
	return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
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