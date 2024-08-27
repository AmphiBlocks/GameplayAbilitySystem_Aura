// By Josh Rubenstein, built on a base of the Aura project by Stephen Ulibarri


#include "Player/AuraPlayerState.h"
#include <AbilitySystem/AuraAbilitySystemComponent.h>
#include <AbilitySystem/AuraAttributeSet.h>
#include "Net/UnrealNetwork.h"

class UAbilitySystemComponent;
class UAttributeSet;

AAuraPlayerState::AAuraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAuraPlayerState, level);
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraPlayerState::OnRep_Level(int32 OldLevel) const
{
	
}
