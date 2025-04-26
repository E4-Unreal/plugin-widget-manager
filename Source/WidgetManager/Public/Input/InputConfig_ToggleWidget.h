// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/InputConfigBase.h"
#include "InputConfig_ToggleWidget.generated.h"

class UInputAction;
class UUserWidget;

/**
 *
 */
UCLASS()
class WIDGETMANAGER_API UInputConfig_ToggleWidget : public UInputConfigBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    TMap<TObjectPtr<UInputAction>, TSubclassOf<UUserWidget>> ToggleWidgetMap;

protected:
    virtual TArray<UInputAction*> GetInputActions() const override;
    virtual void OnTriggered_Implementation(APlayerController* PlayerController, const FInputActionInstance& InputActionInstance) override;
};
