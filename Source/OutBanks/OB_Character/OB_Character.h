#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "OB_Character.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDeath);

UCLASS(config=Game)
class AOB_Character : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FPCameraComp;

	UPROPERTY(Instanced, VisibleAnywhere, BlueprintGetter=GetAmmoComp, Category = Component)
	class UOB_AmmoComp* AmmoComp;
	
	UPROPERTY(Instanced, VisibleAnywhere, BlueprintGetter=BPGetHealthComp, Category = Component)
	class UOB_HealthComp* HealthComp;

	UPROPERTY(VisibleAnywhere, BlueprintGetter=BPGetWeapon, Category = Weapon)
	class AOB_WeaponBase* WeaponHandle;

	UPROPERTY(VisibleAnywhere, BlueprintGetter=GetHasRifle, BlueprintSetter=SetHasRifle, Category = Weapon)
	bool bHasRifle;


protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnPickUpWeaponUpdateHUD();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateAmmoHUD();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthHUD();
	
	UFUNCTION()
	void OnDeath();

public:
	AOB_Character();
	
	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FPlayerDeath OnPlayerDeath;
	
	UFUNCTION(BlueprintCallable, Category=Weapon)
	void SetHasRifle(const bool NewHasRifle) { bHasRifle = NewHasRifle; }
	UFUNCTION(BlueprintCallable, Category=Weapon)
	bool GetHasRifle() const { return bHasRifle; }


	UFUNCTION(BlueprintCallable)
	UOB_HealthComp* BPGetHealthComp() const { return HealthComp; }
	
	UOB_HealthComp* GetHealthComp() const { return HealthComp; }

	UFUNCTION(BlueprintCallable, Category=Component)
	UOB_AmmoComp* GetAmmoComp() const { return AmmoComp; }


	// Function to interact with the weapon
	UFUNCTION(BlueprintCallable)
	AOB_WeaponBase* BPGetWeapon() const { return WeaponHandle; }
	AOB_WeaponBase* GetWeapon() const { return WeaponHandle; }
	
	void SetWeapon(AOB_WeaponBase* NewWeapon) { WeaponHandle = NewWeapon; }
	
	void PickUpWeapon(AOB_WeaponBase* WeaponPickUp);

	
	// Functions for pick up speed effect
	UFUNCTION(BlueprintCallable)
	void Speeder(float Timer, float Amount);
	UFUNCTION(BlueprintCallable)
	void IncreaseSpeed(float Amount);
	UFUNCTION(BlueprintCallable)
	void DecreaseSpeed(float Amount);
};