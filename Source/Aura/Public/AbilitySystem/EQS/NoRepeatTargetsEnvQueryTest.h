// By Josh Rubenstein, built on a base of the Aura project by Stephen Ulibarri

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "NoRepeatTargetsEnvQueryTest.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UNoRepeatTargetsEnvQueryTest : public UEnvQueryTest
{
	GENERATED_BODY()

public:
	UNoRepeatTargetsEnvQueryTest();

protected:
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
	
};
