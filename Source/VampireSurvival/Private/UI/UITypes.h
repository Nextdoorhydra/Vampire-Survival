/*
 * UI모듈 내부에서만 참조하는 data types 헤더 파일입니다.
 */

#pragma once

// 가시성 상태 (Visible State)
UENUM(BlueprintType)
enum class EUIState : uint8
{
	Hidden,         // Disappeared
	Appearing,      // 등장 중
	Shown,          // Appeared (완전히 보임)
	Disappearing    // 퇴장 중
};