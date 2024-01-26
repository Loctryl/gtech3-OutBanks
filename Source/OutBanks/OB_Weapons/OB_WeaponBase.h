// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OB_WeaponBase.generated.h"


class UInputAction;
class UInputMappingContext;
class AOB_Character;


UCLASS()
class OUTBANKS_API AOB_WeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AOB_WeaponBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName WeaponName;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComp;

	UPROPERTY(VisibleAnywhere);
	class UBoxComponent* BoxComp;

	
	UPROPERTY(EditDefaultsOnly, Category=Shoot)
	TSubclassOf<class AOB_Projectile> ProjectileClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Shoot)
	USoundBase* FireSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shoot)
	UAnimMontage* FireAnimation;

	
	UPROPERTY()
	AOB_Character* CharacterRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector FireSpawnOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxAmmoInClip;
	
	

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void PlayAnimationAndSound();
	
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();

	UFUNCTION()
	FName GetWeaponName() const { return WeaponName; }

	UFUNCTION()
	int32 GetWeaponClipSize() const { return MaxAmmoInClip; }

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void OnTrigger(UPrimitiveComponent* OverlappedComponent,
						AActor* OtherActor,
						UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex,
						bool bFromSweep,
						const FHitResult& SweepResult
	);
};