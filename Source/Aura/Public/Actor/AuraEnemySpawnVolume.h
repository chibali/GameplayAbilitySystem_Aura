// Hey yo

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/SaveInterface.h"
#include "AuraEnemySpawnVolume.generated.h"

class UBoxComponent;
class AAuraEnemySpawnPoint;

UCLASS()
class AURA_API AAuraEnemySpawnVolume : public AActor, public ISaveInterface
{
	GENERATED_BODY()
	
public:	
	AAuraEnemySpawnVolume();

	/*Begin SaveInterface*/
	virtual void LoadActor_Implementation() override;
	/*End SaveInterface*/

	UPROPERTY(BlueprintReadOnly, SaveGame)
	bool bReached = false;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	TArray<AAuraEnemySpawnPoint*> SpawnPoints;
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> Box;
};
