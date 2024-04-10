// Hey yo

#pragma once

#include "CoreMinimal.h"
#include "Checkpoint/AuraCheckpoint.h"
#include "MapEntrance.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AMapEntrance : public AAuraCheckpoint
{
	GENERATED_BODY()
public:
	AMapEntrance(const FObjectInitializer& ObjectInitializer);


	/*Save Interface*/
	virtual void LoadActor_Implementation() override;
	/*Save Interface*/

	/*Highlight Interface*/
	void HighlightActor_Implementation() override;
	/*Highlight Interface*/

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> DestinationMap;

	UPROPERTY(EditAnywhere)
	FName DestinationPlayerStartTag;

protected:
	
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
