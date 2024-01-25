// Copyright Epic Games, Inc. All Rights Reserved.

#include "OB_PlayerController.h"
#include <EnhancedInputComponent.h>
#include <Kismet/GameplayStatics.h>
#include "EnhancedInputSubsystems.h"
#include "OB_Character.h"


void AOB_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}

	CharacterRef = Cast<AOB_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	CharacterForward = CharacterRef->GetActorForwardVector();
	CharacterRight = CharacterRef->GetActorRightVector();
}

void AOB_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AOB_PlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AOB_PlayerController::StopJump);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOB_PlayerController::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AOB_PlayerController::Look);

		// Looking
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AOB_PlayerController::Look);
	}
}


void AOB_PlayerController::Tick(float DeltaSeconds)
{
	CharacterRef->AddMovementInput(CharacterForward);
}


void AOB_PlayerController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (CharacterRef->GetController() != nullptr)
	{
		// add movement 
		CharacterRef->AddMovementInput(CharacterRight, MovementVector.X);
	}
}

void AOB_PlayerController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (CharacterRef->GetController() != nullptr)
	{
		FRotator Rotator = GetControlRotation();
		Rotator.Yaw = FMath::ClampAngle(Rotator.Yaw + LookAxisVector.X * SensibilityX, -ClampAngleX, ClampAngleX);
		Rotator.Pitch = FMath::ClampAngle(Rotator.Pitch + LookAxisVector.Y * SensibilityY, -ClampAngleY, ClampAngleY);

		SetControlRotation(Rotator);
	}
}

void AOB_PlayerController::Jump(const FInputActionValue& Value)
{
	if (CharacterRef->GetController() != nullptr)
		CharacterRef->Jump();
	
}

void AOB_PlayerController::StopJump(const FInputActionValue& Value)
{
	if (CharacterRef->GetController() != nullptr)
		CharacterRef->StopJumping();
}
