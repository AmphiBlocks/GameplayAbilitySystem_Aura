// By Josh Rubenstein, built on a base of the Aura project by Stephen Ulibarri

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <UI/WidgetController/AuraWidgetController.h>
#include "AuraHUD.generated.h"

class UAuraUserWidget;
class UOverlayWidgetController;
class UAttributeMenuWidgetController;

/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	TObjectPtr<UAuraUserWidget> AttributeMenuWidget;

	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);

protected:

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};
