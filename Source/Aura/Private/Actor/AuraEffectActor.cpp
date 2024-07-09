// Cat Cat Cat


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemInterface.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include <AbilitySystem/AuraAttributeSet.h>


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;
	
	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
	FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC );
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		if(InstantGameplayEffectClass != nullptr)
			ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
		for (TSubclassOf<UGameplayEffect> InstantGameplayEffectClass_i : InstantGameplayEffectClasses)
		{
			ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass_i);
		}
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		if (DurationGameplayEffectClass != nullptr)
			ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
		for (TSubclassOf<UGameplayEffect> DurationGameplayEffectClass_i : DurationGameplayEffectClasses)
		{
			ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass_i);
		}
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		if (InfiniteGameplayEffectClass != nullptr)
			ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
		for (TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass_i : InfiniteGameplayEffectClasses)
		{
			ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass_i);
		}
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
		for (TSubclassOf<UGameplayEffect> InstantGameplayEffectClass_i : InstantGameplayEffectClasses)
		{
			ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass_i);
		}
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
		for (TSubclassOf<UGameplayEffect> DurationGameplayEffectClass_i : DurationGameplayEffectClasses)
		{
			ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass_i);
		}
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
		for (TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass_i : InfiniteGameplayEffectClasses)
		{
			ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass_i);
		}
	}

	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (IsValid(TargetASC)) {

			TArray<FActiveGameplayEffectHandle> HandlesToRemove;
			for (auto& HandlePair : ActiveEffectHandles)
			{
				if (TargetASC == HandlePair.Value)
				{
					TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
					HandlesToRemove.Add(HandlePair.Key);
				}
			}
			for (auto& Handle : HandlesToRemove)
			{
				ActiveEffectHandles.FindAndRemoveChecked(Handle);
			}
		}
	}
}



