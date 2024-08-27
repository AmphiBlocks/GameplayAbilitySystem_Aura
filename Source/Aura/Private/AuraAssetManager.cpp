// By Josh Rubenstein, built on a base of the Aura project by Stephen Ulibarri


#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"
#include "AbilitySystemGlobals.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	UAuraAssetManager* AssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAuraGameplayTags::InitializeNativeGameplayTags();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
