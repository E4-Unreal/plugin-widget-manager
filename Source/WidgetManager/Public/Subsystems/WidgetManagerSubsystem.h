// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "WidgetManagerSubsystem.generated.h"

/**
 *
 */
UCLASS()
class WIDGETMANAGER_API UWidgetManagerSubsystem : public ULocalPlayerSubsystem
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    TMap<TSubclassOf<UUserWidget>, TObjectPtr<UUserWidget>> WidgetMap;

public:
    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

    UFUNCTION(BlueprintCallable)
    virtual void ShowWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void HideWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void ToggleWidget(TSubclassOf<UUserWidget> WidgetClass);

protected:
    virtual bool DoesWidgetExist(TSubclassOf<UUserWidget> WidgetClass) { return WidgetMap.Contains(WidgetClass); }

    virtual UUserWidget* GetOrCreateWidget(TSubclassOf<UUserWidget> WidgetClass);

    virtual void RegisterWidget(UUserWidget* Widget);

    virtual void UnRegisterWidget(UUserWidget* Widget);

    virtual bool IsActive(UUserWidget* Widget);

    virtual void ActivateWidget(UUserWidget* Widget);

    virtual void DeactivateWidget(UUserWidget* Widget);
};
