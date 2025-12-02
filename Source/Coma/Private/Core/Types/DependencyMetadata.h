// Copyright (c) fivefingergames GmbH. All rights reserved.

#pragma once

#include "SubclassOf.h"

#include "DependencyMetadata.generated.h"

/** @brief	Dependency metadata. */
USTRUCT()
struct FDependencyMetadata {
    GENERATED_BODY()

    /** @brief	Name of the dependency class. */
    FString ClassName;

    /** @brief	Display name of the dependency; used inside blueprints. */
    FName DisplayName;

    /** @brief	Depended component */
    TSubclassOf<class UActorComponent> Component;

    /**
     * @brief	Converts this to a dependency.
     *
     * @returns	Converted dependency
     */
    struct FDependency ToDependency() const;
};
