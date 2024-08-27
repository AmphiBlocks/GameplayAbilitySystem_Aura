// By Josh Rubenstein, built on a base of the Aura project by Stephen Ulibarri


#include "UI/WidgetController/OverlayWidgetController.h"
#include <Player/AuraPlayerState.h>
#include <AbilitySystem/AuraAttributeSet.h>
#include <AbilitySystem/AuraAbilitySystemComponent.h>

void UOverlayWidgetController::BroadcastInitialValues()
{
	//UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(Cast<AAuraPlayerState>(this->PlayerState)->GetAttributeSet());
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data) {
				OnHealthChanged.Broadcast(Data.NewValue);
			}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data) {
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data) {
				OnManaChanged.Broadcast(Data.NewValue);
			}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data) {
				OnMaxManaChanged.Broadcast(Data.NewValue);
			}
		);
	/** 

	FGameplayAttribute AttributesToBind[] = { AuraAttributeSet->GetHealthAttribute(), AuraAttributeSet->GetMaxHealthAttribute(),
	AuraAttributeSet->GetManaAttribute(), AuraAttributeSet->GetMaxManaAttribute() };

	void* DelegatesToBindTo[] = { &OnHealthChanged, &OnMaxHealthChanged, &OnManaChanged, &OnMaxManaChanged };
 	FGameplayAttribute i_attribute = AttributesToBind[i];
	void* delegate_to_bind_to = DelegatesToBindTo[i];
	for (FGameplayAttribute i_attribute : AttributesToBind) {
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			i_attribute).AddLambda(
				[this, AuraAttributeSet](const FOnAttributeChangeData& Data) {
					OnAttributeChanged.Broadcast(Data.Attribute.AttributeName, Data.NewValue);
				}
			);
	}**/

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (auto Tag : AssetTags)
			{
				// tag = message.healthpotion
				// *"Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag)) {
					const FUIWidgetRow* WidgetRow = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*WidgetRow);
				}
			}
		}
	);
}