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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* TriggerChaseSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USphereComponent* TriggerAttackSphere;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	class UOB_HealthComp* HealthComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<BaseStates> CurrentState;

public:
	AOB_EnemyBase();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void Die();

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

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthHUD();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeed = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DamageDone = 5;
	
	FTimerHandle TimerHandle;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	UOB_HealthComp* GetHealthComp() { return HealthComp; }

	BaseStates GetCurrentState() const { return CurrentState; }

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FChangeState OnStateChange;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FOnDeath OnDeath;
};
