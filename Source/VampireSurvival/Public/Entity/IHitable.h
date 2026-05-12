// HitReceiver.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IHitable.generated.h"


UINTERFACE(MinimalAPI)
class UHitable : public UInterface
{
	GENERATED_BODY()
};

class VAMPIRESURVIVAL_API IHitable
{
	GENERATED_BODY()

public:

	//TODO 버프, 디버프 등은 TakeBuff 등의 함수를 만들어서 처리해도 될듯?
	virtual void TakeDamage(float Damage, AActor* Attacker)
		PURE_VIRTUAL(IHitable::TakeDamage, );
	virtual void Death()
		PURE_VIRTUAL(IHitable::Death, );
};

