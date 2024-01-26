// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "OB_Character.generated.h"

class AOB_WeaponBase;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UOB_AmmoComp;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AOB_Character : public ACharacter
{
	GENERATED_BODY()
	
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	UOB_AmmoComp* AmmoComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	AOB_WeaponBase* WeaponHandle;

protected:
	virtual void BeginPlay();

public:
	AOB_Character();
	
	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;
	
	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();
	
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UOB_AmmoComp* GetAmmoComponent() const { return AmmoComp; }

	UFUNCTION(BlueprintCallable)
	AOB_WeaponBase* GetWeapon() const { return WeaponHandle; }

	void SetWeapon(AOB_WeaponBase* NewWeapon) { WeaponHandle = NewWeapon; }

	UFUNCTION(BlueprintImplementableEvent)
	void PickUpWeapon();
};