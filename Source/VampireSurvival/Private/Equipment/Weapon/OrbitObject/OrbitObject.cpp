#include "Equipment/Weapon/OrbitObject/OrbitObject.h"

AOrbitObject::AOrbitObject()
{
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
}

void AOrbitObject::InjectData(float InDamage, float InKnockBack)
{
	Damage = InDamage;
	KnockBack = InKnockBack;
}

void AOrbitObject::ClearHitCooldown()
{
	HitCooldownMap.Reset(); //메모리는 유지
	//HitCooldownMap.Empty(); //메모리까지 제거
}



