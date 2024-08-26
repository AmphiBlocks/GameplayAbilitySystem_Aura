// Cat Cat Cat


#include "AbilitySystem/MMC/MMC_ResistedElectricDamage.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include <Character/AuraCharacterBase.h>

UMMC_ResistedElectricDamage::UMMC_ResistedElectricDamage()
{
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	IntelligenceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDef);

	ElectricResistDef.AttributeToCapture = UAuraAttributeSet::GetResilienceAttribute();
	ElectricResistDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ElectricResistDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(ElectricResistDef);
}

float UMMC_ResistedElectricDamage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Intelligence = 0.0f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluationParameters, Intelligence);
	Intelligence = FMath::Max<float>(Intelligence, 0.f);

	float ElecResist = 0.0f;
	GetCapturedAttributeMagnitude(ElectricResistDef, Spec, EvaluationParameters, ElecResist);
	ElecResist = FMath::Max<float>(ElecResist, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 80.f + 2.5f * Intelligence/ElecResist + 10.f;

}
