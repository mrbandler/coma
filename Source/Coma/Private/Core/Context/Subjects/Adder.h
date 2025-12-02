// Copyright (c) fivefingergames GmbH. All rights reserved.

#pragma once

#include "Core/Context/ContextSubject.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Adder.generated.h"


/** @brief	Component adder; adds component instances for a managed component to the owner blueprint. */
UCLASS()
class UAdder : public UContextSubject {
	GENERATED_BODY()

public:

    /**
     * @brief	Adds components into blueprint.
     *
     * @param 	Components	Components to add
     */
    void AddToParentBlueprint(const TArray<class UActorComponent*>& Components) const;

    /**
     * @brief	Adds dependency variables into a blueprint.
     *
     * @param [in,out]	Blueprint	Blueprint to add dependency variables to
     */
    void AddDependencyVariables(class UBlueprint* Blueprint) const;

private:

    /**
     * @brief	Adds a dependency variable to a given blueprint.
     *
     * @param [in,out]	Blueprint 	Blueprint to add the variable to
     * @param 		  	Dependency	Dependency to add a variable for
     *
     * @returns	True if it succeeds, false if it fails
     */
    bool AddDependencyVariable(class UBlueprint* Blueprint, struct FDependency Dependency) const;

};
