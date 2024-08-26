// Cat Cat Cat

#include "Manager/AuraAbilityManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/AuraEnemy.h"

void AAuraAbilityManager::Initialize(AActor* InitialTarget)
{
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
		TArray<AActor*>(),
		OverlappedActors // out
	);

	for (AActor* AlreadyHitTarget : AlreadyHitTargets) {
		OverlappedActors.RemoveSingle(AlreadyHitTarget);
	}

	OverlappedActors.Sort([BounceSourceLocation](const AActor& A, const AActor& B) -> bool
		{
			return FVector::DistSquared(A.GetActorLocation(), BounceSourceLocation) <
				FVector::DistSquared(B.GetActorLocation(), BounceSourceLocation);
		});

	if (OverlappedActors.Num() > 0) {
		AActor* NextTarget = OverlappedActors[0];
		//TODO: instead of the above, walk the array until we get to one with a clear line of sight

		AlreadyHitTargets.Add(NextTarget);
		return NextTarget;
	}

	return nullptr;
}
