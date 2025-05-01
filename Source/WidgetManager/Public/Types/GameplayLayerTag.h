// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayLayerTag.generated.h"

USTRUCT(BlueprintType)
struct FGameplayLayerTag
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "UI.Layer"))
    FGameplayTag Tag;

    FORCEINLINE bool IsValid() const { return Tag.IsValid(); }

    FORCEINLINE bool operator==(const FGameplayLayerTag& Other) const { return Tag == Other.Tag; }
    FORCEINLINE bool operator!=(const FGameplayLayerTag& Other) const { return !(*this == Other); }

    FORCEINLINE bool operator==(const FGameplayTag& Other) const { return Tag == Other; }
    FORCEINLINE bool operator!=(const FGameplayTag& Other) const { return !(*this == Other); }

    FORCEINLINE FGameplayLayerTag& operator=(const FGameplayTag& Other) { Tag = Other; return *this; }

    friend FORCEINLINE uint32 GetTypeHash(const FGameplayLayerTag& GameplayLayerTag) { return GetTypeHash(GameplayLayerTag.Tag); }
};
