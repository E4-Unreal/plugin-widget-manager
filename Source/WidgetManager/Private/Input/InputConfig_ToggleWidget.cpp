// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfig_ToggleWidget.h"

#include "Components/WidgetManagerComponent.h"

void UInputConfig_ToggleWidget::OnTriggered_Implementation(APlayerController* PlayerController, const FInputActionInstance& InputActionInstance)
{
    Super::OnTriggered_Implementation(PlayerController, InputActionInstance);

    auto WidgetManagerComponent = bPlayerController ? PlayerController->GetComponentByClass<UWidgetManagerComponent>() : PlayerController->GetPawn()->GetComponentByClass<UWidgetManagerComponent>();
    if (WidgetManagerComponent) WidgetManagerComponent->ToggleWidget(WidgetClass, WidgetType);
}
