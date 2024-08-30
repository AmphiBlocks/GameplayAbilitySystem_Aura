// By Josh Rubenstein, built on a base of the Aura project by Stephen Ulibarri

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilityManager.generated.h"

/**
 * 
 */
class UEnvQuery;
struct FEnvQueryResult;

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
	
	UFUNCTION(BlueprintCallable)
	void SeekNextBounceTarget(int MaxBounces, float BounceRadius, UEnvQuery* EnemyEnvQuery);

	void NearbyTargetQueryFinished(TSharedPtr<FEnvQueryResult> Result);

	UFUNCTION(BlueprintImplementableEvent)
	void OnTargetChosen(AActor* ChosenTarget);
};
