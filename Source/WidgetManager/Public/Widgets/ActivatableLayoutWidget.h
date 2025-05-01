// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Types/GameplayLayerTag.h"
#include "ActivatableLayoutWidget.generated.h"

class UCommonActivatableWidgetContainerBase;

/**
 *
 */
UCLASS()
class WIDGETMANAGER_API UActivatableLayoutWidget : public UCommonActivatableWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "State")
    TMap<FGameplayTag, TObjectPtr<UCommonActivatableWidgetContainerBase>> LayerMap;

private:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
    TObjectPtr<UCommonActivatableWidgetContainerBase> DefaultLayer;

public:
    virtual void NativePreConstruct() override;

    UFUNCTION(BlueprintCallable)
    virtual void AddWidget(TSubclassOf<UCommonActivatableWidget> ActivatableWidget, UPARAM(meta = (Categories = "UI.Layer")) const FGameplayTag& LayerTag = FGameplayTag());

    FORCEINLINE UCommonActivatableWidgetContainerBase* GetDefaultLayer() { return DefaultLayer; }

protected:
    UFUNCTION(BlueprintCallable)
    virtual void RegisterLayer(UPARAM(meta = (Categories = "UI.Layer")) const FGameplayTag& LayerTag, UCommonActivatableWidgetContainerBase* Container);

    UFUNCTION(BlueprintPure)
    UCommonActivatableWidgetContainerBase* GetLayer(UPARAM(meta = (Categories = "UI.Layer")) const FGameplayTag& LayerTag) const { return LayerMap.Contains(LayerTag) ? LayerMap[LayerTag] : DefaultLayer; }
};
