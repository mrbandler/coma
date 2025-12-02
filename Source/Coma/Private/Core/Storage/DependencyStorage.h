// Copyright (c) fivefingergames GmbH. All rights reserved.

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"

#include "DependencyStorage.generated.h"

/** @brief	Context storage. */
UCLASS()
class UDependencyStorage final: public UObject {
    GENERATED_BODY()

public:
    void AddDependency(const FString& ComponentId, struct FDependency Dependency);
    void AddDependencies(const FString& ComponentId, TArray<struct FDependency>& DependenciesToAdd);

    TArray<struct FDependency> GetDependencies(const FString& ComponentId);

    void RemoveDependencies(const FString& ComponentId);

private:
    /** @brief	Map of all contexts. */
    TMap<FString, TSet<FDependency>> Dependencies;
};
