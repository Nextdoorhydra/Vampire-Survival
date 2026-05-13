#include "UI/UIPlayer.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UUIPlayer::OnHealthChanged(float CurrentHealth, float MaxHealth)
{
	if (PB_Health && MaxHealth > 0.f)
	{
		// 0.0 ~ 1.0 사이의 비율로 프로그레스 바 업데이트
		PB_Health->SetPercent(CurrentHealth / MaxHealth);
	}
}

void UUIPlayer::OnExpChanged(float CurrentExp, float MaxExp)
{	
	if (PB_Exp && MaxExp > 0.f)
	{
		PB_Exp->SetPercent(CurrentExp / MaxExp);
	}
}

void UUIPlayer::OnLevelChanged(int32 NewLevel)
{
	if (Text_Level)
	{
		FText FormattedGold = FText::Format(FText::FromString(TEXT("Lv: {0}")), FText::AsNumber(NewLevel));
		Text_Gold->SetText(FormattedGold);
	}
}

void UUIPlayer::OnGoldChanged(int32 NewGold)
{
	if (Text_Gold)
	{
		FText FormattedGold = FText::Format(FText::FromString(TEXT("Gold: {0}")), FText::AsNumber(NewGold));
		Text_Gold->SetText(FormattedGold);
	}
}

void UUIPlayer::OnKillChanged(int32 NewKill)
{
	if (Text_Kill)
	{
		FText FormattedKill = FText::Format(FText::FromString(TEXT("Kills: {0}")), FText::AsNumber(NewKill));
		Text_Kill->SetText(FormattedKill);
	}
}

void UUIPlayer::OnTimerChanged(float NewTime)
{
	if (Text_Timer)
	{
		int32 TotalSeconds = FMath::FloorToInt(NewTime); // 소수점 버림
		int32 Minutes = TotalSeconds / 60;
		int32 Seconds = TotalSeconds % 60;

		FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);

		Text_Timer->SetText(FText::FromString(TimeString));
	}
}