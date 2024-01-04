// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ABGASWidgetComponent.h"
#include "UI/ABGASUserWidget.h"

void UABGASWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UABGASUserWidget* GASUserWidget = Cast<UABGASUserWidget>(GetWidget());
	if (GASUserWidget)
	{
		GASUserWidget->SetAbilitySystemComponent(GetOwner());
	}
}
