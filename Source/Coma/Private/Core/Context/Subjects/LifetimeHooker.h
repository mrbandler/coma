// Copyright (c) fivefingergames GmbH. All rights reserved.

#pragma once

#include "Core/Context/ContextSubject.h"
#include "Core/Types/DependencyInstance.h"
#include "CoreMinimal.h"
#include "Dependency.h"
#include "Engine/EngineTypes.h"
#include "UObject/NoExportTypes.h"

#include "LifetimeHooker.generated.h"

/** @brief	Component lifetime hooks; this is the event hub where the context logic is added to specific component lifetime hooks. */
UCLASS()
class ULifetimeHooker: public UContextSubject {
    GENERATED_BODY()

public:
    /** @brief	Handles the begin play action. */
    void OnBeginPlay() const;

    /** @brief	Handles the component created action. */
    void OnComponentCreated() const;

    /** @brief	Handles the blueprint changed action. */
    void OnBlueprintChanged(class UBlueprint* Blueprint) const;

    /** @brief	Handles the component destroyed action. */
    void OnComponentDestroyed(bool bDestroyingHierarchy) const;

    /** @brief	Handles the register action. */
    void OnRegister() const;

private:
    /**
     * @brief	Checks if we are currently in a game state.
     *
     * @returns	True if playing, false if not
     */
    bool IsPlaying() const;

    /**
     * @brief	Returns managed component dependency instances.
     *
     * @returns	Managed component dependency instances
     */
    TArray<class UActorComponent*> GetInstances(EInstanceType Type = EInstanceType::None) const;

    /**
     * @brief	Returns native dependencies.
     *
     * @returns	Native dependencies
     */
    TArray<struct FDependency> GetDependencies(EDependencyType Type = EDependencyType::None) const;

    /**
     * @brief	Converts dependency instances to instances.
     *
     * @param 	DependencyInstances	Dependency instances to convert
     *
     * @returns	Converted dependency instances
     */
    static TArray<class UActorComponent*> DependencyInstancesToInstances(const TArray<struct FDependencyInstance>& DependencyInstances);
};
