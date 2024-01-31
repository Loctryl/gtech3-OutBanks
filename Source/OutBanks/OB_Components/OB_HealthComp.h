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

public:
	UOB_HealthComp();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	int32 CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health)
	int32 MaxHealth;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
								FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ApplyDamage(int32 Amount);

	UFUNCTION(BlueprintCallable)
	void Heal(int32 Amount);

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() { return float(CurrentHealth) / float(MaxHealth); }

	UPROPERTY()
	FDeath DeathEvent;

	UPROPERTY()
	FUpdateHealth UpdateHealthEvent;
};
