// Hey yo


#include "Actor/AuraTornado.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"

AAuraTornado::AAuraTornado()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(Capsule);
	Capsule->SetCollisionObjectType(ECC_WorldDynamic);
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Capsule->SetCollisionResponseToAllChannels(ECR_Ignore);
	Capsule->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Capsule->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	TornadoMesh = CreateDefaultSubobject<UStaticMeshComponent>("Tornado Mesh");
	TornadoMesh->SetupAttachment(GetRootComponent());

	TornadoEffect = CreateDefaultSubobject<UNiagaraComponent>("Tornado Effect");
	TornadoEffect->SetupAttachment(TornadoMesh);
	TornadoEffect->Deactivate();
}

void AAuraTornado::BeginPlay()
{
	Super::BeginPlay();
	TornadoEffect->Activate();
	//StartTornadoTimeline(TornadoLifespan);
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &AAuraTornado::OnCapsuleOverlap);
}

void AAuraTornado::Destroyed()
{
	Super::Destroyed();
	TornadoEffect->Deactivate();
}

void AAuraTornado::OnCapsuleOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*TO DO:
	*	- Set DamageEffects and Apply Radial Damage
	*	- Apply debuff "Pull":
	*		- When overlapping, enemies and objects will be attracted to the middle (Maybe add a SceneComponent to be the center pull object);
	*/
}

void AAuraTornado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

