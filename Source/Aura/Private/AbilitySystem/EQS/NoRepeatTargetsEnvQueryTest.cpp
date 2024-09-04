// By Josh Rubenstein, built on a base of the Aura project by Stephen Ulibarri


#include "AbilitySystem/EQS/NoRepeatTargetsEnvQueryTest.h"
#include "Manager/AuraAbilityManager.h"

UNoRepeatTargetsEnvQueryTest::UNoRepeatTargetsEnvQueryTest()
{

    TestPurpose = EEnvTestPurpose::Filter;
}

void UNoRepeatTargetsEnvQueryTest::RunTest(FEnvQueryInstance& QueryInstance) const
{
    UObject* QuerierObject = QueryInstance.Owner.Get();
    AAuraAbilityManager* ChainLightningManager = Cast<AAuraAbilityManager>(QuerierObject);
    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        AActor* FoundActor = Cast<AActor>(It.GetItemData());
         
        if (ChainLightningManager->AlreadyHitTargets.Contains(FoundActor)) {
            It.SetScore(EEnvTestPurpose::Filter, EEnvTestFilterType::Match, 0, 0);
        }
        else {
            It.SetScore(EEnvTestPurpose::Filter, EEnvTestFilterType::Minimum, 1, 1);
        }
    }
}