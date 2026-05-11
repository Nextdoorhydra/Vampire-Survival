#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "UI/UITypes.h"

#include "UIBase.generated.h"


// 상태 변경을 외부에 알리기 위한 델리게이트 (옵저버 패턴)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUIStateChanged, EUIState, NewState);

UCLASS(Abstract)
class VAMPIRESURVIVAL_API UUIBase : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void CloseUI();
	
	// 외부(Presenter 등)에서 상태 변화를 구독할 수 있는 이벤트
	UPROPERTY(BlueprintAssignable, Category = "UI|Events")
	FOnUIStateChanged OnUIStateChanged;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	
	// 현재 UI의 상태
	UPROPERTY(BlueprintReadOnly, Category = "UI|State")
	EUIState CurrentState = EUIState::Hidden;
	
	// UMG에서 애니메이션 이름을 "UIAnim_Show", "UIAnim_Hide"로 지으면 자동 할당됨	
	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	class UWidgetAnimation* UIAnim_Show;

	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	class UWidgetAnimation* UIAnim_Hide;

	// 애니메이션이 끝났을 때 상태를 전이시키기 위한 콜백
	UFUNCTION()
	void OnShowAnimationFinished();

	UFUNCTION()
	void OnHideAnimationFinished();
};