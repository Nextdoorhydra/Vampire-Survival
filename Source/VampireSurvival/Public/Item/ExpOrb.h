#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExpOrb.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class VAMPIRESURVIVAL_API AExpOrb : public AActor
{
	GENERATED_BODY()
	
public:	
	AExpOrb();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void OnOrbOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

public:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereCollision;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* OrbMesh;
	
	UPROPERTY(EditAnywhere)
	int32 ExpValue = 1;
};