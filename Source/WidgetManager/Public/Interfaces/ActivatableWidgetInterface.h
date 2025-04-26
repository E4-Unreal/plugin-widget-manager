// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActivatableWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActivatableWidgetInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class WIDGETMANAGER_API IActivatableWidgetInterface
{
    GENERATED_BODY()

    // Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool IsActive();
    virtual bool IsActive_Implementation();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Activate();
    virtual void Activate_Implementation();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Deactivate();
    virtual void Deactivate_Implementation();
};
