#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OB_Tile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FExitTile);


UCLASS()
class OUTBANKS_API AOB_Tile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneRootComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* FloorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RightWallMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LeftWallMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* EndTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* SpawnArea;

public:
	AOB_Tile();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnEndTrigger(UPrimitiveComponent* OverlappedComponent,
						AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult);

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	FExitTile OnExitTile;
};
