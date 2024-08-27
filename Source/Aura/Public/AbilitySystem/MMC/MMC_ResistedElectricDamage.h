// By Josh Rubenstein, built on a base of the Aura project by Stephen Ulibarri

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_ResistedElectricDamage.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_ResistedElectricDamage : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_ResistedElectricDamage();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:

	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;
	FGameplayEffectAttributeCaptureDefinition ElectricResistDef;
};
