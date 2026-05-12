#include "UI/MainMenuHUD.h"
#include "UI/UIRoot.h"
#include "UI/UIManager.h"
#include "Engine/LocalPlayer.h"

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = GetOwningPlayerController())
	{
		if (TitleRootClass)
		{
			UUIRoot* RootWidget = CreateWidget<UUIRoot>(PC, TitleRootClass);
			
			if (RootWidget)
			{
				RootWidget->AddToViewport();
				
				if (ULocalPlayer* LP = PC->GetLocalPlayer())
				{
					if (UUIManager* UIManager = LP->GetSubsystem<UUIManager>())
					{
						UIManager->PushWidget(MenuLayerTag, MainMenuClass);
					}
				}
			}
		}
	}
}