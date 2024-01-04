// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GA/TA/ABTA_Trace.h"
#include "ABTA_SphereMultiTrace.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API AABTA_SphereMultiTrace : public AABTA_Trace
{
	GENERATED_BODY()

protected:
	virtual FGameplayAbilityTargetDataHandle MakeTargetData() const override;
};
