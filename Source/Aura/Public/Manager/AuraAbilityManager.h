// Cat Cat Cat

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilityManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class AURA_API AAuraAbilityManager : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void Initialize(AActor* InitialTarget);

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> AlreadyHitTargets;

	UFUNCTION(BlueprintCallable)
	AActor* ChooseNextBounceTarget(int MaxBounces, float BounceRadius);
};
