// Cat Cat Cat

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"

class UDamageTextComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class UAuraInputConfig;
class UAuraAbilitySystemComponent;
class USplineComponent;

class UMaterialInterface;
class ADecalActor;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

	void AutoRun();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMaterialInterface* SkillshotDecalMaterial;

	UPROPERTY()
	ADecalActor* SkillshotDecalActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector SkillshotDecalSize;

	FHitResult CursorHit;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Skillshot")
	void OnSkillshotIndicatorShow(FVector TargetLocation);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Skillshot")
	void OnSkillshotIndicatorHide();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Skillshot")
	void OnSkillshotIndicatorUpdate(FVector TargetLocation);

	UFUNCTION(BlueprintNativeEvent)
	void ShowDamageNumber(float DamageAmount, bool IsCritical, ACharacter* TargetCharacter);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ShiftAction;

	void ShiftPressed();
	void ShiftReleased();
	bool bShiftKeyDown = false;

	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();
	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;



	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetASC();

	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
};
