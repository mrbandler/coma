// Copyright (c) fivefingergames GmbH. All rights reserved.

#pragma once

#include "SubclassOf.h"

#include "Dependency.generated.h"

UENUM()
enum class EDependencyType : uint8 {
    None      = 0,
    Manual    = 1,
    Reflected = 2,
};

USTRUCT(BlueprintType)
struct COMA_API FDependency {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Coma")
    TSubclassOf<class UActorComponent> Class;

    UPROPERTY(BlueprintReadOnly, Category = "Coma")
    FName DisplayName;

    EDependencyType Type = EDependencyType::Manual;


    FORCEINLINE bool operator==(const FDependency& Other) const {
        return this->DisplayName == Other.DisplayName;
    }

    friend uint32 GetTypeHash(const FDependency& Other) {
        return GetTypeHash(Other.DisplayName);
    }
};
