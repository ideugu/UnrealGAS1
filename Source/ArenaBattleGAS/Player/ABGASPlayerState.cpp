// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ABGASPlayerState.h"
#include "AbilitySystemComponent.h"

AABGASPlayerState::AABGASPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	//ASC->SetIsReplicated(true);
}

UAbilitySystemComponent* AABGASPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}
