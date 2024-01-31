#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OB_GameMode.generated.h"

UCLASS(minimalapi)
class AOB_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AOB_GameMode();

	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AOB_Tile>TileClass;
	
	FVector NextSpawnPoint;

	UFUNCTION()
	void SpawnTile();

	UFUNCTION()
	void TriggerSpawn(AOB_Tile* Tile);
};



