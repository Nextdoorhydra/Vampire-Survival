// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "GameplayTagContainer.h"
#include "UIManager.generated.h"

// 전방 선언
class UCommonActivatableWidget;
class UCommonActivatableWidgetStack;

/*
 * UUIManager는 현재 활성화되어 있는 UI를 Stack으로 캐싱해서 네이게이트 시켜주는 클래스입니다.
 * UI를 새로 생성하거나, 삭제할 때 UIMnager의 public 메서드를 사용 해주세요.
 */
UCLASS()
class VAMPIRESURVIVAL_API UUIManager : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	// UI 레이어(스택)를 등록하는 함수 (UI Root 위젯에서 호출)
	void RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetStack* Stack);

	// 위젯을 특정 레이어에 띄우는 메인 함수
	UCommonActivatableWidget* PushWidget(FGameplayTag LayerTag, TSubclassOf<UCommonActivatableWidget> WidgetClass);
	
	// LayerTag인 위젯의 최신창(Top of stack)을 메모리에서 해제
	UCommonActivatableWidget* PopWidget(FGameplayTag LayerTag);
	
private:
	UPROPERTY()
	TMap<FGameplayTag, UCommonActivatableWidgetStack*> LayerMap;
};