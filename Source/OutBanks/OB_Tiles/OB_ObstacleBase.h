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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComp;

public:
	AOB_ObstacleBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
