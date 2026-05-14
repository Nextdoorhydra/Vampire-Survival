// Fill out your copyright notice in the Description page of Project Settings.

#include "Entity/Character/PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "Component/HitableComponent.h"
#include "Equipment/Weapon/Base/WeaponBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/InventoryComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(RootComponent);
	FollowCamera->bUsePawnControlRotation = false;

	FollowCamera->SetUsingAbsoluteLocation(true);
	FollowCamera->SetUsingAbsoluteRotation(true);

	FollowCamera->SetWorldRotation(FRotator(-60.f, 0.f, 0.f));

	HitableComponent = CreateDefaultSubobject<UHitableComponent>(TEXT("HitableComponent"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void APlayerCharacter::TakeDamage(float Damage_, AActor* Attacker)
{
	HitableComponent->AddHP(-Damage_);
}

void APlayerCharacter::Death()
{
	//죽었을때 처리 ㄱㄱ
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		PlayerController->bShowMouseCursor = true;
	}

	if (HitableComponent)
	{
		HitableComponent->Initialize(PlayerData.MaxHP);
		HitableComponent->OnDeathEvent.AddDynamic(this, &APlayerCharacter::Death);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LookAtMouse();
	// 거리 800, 각도 -60도기준 계산 거리
	// X: 뒤로 400 (-800 * cos(60))
	// Z: 위로 692.82 (800 * sin(60))
	FVector CameraOffset = FVector(-400.f, 0.f, 692.82f);
	
	FollowCamera->SetWorldLocation(GetActorLocation() + CameraOffset);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		// EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	}
}

void APlayerCharacter::AddExp(float InExp)
{
	PlayerData.Exp += InExp;
	OnExpChangedDelegate.Broadcast(PlayerData.Exp, MaxExp);
	if (PlayerData.Exp < MaxExp) return;

	//경험치 한번에 많이 들어왔을때 로직 수정 필요
	
	LevelUp();
	PlayerData.Exp -= MaxExp;
	OnExpChangedDelegate.Broadcast(PlayerData.Exp, MaxExp);
}

void APlayerCharacter::AddWeapon(TSubclassOf<AWeaponBase> weapon)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;                        
	SpawnParams.Instigator = GetInstigator();         
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	auto NewWeapon = GetWorld()->SpawnActorDeferred<AWeaponBase>(weapon, GetTransform(), this);
	NewWeapon->Spawn(this);
}

TObjectPtr<UHitableComponent> APlayerCharacter::GetHitableComponent()
{
	return HitableComponent;
}

TObjectPtr<UInventoryComponent> APlayerCharacter::GetInventoryComponent()
{
	return InventoryComponent;
}

void APlayerCharacter::LevelUp()
{
	PlayerData.Level += 1;
	OnLevelUpDelegate.Broadcast(PlayerData.Level);
}


void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), MovementVector.Y);
		AddMovementInput(FVector(0.0f, 1.0f, 0.0f), MovementVector.X);
	}
}

void APlayerCharacter::LookAtMouse()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		FHitResult HitResult;
		if (PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
		{
			FVector TargetLocation = HitResult.ImpactPoint;
			TargetLocation.Z = GetActorLocation().Z;

			FRotator TargetRotation = (TargetLocation - GetActorLocation()).Rotation();

			GetCharacterMovement()->bOrientRotationToMovement = false;
			
			SetActorRotation(FRotator(0.f, TargetRotation.Yaw, 0.f));
		}
	}
}