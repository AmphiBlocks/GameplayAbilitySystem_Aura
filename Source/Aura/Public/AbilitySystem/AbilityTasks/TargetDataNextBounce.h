// Cat Cat Cat

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataNextBounce.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBounceTargetDataSigature, const FGameplayAbilityTargetDataHandle&, DataHandle);
/**
 * 
 */
UCLASS()
class AURA_API UTargetDataNextBounce : public UAbilityTask
{
public:
	GENERATED_BODY()
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "TargetDataNextBounce", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UTargetDataNextBounce* CreateTargetDataNextBounce(UGameplayAbility* OwningAbility, float Radius, int MaxBounces, TArray<AActor*> AlreadyHitTargets);
	
	UPROPERTY()
	TArray<AActor*> AlreadyHitTargets;

	float Radius = 0.f;

	int MaxBounces = 30;

	UPROPERTY(BlueprintAssignable)
	FBounceTargetDataSigature ValidData;

private:

	void SendNextBounceData();
};
