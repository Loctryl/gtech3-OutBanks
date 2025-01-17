﻿#pragma once

#include "CoreMinimal.h"
#include "OutBanks/OB_Enemies/OB_EnemyBase.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "OB_EnemyBaseController.generated.h"


UCLASS()
class OUTBANKS_API AOB_EnemyBaseController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY()
	class AOB_Character* PlayerToChase = nullptr;

	bool Chasing = false;

protected:
	UFUNCTION(BlueprintCallable)
	void OnPawnStateChange(BaseStates NewState, AOB_Character* Player);

public:
	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;
};