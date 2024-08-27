// By Josh Rubenstein, built on a base of the Aura project by Stephen Ulibarri

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
class UAbilitySystemComponent;

UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
	
public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	virtual int32 GetPlayerLevel() override;

private:
	virtual void InitAbilityActorInfo() override;
};
