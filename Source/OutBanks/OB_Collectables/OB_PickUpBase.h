#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OB_PickUpBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickUp);

UCLASS()
class OUTBANKS_API AOB_PickUpBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere)
	class URotatingMovementComponent* RotatorComp;

public:
	AOB_PickUpBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	FOnPickUp OnPickUpEvent;
};
