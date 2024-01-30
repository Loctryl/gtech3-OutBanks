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

	UFUNCTION()
	void OnDeath();

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

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	UOB_HealthComp* GetHealthComp() { return HealthComp; }

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FChangeState OnStateChange;
};
