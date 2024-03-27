// Hey yo


#include "Actor/AuraFireBall.h"

// Sets default values
AAuraFireBall::AAuraFireBall()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAuraFireBall::OnSphereOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AAuraFireBall::BeginPlay()
{
	Super::BeginPlay();
	StartOutgoingTimeline();
}


