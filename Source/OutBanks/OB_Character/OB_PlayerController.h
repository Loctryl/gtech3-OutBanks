// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OB_PlayerController.generated.h"

class AOB_Character;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

/**
 *
 */
UCLASS()
class OUTBANKS_API AOB_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;


	UPROPERTY(VisibleAnywhere)
	AOB_Character* CharacterRef;
	UPROPERTY(VisibleAnywhere)
	FVector CharacterForward;
	UPROPERTY(VisibleAnywhere)
	FVector CharacterRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input, meta=(UIMin="10.0", UIMax="90.0"))
	float ClampAngleX = 45;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input, meta=(UIMin="10.0", UIMax="90.0"))
	float ClampAngleY = 45;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input, meta=(UIMin="0.01", UIMax="5.0"))
	float SensibilityX = 0.5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input, meta=(UIMin="0.01", UIMax="5.0"))
	float SensibilityY = 0.5;

	
	// Begin Actor interface
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaSeconds) override;

	void Move(const FInputActionValue& Value);
	
	void Look(const FInputActionValue& Value);

	void Jump(const FInputActionValue& Value);
	
	void StopJump(const FInputActionValue& Value);
	// End Actor interface
public:
	void SetUpWeaponInputs();
};
