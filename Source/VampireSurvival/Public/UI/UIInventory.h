// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIBase.h"
#include "Item/InventoryComponent.h"
#include "UIInventory.generated.h"

class UUIItem;

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVAL_API UUIInventory : public UUIBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void InitializeItemList(const TArray<FOwnedEquip>& Items, int32 ItemsPerRow);
	
protected:
	// 에디터에서 배치한 UniformGridPanel과 변수명을 맞춰야 함
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* ItemGrid;

	// 생성할 아이템 위젯의 클래스 (에디터에서 설정)
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUIItem> ItemWidgetClass;
};
