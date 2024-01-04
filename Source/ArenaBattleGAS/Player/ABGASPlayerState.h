// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "ABGASPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API AABGASPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AABGASPlayerState();
	
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY()
	TObjectPtr<class UABCharacterAttributeSet> AttributeSet;

	UPROPERTY()
	TObjectPtr<class UABCharacterSkillAttributeSet> SkillAttributeSet;
};
