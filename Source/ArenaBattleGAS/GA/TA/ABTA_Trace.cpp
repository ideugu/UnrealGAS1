// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/TA/ABTA_Trace.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Physics/ABCollision.h"
#include "DrawDebugHelpers.h"
#include "AbilitySystemComponent.h"
#include "Attribute/ABCharacterAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "ArenaBattleGAS.h"

AABTA_Trace::AABTA_Trace()
{
}

void AABTA_Trace::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);

	SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
}

void AABTA_Trace::ConfirmTargetingAndContinue()
{
	if (SourceActor)
	{
		FGameplayAbilityTargetDataHandle DataHandle = MakeTargetData();
		TargetDataReadyDelegate.Broadcast(DataHandle);
	}
}

FGameplayAbilityTargetDataHandle AABTA_Trace::MakeTargetData() const
{
	ACharacter* Character = CastChecked<ACharacter>(SourceActor);

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);
	if (!ASC)
	{
		ABGAS_LOG(LogABGAS, Error, TEXT("ASC not found!"));
		return FGameplayAbilityTargetDataHandle();
	}

	const UABCharacterAttributeSet* AttributeSet = ASC->GetSet<UABCharacterAttributeSet>();
	if (!AttributeSet)
	{
		ABGAS_LOG(LogABGAS, Error, TEXT("ABCharacterAttributeSet not found!"));
		return FGameplayAbilityTargetDataHandle();
	}

	FHitResult OutHitResult;
	const float AttackRange = AttributeSet->GetAttackRange();
	const float AttackRadius = AttributeSet->GetAttackRadius();

	FCollisionQueryParams Params(SCENE_QUERY_STAT(UABTA_Trace), false, Character);
	const FVector Forward = Character->GetActorForwardVector();
	const FVector Start = Character->GetActorLocation() + Forward * Character->GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + Forward * AttackRange;

	bool HitDetected = GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, CCHANNEL_ABACTION, FCollisionShape::MakeSphere(AttackRadius), Params);

	FGameplayAbilityTargetDataHandle DataHandle;
	if (HitDetected)
	{
		FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit(OutHitResult);
		DataHandle.Add(TargetData);
	}

#if ENABLE_DRAW_DEBUG

	if (bShowDebug)
	{
		FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
		float CapsuleHalfHeight = AttackRange * 0.5f;
		FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;
		DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(Forward).ToQuat(), DrawColor, false, 5.0f);
	}

#endif

	return DataHandle;
}
