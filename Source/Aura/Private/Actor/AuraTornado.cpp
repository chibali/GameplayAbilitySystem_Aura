// Hey yo


#include "Actor/AuraTornado.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "TimerManager.h"

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
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &AAuraTornado::OnCapsuleOverlap);
}

void AAuraTornado::Destroyed()
{
	Super::Destroyed();
	TornadoEffect->Deactivate();
}

bool AAuraTornado::IsValidOverlap(AActor* OtherActor)
{
	if (DamageEffectParams.SourceAbilitySystemComponent == nullptr) return false;
	AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();
	if (SourceAvatarActor == OtherActor) return false;
	if (!UAuraAbilitySystemLibrary::IsNotAlly(SourceAvatarActor, OtherActor)) return false;

	return true;
}

void AAuraTornado::OnCapsuleOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*TO DO:
	*	- Set DamageEffects and Apply Radial Damage
	*	- Apply debuff "Pull":
	*		- When overlapping, enemies and objects will be attracted to the middle (Maybe add a SceneComponent to be the center pull object);
	*/

	if (HasAuthority())
	{
		if (!IsValidOverlap(OtherActor)) return;
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			/*const FVector DeathImpulse = GetActorForwardVector() * DamageEffectParams.DeathImpulseMagnitude;
			DamageEffectParams.DeathImpulse = DeathImpulse;

			FRotator Rotation = GetActorRotation();
			Rotation.Pitch = 45.f;

			const FVector KnockbackDirection = Rotation.Vector();
			const FVector Knockback = KnockbackDirection * DamageEffectParams.KnockbackMagnitude;
			DamageEffectParams.Knockback = Knockback;*/

			DamageEffectParams.TargetAbilitySystemComponent = TargetASC;
			if (!GetWorldTimerManager().IsTimerActive(DamageTimer))
			{
				GetWorldTimerManager().SetTimer(DamageTimer, DamageRate, false, DamageDelay);
				ApplyDamage();
			}
		}
	}
}

void AAuraTornado::ApplyDamage()
{
	UAuraAbilitySystemLibrary::ApplyDamageEffect(DamageEffectParams);
}

void AAuraTornado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

