// Copyright (c) fivefingergames GmbH. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "ComponentManager.generated.h"

/** @brief	Component Manager; contains the public API for Coma. */
UCLASS()
class COMA_API UComa final: public UObject {
    GENERATED_BODY()

public:
    /**
     * @brief	Adds dependencies for a given component.
     *
     * @param [in,out]	Component   	Component to add dependencies for
     * @param [in,out]	Dependencies	Dependencies to add
     */
    static void AddDependencies(class UActorComponent* Component, TArray<struct FDependency>& Dependencies);

    /**
     * @brief	Adds a dependency for a given component.
     *
     * @param [in,out]	Component 	Component to add the dependency for
     * @param 		  	Dependency	Dependency to add
     */
    static void AddDependency(class UActorComponent* Component, struct FDependency Dependency);

    /**
     * @brief	Handles the component constructor event for a given managed component.
     *
     * @param [in,out]	Component	Component to manage
     */
    static void OnComponentConstructor(class UActorComponent* Component);

    /**
     * @brief	Handles the begin play event for a given managed component.
     *
     * @param [in,out]	Component	Component to manage
     */
    static void OnBeginPlay(class UActorComponent* Component);

    /**
     * @brief	Handles the component created event for a given managed component.
     *
     * @param [in,out]	Component	Component to manage
     */
    static void OnComponentCreated(class UActorComponent* Component);

    /**
     * @brief	Handles the component destroyed event for a given managed component.
     *
     * @param [in,out]	Component				Component to manage.
     * @param 		  	bDestroyingHierarchy	True to destroying hierarchy.
     */
    static void OnComponentDestroyed(class UActorComponent* Component, bool bDestroyingHierarchy);

    /**
     * @brief	Handles the on register event for a given managed component.
     *
     * @param [in,out]	Component	Component to manage
     */
    static void OnRegister(class UActorComponent* Component);

protected:
    /** @brief	Static pointer to the dependency storage; only friends can access. */
    static class UDependencyStorage* Storage;

private:
    /** @brief	On destroyed timer handle. */
    static struct FTimerHandle OnDestroyedTimer;

    /** @brief On register time handle. */
    static struct FTimerHandle OnRegisterTimer;

    /** @brief Flag, whether the managed component was only compiled. */
    static bool bOnlyCompiled;

    /**
     * @brief	Starts the component destroyed timer.
     *
     * @param [in,out]	Component				Component to be destroyed
     * @param 		  	bDestroyingHierarchy	True to destroying hierarchy
     */
    static void StartOnDestroyedTimer(class UActorComponent* Component, bool bDestroyingHierarchy);

    /**
     * @brief	Stops the component destroyed timer.
     *
     * @param [in,out]	Component	Component to be destroyed
     */
    static void StopOnDestroyedTimer(class UActorComponent* Component);

    /**
     * @brief	Starts the component register timer.
     *
     * @param [in,out]	Component	Component to be registered
     */
    static void StartOnRegisterTimer(class UActorComponent* Component);

    /**
     * @brief	Stops the component register timer.
     *
     * @param [in,out]	Component	Component to be registered
     */
    static void StopOnRegisterTimer(class UActorComponent* Component);

    /**
     * @brief	Handles the actual component destroyed event.
     *
     * @param [in,out]	Component				Component to manage
     * @param 		  	bDestroyingHierarchy	True to destroying hierarchy
     */
    static void OnActualComponentDestroyed(class UActorComponent* Component, bool bDestroyingHierarchy);


    /**
     * @brief    Checks whether the OnDestroyed timer is currently active.
     *
     * @param Component Component to manage
     * @return Flag, whether the OnDestroyed timer is currently active or not
     */
    static bool IsComponentDestroyedTimerActive(class UActorComponent* Component);

    /**
     * @brief	Handles the deferred component register event.
     *
     * @param [in,out]	Component	Component to manage
     */
    static void OnDeferredComponentRegister(class UActorComponent* Component);

    /**
     * @brief	Handles the blueprint compiled event.
     *
     * @param [in,out]	Blueprint	Compiled blueprint
     */
    UFUNCTION()
    static void OnBlueprintChanged(class UBlueprint* Blueprint);

    friend class UContext;
};
