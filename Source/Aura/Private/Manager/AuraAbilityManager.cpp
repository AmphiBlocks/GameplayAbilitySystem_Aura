// By Josh Rubenstein, built on a base of the Aura project by Stephen Ulibarri

#include "Manager/AuraAbilityManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/AuraEnemy.h"

void AAuraAbilityManager::Initialize(AActor* InitialTarget)
{
	bReplicates = true;
	AlreadyHitTargets.Empty();
	AlreadyHitTargets.Add(InitialTarget);
}

AActor* AAuraAbilityManager::ChooseNextBounceTarget(int MaxBounces, float BounceRadius)
{
	if (AlreadyHitTargets.Num() >= MaxBounces) return nullptr;

	FVector BounceSourceLocation = AlreadyHitTargets[AlreadyHitTargets.Num() - 1]->GetActorLocation();

	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
	traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	UClass* seekClass = AAuraEnemy::StaticClass();

	TArray<AActor*> OverlappedActors;
	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		BounceSourceLocation,
		BounceRadius,
		traceObjectTypes,
		seekClass,
		AlreadyHitTargets,
		OverlappedActors // out
	);

	OverlappedActors.Sort([BounceSourceLocation](const AActor& A, const AActor& B) -> bool
		{
			return FVector::DistSquared(A.GetActorLocation(), BounceSourceLocation) <
				FVector::DistSquared(B.GetActorLocation(), BounceSourceLocation);
		});

	while (OverlappedActors.Num() > 0) {
		TArray<FHitResult> HitResults;

		AActor* NextTarget = OverlappedActors[0];
		if(!GetWorld()->LineTraceMultiByChannel(
			HitResults,
			BounceSourceLocation,
			NextTarget->GetActorLocation(),
			ECC_WorldStatic
		)){
			AlreadyHitTargets.Add(NextTarget);
			return NextTarget;
		}
		AActor* HitActor = HitResults[0].GetActor();
		OverlappedActors.RemoveAt(0);
	}

	return nullptr;
}
