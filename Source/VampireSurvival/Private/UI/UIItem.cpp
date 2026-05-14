#include "UI/UIItem.h"

#include "Components/TextBlock.h"

void UUIItem::SetItemData_Implementation(const UEquipData* Item, int32 Level)
{
	if (!Item) return;

	if (Text_ItemNameText)
	{
		Text_ItemNameText->SetText(Item->EquipName);
	}

	if (Text_ItemLevelText)
	{
		FText LevelText = FText::Format(NSLOCTEXT("UI", "ItemLevel", "Lv.{0}"), FText::AsNumber(Level));
		Text_ItemLevelText->SetText(LevelText);
	}
}
