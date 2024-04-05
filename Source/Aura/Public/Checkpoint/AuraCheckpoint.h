// Hey yo

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "AuraCheckpoint.generated.h"

class USphereComponent;

/**
 * 
 */
UCLASS()
class AURA_API AAuraCheckpoint : public APlayerStart
{
	GENERATED_BODY()
	
public:
	AAuraCheckpoint(const FObjectInitializer& ObjectInitializer);

protected:
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void CheckpointReached(UMaterialInstanceDynamic* DynamicMaterialInstance);

	void HandleGlowEffects();

	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> CheckpointMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
};
