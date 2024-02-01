#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OB_GameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateKillCount);


UCLASS(minimalapi)
class AOB_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AOB_GameMode();

	UPROPERTY(BlueprintAssignable)
	FUpdateKillCount UpdateKillCount;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AOB_Tile>TileClass;
	
	FVector NextSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int KillCount = 0;

	UFUNCTION()
	void SpawnTile();

	UFUNCTION()
	void TriggerSpawn(AOB_Tile* Tile);

	UFUNCTION()
	void IncreaseKillCount() { KillCount++; UpdateKillCount.Broadcast(); }
};



