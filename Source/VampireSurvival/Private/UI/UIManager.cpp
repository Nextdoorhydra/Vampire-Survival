#include "UI/UIManager.h"
#include "UI/UIBase.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "GameplayTagContainer.h"

void UUIManager::RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetStack* Stack)
{
	if (Stack)
	{
		LayerMap.Add(LayerTag, Stack);
	}
}

UCommonActivatableWidget* UUIManager::PushWidget(FGameplayTag LayerTag, TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	if (UCommonActivatableWidgetStack** StackPtr = LayerMap.Find(LayerTag))
	{
		// CommonUI 스택에 위젯 추가 (자동으로 NativeOnActivated 호출됨)
		return (*StackPtr)->AddWidget(WidgetClass);
	}
	return nullptr;
}

UCommonActivatableWidget* UUIManager::PopWidget(FGameplayTag LayerTag)
{
	if (auto* StackPtr = LayerMap.Find(LayerTag))
	{
		if (UCommonActivatableWidgetStack* Stack = *StackPtr)
		{
			UCommonActivatableWidget* TopWidget = Stack->GetActiveWidget();
			
			if (TopWidget)
			{
				// UUIBase라면 애니메이션을 거쳐 닫히도록 CloseUI 호출
				if (UUIBase* BaseUI = Cast<UUIBase>(TopWidget))
				{
					BaseUI->CloseUI();
				}
				else
				{
					TopWidget->DeactivateWidget(); // DeactivateWidget 시 자동으로 스택에서 제거
				}
				return TopWidget;
			}			
		}
	}
	return nullptr;
}