#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OB_ObstacleBase.generated.h"


UCLASS()
class OUTBANKS_API AOB_ObstacleBase : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	USceneComponent* SceneRootComp;

	UPROPERTY(EditAnywhere, BlueprintGetter=BPGetMeshComp, Category=Mesh)
	UStaticMeshComponent* MeshComp;

public:
	AOB_ObstacleBase();

	UFUNCTION(BlueprintPure)
	UStaticMeshComponent* BPGetMeshComp() const { return MeshComp;}
};
