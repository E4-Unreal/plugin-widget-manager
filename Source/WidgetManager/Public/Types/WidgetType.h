// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetType.generated.h"

UENUM(BlueprintType)
enum class EWidgetType : uint8
{
    HUD, // Don't show mouse cursor.
    Main, // Mouse cursor should be shown and all sub widgets must be closed when main widget opened.
    Sub // Mouse cursor should be shown.
};
