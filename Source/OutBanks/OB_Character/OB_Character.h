#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "OB_Character.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDeath);

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AOB_Character : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FPCameraComp;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = Component, meta = (AllowPrivateAccess = "true"))
	class UOB_AmmoComp* AmmoComp;
	
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = Component, meta = (AllowPrivateAccess = "true"))
	class UOB_HealthComp* HealthComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class AOB_WeaponBase* WeaponHandle;


protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnPickUpWeaponUpdateHUD();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateAmmoHUD();

	UFUNCTION()
	void OnDeath();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthHUD();

public:
	AOB_Character();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FPlayerDeath OnPlayerDeath;
	
	
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(const bool NewHasRifle) { bHasRifle = NewHasRifle; }
	
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle() const { return bHasRifle; }
	
	UCameraComponent* GetFirstPersonCameraComponent() const { return FPCameraComp; }

	UFUNCTION()
	UOB_HealthComp* GetHealthComp() { return HealthComp; }

	UOB_AmmoComp* GetAmmoComponent() const { return AmmoComp; }
	
	AOB_WeaponBase* GetWeapon() const { return WeaponHandle; }
	void SetWeapon(AOB_WeaponBase* NewWeapon) { WeaponHandle = NewWeapon; }

	UFUNCTION()
	void PickUpWeapon(AOB_WeaponBase* WeaponPickUp);

	UFUNCTION(BlueprintCallable)
	void FlashTime(float Timer, float Amount);

	UFUNCTION(BlueprintCallable)
	void IncreaseSpeed(float Amount);
	UFUNCTION(BlueprintCallable)
	void DecreaseSpeed(float Amount);
};