#pragma once

#include "CoreMinimal.h"
#include "OutBanks/Enemies/OB_EnemyBase.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "OB_EnemyBaseController.generated.h"

class AOB_Character;


UCLASS()
class OUTBANKS_API AOB_EnemyBaseController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY()
	AOB_Character* PlayerToChase;

public:
	AOB_EnemyBaseController();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnPawnStateChange(BaseStates NewState, AOB_Character* Player);

public:
	virtual void Tick(float DeltaTime) override;
};
