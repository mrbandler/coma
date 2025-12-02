// Copyright (c) fivefingergames GmbH. All rights reserved.

#include "Core/Types/DependencyMetadata.h"

#include "Core/Types/Dependency.h"

FDependency FDependencyMetadata::ToDependency() const {
    FDependency Result;

    Result.DisplayName = DisplayName;
    Result.Class   = Component;
    Result.Type        = EDependencyType::Reflected;

    return Result;
}
