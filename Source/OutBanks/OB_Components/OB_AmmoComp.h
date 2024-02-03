#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OB_AmmoComp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateAmmo);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OUTBANKS_API UOB_AmmoComp : public UActorComponent
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	bool Rambo;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentAmmoInClip;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxAmmoInClip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentAmmoInReserve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxAmmoInReserve;
	
	void SetRambo(const bool Value) { Rambo = Value; }

public:
	FUpdateAmmo UpdateAmmo;
	
	void SetMaxAmmoInClip(const int MaxAmmo) { MaxAmmoInClip = MaxAmmo; }
	
	UFUNCTION(BlueprintCallable)
	void Reload();

	UFUNCTION(BlueprintCallable)
	bool ShootOneAmmo();

	UFUNCTION(BlueprintCallable)
	void PickUpAmmo(int Amount);

	UFUNCTION(BlueprintCallable)
	void RamboTime(float Timer);
};
