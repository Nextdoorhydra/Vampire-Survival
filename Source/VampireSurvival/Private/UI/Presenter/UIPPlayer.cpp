#include "Gamemode/VampireSurvivalGamemode.h"
#include "UI/Presenter/UIPPlayer.h"
#include "Entity/Character/PlayerCharacter.h"
#include "Component/HitableComponent.h"
#include "UI/UIPlayer.h"

void UUIPPlayer::Bind(APlayerCharacter* InPlayer, UUIPlayer* InUI)
{
	// 1. 유효성 검사 및 참조 저장
	if (!InPlayer || !InUI) return;

	PlayerModel = InPlayer;
	PlayerView = InUI;
	VSGamemodeModel = GetWorld()->GetAuthGameMode<AVampireSurvivalGamemode>();

	// 경험치 바인딩
	// PlayerCharacter의 FOnExpChangedDelegate(float, float) -> UUIPlayer의 OnExpChanged(float, float)
	PlayerModel->OnExpChangedDelegate.AddDynamic(PlayerView.Get(), &UUIPlayer::OnExpChanged);

	// 레벨업 바인딩
	// PlayerCharacter의 FOnLevelUpDelegate(int) -> UUIPlayer의 OnLevelChanged(int32)
	PlayerModel->OnLevelUpDelegate.AddDynamic(PlayerView.Get(), &UUIPlayer::OnLevelChanged);

	// 체력 바인딩
	PlayerModel->GetHitableComponent()->OnHPChangedEvent.AddDynamic(PlayerView.Get(), &UUIPlayer::OnHealthChanged);
	
	// 타이머 바인딩
	VSGamemodeModel->OnRunElapsedTimeChanged.AddDynamic(PlayerView.Get(), &UUIPlayer::OnTimerChanged);
}