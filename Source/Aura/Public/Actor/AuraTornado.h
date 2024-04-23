// Hey yo

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraAbilityTypes.h"
#include "AuraTornado.generated.h"

class UCapsuleComponent;
class UNiagaraComponent;

UCLASS()
class AURA_API AAuraTornado : public AActor
{
	GENERATED_BODY()
	
public:	

	AAuraTornado();

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FDamageEffectParams DamageEffectParams;

	UFUNCTION(BlueprintImplementableEvent)
	void StartTornadoTimeline(float Lifespan);

	virtual void Tick(float DeltaTime) override;


protected:

	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> Capsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> TornadoMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraComponent> TornadoEffect;

	UFUNCTION()
	virtual void OnCapsuleOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TornadoLifespan = 5.f;
};
