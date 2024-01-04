// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/TA/ABTA_SphereMultiTrace.h"
#include "ArenaBattleGAS.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Physics/ABCollision.h"
#include "DrawDebugHelpers.h"
#include "Attribute/ABCharacterSkillAttributeSet.h"

FGameplayAbilityTargetDataHandle AABTA_SphereMultiTrace::MakeTargetData() const
{
	ACharacter* Character = CastChecked<ACharacter>(SourceActor);

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);
	if (!ASC)
	{
		ABGAS_LOG(LogABGAS, Error, TEXT("ASC not found!"));
		return FGameplayAbilityTargetDataHandle();
	}

	const UABCharacterSkillAttributeSet* SkillAttribute = ASC->GetSet<UABCharacterSkillAttributeSet>();
	if (!SkillAttribute)
	{
		ABGAS_LOG(LogABGAS, Error, TEXT("SkillAttribute not found!"));
		return FGameplayAbilityTargetDataHandle();
	}

	TArray<FOverlapResult> Overlaps;
	const float SkillRadius = SkillAttribute->GetSkillRange();

	FVector Origin = Character->GetActorLocation();
	FCollisionQueryParams Params(SCENE_QUERY_STAT(AABTA_SphereMultiTrace), false, Character);
	GetWorld()->OverlapMultiByChannel(Overlaps, Origin, FQuat::Identity, CCHANNEL_ABACTION, FCollisionShape::MakeSphere(SkillRadius), Params);

	TArray<TWeakObjectPtr<AActor>> HitActors;
	for (const FOverlapResult& Overlap : Overlaps)
	{
		AActor* HitActor = Overlap.OverlapObjectHandle.FetchActor<AActor>();
		if (HitActor && !HitActors.Contains(HitActor))
		{
			HitActors.Add(HitActor);
		}
	}

	FGameplayAbilityTargetData_ActorArray* ActorsData = new FGameplayAbilityTargetData_ActorArray();
	ActorsData->SetActors(HitActors);

#if ENABLE_DRAW_DEBUG

	if (bShowDebug)
	{
		FColor DrawColor = HitActors.Num() > 0 ? FColor::Green : FColor::Red;
		DrawDebugSphere(GetWorld(), Origin, SkillRadius, 16, DrawColor, false, 5.0f);
	}

#endif

    return FGameplayAbilityTargetDataHandle(ActorsData);
}
