#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"
#include "UIRoot.generated.h"

class UCommonActivatableWidgetStack;

/**
 * 화면 최상단에 하나만 생성되며, 내부적으로 여러 UI 레이어(스택)를 가집니다.
 */
UCLASS(Abstract)
class VAMPIRESURVIVAL_API UUIRoot : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	// --- UI 레이어 스택 (UMG와 바인딩) ---
	// UMG 캔버스에 UCommonActivatableWidgetStack을 배치하고 변수명을 일치시켜야 합니다.
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCommonActivatableWidgetStack* GameLayerStack;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCommonActivatableWidgetStack* MenuLayerStack;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCommonActivatableWidgetStack* PopupLayerStack;

	// --- 레이어 태그 설정 ---
	// 에디터(블루프린트)에서 각 스택에 매칭할 GameplayTag를 지정합니다.
	UPROPERTY(EditDefaultsOnly, Category = "UI|Tags")
	FGameplayTag GameLayerTag;

	UPROPERTY(EditDefaultsOnly, Category = "UI|Tags")
	FGameplayTag MenuLayerTag;

	UPROPERTY(EditDefaultsOnly, Category = "UI|Tags")
	FGameplayTag PopupLayerTag;
};