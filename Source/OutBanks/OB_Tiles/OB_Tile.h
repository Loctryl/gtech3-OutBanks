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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ObstaclesOnTile = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PickUpOnTile = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EnemiesOnTile = 2;

	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<AActor>, float>ObstacleClasses;
	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<AActor>, float>PickUpClasses;
	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<AActor>, float>EnemiesClasses;

	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnEndTrigger(UPrimitiveComponent* OverlappedComponent,
						AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult);


	void SpawnEnemies();

	void SpawnObstacles();
	
	void SpawnPickUps();

	TSubclassOf<AActor> GetClassInMapWithRate(TMap<TSubclassOf<AActor>, float> Map);


public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	FVector GetAttachPoint() const { return AttachPoint->GetComponentLocation(); }

	TArray<AOB_EnemyBase*> GetAllEnemies() { return Enemies; }

	void ToDestroy();

	UPROPERTY()
	FExitTile OnExitTile;
};
