#include "UI/UIInventory.h"
#include "UI/UIItem.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

void UUIInventory::InitializeItemList(const TArray<FOwnedEquip>& Items, int32 ItemsPerRow)
{
	if (!ItemGrid || !ItemWidgetClass)
	{
		return;
	}

	ItemGrid->ClearChildren();

	for (int32 i = 0; i < Items.Num(); ++i)
	{
		UUIItem* NewItem = CreateWidget<UUIItem>(this, ItemWidgetClass);
		if (NewItem)
		{
			NewItem->SetItemData(Items[i].EquipData, Items[i].Level);

			// 행(Row)과 열(Column) 계산 로직
			int32 Row = i / ItemsPerRow;
			int32 Column = i % ItemsPerRow;

			// 그리드에 자식으로 추가하고 슬롯 설정
			UUniformGridSlot* ItemSlot = ItemGrid->AddChildToUniformGrid(NewItem);
			if (ItemSlot)
			{
				ItemSlot->SetRow(Row);
				ItemSlot->SetColumn(Column);
			}
		}
	}
}
