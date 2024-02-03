#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OB_EnemyBase.generated.h"

class AOB_Character;


UENUM(BlueprintType)
enum BaseStates : uint8
{
	IDLE UMETA(DisplayName="Idle"),
	CHASE UMETA(DisplayName="Chase"),
	ATTACK UMETA(DisplayName="Attack"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChangeState, BaseStates, NewState, AOB_Character*, Player);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);


UCLASS()
class OUTBANKS_API AOB_EnemyBase : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Mesh)
	class USphereComponent* TriggerChaseSphere;

	UPROPERTY(EditAnywhere, Category = Mesh)
	USphereComponent* TriggerAttackSphere;

	UPROPERTY(Instanced, EditAnywhere, BlueprintGetter=BPGetHealthComp, Category = Component)
	class UOB_HealthComp* HealthComp;

	UPROPERTY(EditAnywhere, BlueprintGetter=BPCurrentState, Category=State)
	TEnumAsByte<BaseStates> CurrentState;

	UFUNCTION()
	void OnTriggerChase(UPrimitiveComponent* OverlappedComponent,
					AActor* OtherActor, UPrimitiveComponent* OtherComp,
					int32 OtherBodyIndex, bool bFromSweep,
					const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndTriggerChase(UPrimitiveComponent* OverlappedComponent,
					AActor* OtherActor, UPrimitiveComponent* OtherComp,
					int32 OtherBodyIndex);

	UFUNCTION()
	void OnTriggerAttack(UPrimitiveComponent* OverlappedComponent,
					AActor* OtherActor, UPrimitiveComponent* OtherComp,
					int32 OtherBodyIndex, bool bFromSweep,
					const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndTriggerAttack(UPrimitiveComponent* OverlappedComponent,
					AActor* OtherActor, UPrimitiveComponent* OtherComp,
					int32 OtherBodyIndex);

	UFUNCTION()
	void Die();

public:
	AOB_EnemyBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeed = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DamageDone = 5;
	
	FTimerHandle TimerHandle;
	
	virtual void BeginPlay() override;

	void ApplyDamageToCharacter(AOB_Character* Ref) const;

	void ToDestroy() { Destroy(); }
	
	//UFUNCTION(BlueprintImplementableEvent)
	//void UpdateHealthHUD();

public:
	UFUNCTION(BlueprintCallable)
	UOB_HealthComp* BPGetHealthComp() const { return HealthComp; }
	
	UOB_HealthComp* GetHealthComp() const { return HealthComp; }

	UFUNCTION(BlueprintCallable)
	BaseStates BPCurrentState() const { return CurrentState; }
	
	BaseStates GetCurrentState() const { return CurrentState; }

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FChangeState OnStateChange;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FOnDeath OnDeath;
};