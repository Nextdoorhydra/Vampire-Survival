#include "Item/ExpOrb.h"
#include "Entity/Character/PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"

AExpOrb::AExpOrb()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;

	OrbMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrbMesh"));
	OrbMesh->SetupAttachment(SphereCollision);
	OrbMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SphereCollision->SetSphereRadius(200.0f);
	SphereCollision->SetCollisionProfileName(TEXT("Item"));
	SphereCollision->SetGenerateOverlapEvents(true);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AExpOrb::OnOrbOverlap);
}

void AExpOrb::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("ExpOrb Spawned"));
}

void AExpOrb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AExpOrb::OnOrbOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (OtherActor == nullptr)
	{
		return;
	}
	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(OtherActor);

	if (playerCharacter == nullptr)
	{
		return;
	}
	
	playerCharacter->AddExp(ExpValue);

	Destroy();
}