#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OB_HealthComp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateHealth);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OUTBANKS_API UOB_HealthComp : public UActorComponent
{
	GENERATED_BODY()

	FTimerHandle TimerHandle;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	int CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health)
	int MaxHealth;

public:
	UFUNCTION(BlueprintCallable, Category = Health)
	void ApplyDamage(int Amount);
	UFUNCTION(BlueprintCallable, Category = Health)
	void Heal(int Amount);

	
	UFUNCTION(BlueprintCallable, Category = Health)
	void DotDamage(float LoopTimer, int Amount);
	UFUNCTION(BlueprintCallable, Category = Health)
	void StopDotDamage();

	
	UFUNCTION(BlueprintCallable, Category = Health)
	float GetHealthPercent() const { return float(CurrentHealth) / float(MaxHealth); }

	UPROPERTY(BlueprintAssignable)
	FDeath DeathEvent;

	UPROPERTY(BlueprintAssignable)
	FUpdateHealth UpdateHealthEvent;
};