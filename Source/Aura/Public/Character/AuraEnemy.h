// Cat Cat Cat

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();

	/** Enemy Interface **/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/** Enemy Interface **/

	// combat interface
	virtual int32 GetPlayerLevel() override;

protected:
	virtual void BeginPlay();
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 level = 1;

};
