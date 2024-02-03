#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OB_PlayerController.generated.h"

struct FInputActionValue;

UCLASS()
class OUTBANKS_API AOB_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* PauseAction;


	//Referenced vectors to get the running direction at the beginning
	UPROPERTY()
	class AOB_Character* CharacterRef;
	UPROPERTY()
	FVector CharacterForward;
	UPROPERTY()
	FVector CharacterRight;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(UIMin="10.0", UIMax="90.0"))
	float ClampAngleX = 45;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(UIMin="10.0", UIMax="90.0"))
	float ClampAngleY = 45;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(UIMin="0.01", UIMax="5.0"))
	float SensibilityX = 0.5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(UIMin="0.01", UIMax="5.0"))
	float SensibilityY = 0.5;

	
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaSeconds) override;

	void Move(const FInputActionValue& Value);
	
	void Look(const FInputActionValue& Value);

	void Jump(const FInputActionValue& Value);
	
	void StopJump(const FInputActionValue& Value);
	
public:
	void SetUpWeaponInputs();
};
