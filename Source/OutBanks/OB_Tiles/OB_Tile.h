#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "OB_Tile.generated.h"

class AOB_EnemyBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FExitTile, AOB_Tile*, Tile);


UCLASS()
class OUTBANKS_API AOB_Tile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	USceneComponent* SceneRootComp;

	UPROPERTY(EditAnywhere, Category=Mesh)
	UStaticMeshComponent* FloorMesh;

	UPROPERTY(EditAnywhere, Category=Mesh)
	UStaticMeshComponent* RightWallMesh;

	UPROPERTY(EditAnywhere, Category=Mesh)
	UStaticMeshComponent* LeftWallMesh;

	UPROPERTY(EditAnywhere, Category=Mesh)
	class UBoxComponent* EndTrigger;

	UPROPERTY(EditAnywhere, Category=Mesh)
	UBoxComponent* SpawnArea;

	UPROPERTY(EditAnywhere, Category=Mesh)
	class UArrowComponent* AttachPoint;


	TArray<AOB_EnemyBase*> Enemies;


public:
	AOB_Tile();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnEndTrigger(UPrimitiveComponent* OverlappedComponent,
						AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult);


	void SpawnEnemies(TSubclassOf<AActor> EnemyClass);

	void SpawnObstacles(TSubclassOf<AActor> ObsClass);
	
	void SpawnPickUps(TSubclassOf<AActor> PickUpClass);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ObstaclesOnTile = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PickUpOnTile = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EnemiesOnTile = 2;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>>ObstacleClasses;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>>PickUpClasses;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>>EnemiesClasses;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	FVector GetAttachPoint() { return AttachPoint->GetComponentLocation(); }

	void ToDestroy();

	UPROPERTY()
	FExitTile OnExitTile;
};
