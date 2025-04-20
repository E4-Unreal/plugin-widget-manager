// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/InputConfig.h"
#include "Types/WidgetType.h"
#include "InputConfig_ToggleWidget.generated.h"

/**
 *
 */
UCLASS()
class WIDGETMANAGER_API UInputConfig_ToggleWidget : public UInputConfig
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    TSubclassOf<UUserWidget> WidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    EWidgetType WidgetType = EWidgetType::HUD;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    bool bPlayerController;

protected:
    virtual void OnTriggered_Implementation(APawn* Pawn, APlayerController* PlayerController, const FInputActionValue& InputActionValue) override;
};
