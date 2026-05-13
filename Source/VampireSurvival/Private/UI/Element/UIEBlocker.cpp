#include "UI/Element/UIEBlocker.h"

UUIEBlocker::UUIEBlocker(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// 이 위젯이 클릭되었을 때 UI 포커스를 게임으로 넘기지 않도록 강제
	SetIsFocusable(true);
}

FReply UUIEBlocker::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	OnBlockerClicked.Broadcast();

	// 포커스를 UI에게 유지
	return FReply::Handled().ReleaseMouseCapture();
}