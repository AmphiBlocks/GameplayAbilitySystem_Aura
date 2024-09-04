// By Josh Rubenstein, built on a base of the Aura project by Stephen Ulibarri


#include "AbilitySystem/EQS/NoRepeatTargetsEnvQueryTest.h"
#include "Manager/AuraAbilityManager.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

UNoRepeatTargetsEnvQueryTest::UNoRepeatTargetsEnvQueryTest()
{
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_Actor::StaticClass();
    TestPurpose = EEnvTestPurpose::Filter;
}

void UNoRepeatTargetsEnvQueryTest::RunTest(FEnvQueryInstance& QueryInstance) const
{
    UObject* QuerierObject = QueryInstance.Owner.Get();
    if (AAuraAbilityManager* ChainLightningManager = Cast<AAuraAbilityManager>(QuerierObject))
    {
        for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
        {
            AActor* FoundActor = GetItemActor(QueryInstance, It.GetIndex());
            if (FoundActor)
            {
                if (!ChainLightningManager->AlreadyHitTargets.Contains(FoundActor)) {
                    It.SetScore(EEnvTestPurpose::Filter, EEnvTestFilterType::Match, 0, 0);
                }
                else {
                    It.SetScore(EEnvTestPurpose::Filter, EEnvTestFilterType::Minimum, 1, 1);
                }
            }
        }
    }

}