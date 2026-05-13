#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIEBlocker.generated.h"

// 블루프린트에서 사용할 수 있는 이벤트(델리게이트) 선언
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBlockerClickedSignature);

UCLASS(Abstract, Blueprintable, ClassGroup = UI, meta = (Category = "VS UI", DisableNativeTick))
class VAMPIRESURVIVAL_API UUIEBlocker : public UUserWidget
{
	GENERATED_BODY()

public:
	UUIEBlocker(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnBlockerClickedSignature OnBlockerClicked;

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};