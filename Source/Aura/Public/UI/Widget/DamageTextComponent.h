// By Josh Rubenstein, built on a base of the Aura project by Stephen Ulibarri

// By Josh Rubenstein, built on a base of the Aura project by Stephen Ulibarri


#pragma once
#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageTextComponent.generated.h"

/**
 *
 */
UCLASS()
class AURA_API UDamageTextComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetDamageText(float Damage, bool IsCritical);
};

