// Fill out your copyright notice in the Description page of Project Settings.

#include "Entity/Character/PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bDoCollisionTest = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
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
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LookAtMouse();
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

/*
void APlayerCharacter::Look(const FInputActionValue& Value)
{
	LookAtMouse();
}
*/

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