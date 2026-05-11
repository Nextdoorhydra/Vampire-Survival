#include "UI/UIRoot.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "UI/UIManager.h" 
#include "Engine/LocalPlayer.h"

void UUIRoot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// PlayerController를 통해 LocalPlayerSubsystem(UUIManager)에 접근
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
		{
			if (UUIManager* UIManager = LocalPlayer->GetSubsystem<UUIManager>())
			{
				// 유효한 태그와 스택이 존재할 경우 UIManager에 등록
				if (GameLayerStack && GameLayerTag.IsValid())
				{
					UIManager->RegisterLayer(GameLayerTag, GameLayerStack);
				}
				
				if (MenuLayerStack && MenuLayerTag.IsValid())
				{
					UIManager->RegisterLayer(MenuLayerTag, MenuLayerStack);
				}
				
				if (PopupLayerStack && PopupLayerTag.IsValid())
				{
					UIManager->RegisterLayer(PopupLayerTag, PopupLayerStack);
				}
			}
		}
	}
}