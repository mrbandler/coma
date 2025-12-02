// Copyright (c) fivefingergames GmbH. All rights reserved.

#pragma once

#include "DependencyInstance.generated.h"


/** @brief	Values that represent instance types. */
UENUM()
enum class EInstanceType : uint8 {
    None    = 0,
    Created = 1,
    Cached  = 2,
};

/** @brief	Dependency instance. */
USTRUCT()
struct FDependencyInstance {
    GENERATED_BODY()

    /** @brief	Instance. */
    class UActorComponent* Instance;

    /** @brief	Type of the instances. */
    EInstanceType Type;
};
