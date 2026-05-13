#include "UI/BattleMapHUD.h"
#include "UI/UIRoot.h"
#include "UI/UIManager.h"
#include "Engine/LocalPlayer.h"

void ABattleMapHUD::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = GetOwningPlayerController())
	{
		if (BattleRootClass)
		{
			UUIRoot* RootWidget = CreateWidget<UUIRoot>(PC, BattleRootClass);
			if (RootWidget)
			{
				RootWidget->AddToViewport();

				if (ULocalPlayer* LP = PC->GetLocalPlayer())
				{
					if (UUIManager* UIManager = LP->GetSubsystem<UUIManager>())
					{
						UIManager->PushWidget(GameLayerTag, GameClass);
					}
				}
			}
		}
	}
}