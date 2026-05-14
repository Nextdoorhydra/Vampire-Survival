#pragma once

#include "CoreMinimal.h"
#include "UIBase.h"
#include "Item/EquipData.h"
#include "UIItem.generated.h"

/**
 *
 */
UCLASS()
class VAMPIRESURVIVAL_API UUIItem : public UUIBase
{
	GENERATED_BODY()

public:
	// 유물 데이터를 설정하는 함수 (예: 이름, 아이콘 등)
	UFUNCTION(BlueprintNativeEvent, Category = "UI")
	void SetItemData(const UEquipData* Item, int32 Level);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_ItemNameText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_ItemLevelText;
};
