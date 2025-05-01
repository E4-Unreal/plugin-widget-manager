// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/ActivatableLayoutWidget.h"

#include "WidgetManagerGameplayTags.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

using namespace WidgetManagerGameplayTags::UI;

void UActivatableLayoutWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    RegisterLayer(Layer::DefaultTag, DefaultLayer);
}

void UActivatableLayoutWidget::AddWidget(TSubclassOf<UCommonActivatableWidget> ActivatableWidget, const FGameplayTag& LayerTag)
{
    if (!ActivatableWidget) return;

    auto Layer = GetLayer(LayerTag);
    Layer->AddWidget(ActivatableWidget);
}

void UActivatableLayoutWidget::RegisterLayer(const FGameplayTag& LayerTag,
                                             UCommonActivatableWidgetContainerBase* Container)
{
    if (bool bCanRegister = LayerTag.IsValid() && !LayerMap.Contains(LayerTag) && Container; !bCanRegister) return;

    LayerMap.Emplace(LayerTag, Container);
}
