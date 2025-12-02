// Copyright (c) fivefingergames GmbH. All rights reserved.

#pragma once

#include "Core/Context/ContextSubject.h"
#include "CoreMinimal.h"

#include "Reflector.generated.h"

/** @brief	Reflector; provides abstraction methods for reflection code on a given subject. */
UCLASS()
class UReflector: public UContextSubject {
    GENERATED_BODY()

public:
    /**
     * @brief	Returns native dependencies of reflector subject.
     *
     * @returns	Found native dependencies
     */
    TArray<struct FDependencyMetadata> GetNativeDependencies() const;

    /**
     * @brief	Inject instances into reflector subject.
     *
     * @param 	Instances	Instances to inject
     */
    void InjectInstances(const TArray<class UActorComponent*>& Instances) const;

    /**
     * @brief	Removes injected instances from reflector subject.
     *
     * @param 	Instances	Instances to remove
     */
    void RemoveInstances(const TArray<class UActorComponent*>& Instances) const;

    /**
     * @brief	Reflects the "dependencies" property on managed component
     *
     * @param [in,out]	Blueprint	Blueprint to reflect on
     *
     * @returns	Reflected dependencies from the given blueprint
     */
    TArray<struct FDependency> ReflectDependencies(class UBlueprint* Blueprint) const;

private:
    /**
     * @brief	Reflect inject metadata specifiers of the reflection subject.
     *
     * @returns Reflected inject metadata dependencies
     */
    TArray<struct FDependencyMetadata> ReflectInjectMetadata() const;

    /**
     * @brief	Reflect native classes with the given metadata dependencies.
     *
     * @param [in,out]	InOutMetadataDependencies	Metadata dependencies
     */
    void ReflectNativeClasses(TArray<struct FDependencyMetadata>& InOutMetadataDependencies) const;

    /**
     * @brief	Returns a component instances in the given instance array for the given class name.
     *
     * @param 	Instances	Instances to search for the given class name
     * @param 	ClassName	Name of the class
     *
     * @returns	Null if it fails, else the component instance
     */
    static class UActorComponent* GetComponentInstance(const TArray<class UActorComponent*>& Instances, const FString& ClassName);

    /**
     * @brief	Creates a array of dependencies based on the reflected values from the managed component.
     *
     * @param [in,out]	MapHelper	Map helper to extract and create the dependency array out of
     *
     * @returns	Created dependency array
     */
    TArray<struct FDependency> CreateDependencies(class FScriptMapHelper& MapHelper) const;
};
