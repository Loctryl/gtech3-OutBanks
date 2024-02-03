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
	
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AOB_Tile>TileClass;
	
	FVector NextSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int KillCount = 0;

	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void SpawnTile();

	UFUNCTION()
	void TriggerSpawn(AOB_Tile* Tile);

	UFUNCTION()
	void IncreaseKillCount() { KillCount++; UpdateKillCount.Broadcast(); }
	
public:
	UPROPERTY(BlueprintAssignable)
	FUpdateKillCount UpdateKillCount;
};