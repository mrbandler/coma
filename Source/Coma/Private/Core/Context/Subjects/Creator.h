// Copyright (c) fivefingergames GmbH. All rights reserved.

#pragma once

#include "Core/Context/ContextSubject.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Creator.generated.h"

/** @brief   Component creator; creates or retrieves dependency instances from/for the managed component. */
UCLASS()
class UCreator: public UContextSubject {
    GENERATED_BODY()

public:
    /**
     * @brief	Creates or retrieves (when cached) dependency instances.
     *
     * @param 	Dependencies	Dependencies to create
     *
     * @returns	New or cached dependency instances
     */
    TArray<struct FDependencyInstance> CreateOrRetrieveDependencyInstances(const TArray<struct FDependency>& Dependencies) const;

private:
    /**
     * @brief	Gets cached or creates.
     *
     * @param [in,out]	Owner	  	Managed component owner
     * @param 		   	Dependency	Dependency to create or retrieve cached instance from
     *
     * @returns	Cached or created dependency instance
     */
    struct FDependencyInstance GetCachedOrCreate(class AActor* Owner, const struct FDependency& Dependency) const;
};
