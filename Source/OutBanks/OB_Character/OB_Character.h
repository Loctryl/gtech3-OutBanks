#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "OB_Character.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AOB_Character : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FPCameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	class UOB_AmmoComp* AmmoComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class AOB_WeaponBase* WeaponHandle;

protected:
	virtual void BeginPlay() override;

public:
	AOB_Character();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;
	
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(const bool NewHasRifle) { bHasRifle = NewHasRifle; }
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle() const { return bHasRifle; }
	
	UCameraComponent* GetFirstPersonCameraComponent() const { return FPCameraComp; }

	UOB_AmmoComp* GetAmmoComponent() const { return AmmoComp; }
	
	AOB_WeaponBase* GetWeapon() const { return WeaponHandle; }
	void SetWeapon(AOB_WeaponBase* NewWeapon) { WeaponHandle = NewWeapon; }

	UFUNCTION()
	void PickUpWeapon(AOB_WeaponBase* WeaponPickUp);

	UFUNCTION(BlueprintImplementableEvent)
	void OnPickUpWeaponUpdateHUDWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHUDWidget();
};