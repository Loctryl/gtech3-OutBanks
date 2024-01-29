#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OB_EnemyBase.generated.h"


UCLASS()
class OUTBANKS_API AOB_EnemyBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMeshComp;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	class UOB_HealthComp* HealthComp;

public:
	AOB_EnemyBase();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDeath();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthHUD();

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	UOB_HealthComp* GetHealthComp() { return HealthComp; }
};
