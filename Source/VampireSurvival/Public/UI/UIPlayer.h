#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "UIPlayer.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class VAMPIRESURVIVAL_API UUIPlayer : public UUIBase
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnHealthChanged(float CurrentHealth, float MaxHealth);

	UFUNCTION()
	void OnExpChanged(float CurrentExp, float MaxExp);

	UFUNCTION()
	void OnLevelChanged(int32 NewLevel);
	
	UFUNCTION()
	void OnGoldChanged(int32 NewGold);
	
	UFUNCTION()
	void OnKillChanged(int32 NewKill);
	
	UFUNCTION()
	void OnTimerChanged(float NewTime);

protected:
	// UMG 에디터에서 동일한 이름으로 위젯을 생성해야 바인딩됩니다.
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* PB_Health;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* PB_Exp;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* Text_Level;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* Text_Gold;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* Text_Kill;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* Text_Timer;
};