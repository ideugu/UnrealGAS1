// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ABGASItemBox.h"
#include "ABGASWeaponBox.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API AABGASWeaponBox : public AABGASItemBox
{
	GENERATED_BODY()
	
protected:
	virtual void NotifyActorBeginOverlap(AActor* Other) override;

protected:
	UPROPERTY(EditAnywhere, Category = GAS, Meta=(Categories=Event))
	FGameplayTag WeaponEventTag;
};
