#include "UI/UIBase.h"
#include "Animation/WidgetAnimation.h" // UWidgetAnimation 제어를 위해 필수

void UUIBase::NativeOnInitialized()
{
	// 엔진의 기본 초기화 로직(입력 바인딩 등)
	Super::NativeOnInitialized();

	// 초기 상태 세팅(숨김)
	CurrentState = EUIState::Hidden;
}

void UUIBase::NativeOnActivated()
{
	// CommonUI의 활성화 로직 실행 (포커스 획득 등)
	Super::NativeOnActivated();

	// 애니메이션 실행
	CurrentState = EUIState::Appearing;
	OnUIStateChanged.Broadcast(CurrentState);

	if (UIAnim_Show)
	{
		// 애니메이션 재생 시작
		PlayAnimation(UIAnim_Show);
		
		FWidgetAnimationDynamicEvent EndEvent;
		EndEvent.BindDynamic(this, &UUIBase::OnShowAnimationFinished);
		BindToAnimationFinished(UIAnim_Show, EndEvent);
	}
	else
	{
		OnShowAnimationFinished();
	}
}

void UUIBase::NativeOnDeactivated()
{
	// Super::DeactivateWidget()이 호출되면 최종적으로 이 함수가 실행됩니다.
	Super::NativeOnDeactivated();

	// 상태를 완벽한 Hidden으로 변경
	CurrentState = EUIState::Hidden;
	OnUIStateChanged.Broadcast(CurrentState);
}

void UUIBase::OnShowAnimationFinished()
{	
	CurrentState = EUIState::Shown;
	OnUIStateChanged.Broadcast(CurrentState);
	
	// 연결한 delegate 해제
	if (UIAnim_Show)
	{
		UnbindAllFromAnimationFinished(UIAnim_Show);
	}
}

void UUIBase::OnHideAnimationFinished()
{
	// 연결한 delegate 해제
	if (UIAnim_Hide)
	{
		UnbindAllFromAnimationFinished(UIAnim_Hide);
	}

	DeactivateWidget(); // 내부에서 NativeOnActivated 호출됨
}

void UUIBase::CloseUI()
{
	if (CurrentState == EUIState::Disappearing || CurrentState == EUIState::Hidden) return;

	if (UIAnim_Hide)
	{
		CurrentState = EUIState::Disappearing;
		OnUIStateChanged.Broadcast(CurrentState);

		FWidgetAnimationDynamicEvent EndEvent;
		EndEvent.BindDynamic(this, &UUIBase::OnHideAnimationFinished);
		BindToAnimationFinished(UIAnim_Hide, EndEvent);
		PlayAnimation(UIAnim_Hide);
	}
	else
	{
		OnHideAnimationFinished();
	}
}