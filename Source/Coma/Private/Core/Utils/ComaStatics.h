// Copyright (c) fivefingergames GmbH. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "ComaStatics.generated.h"

/** @brief	Coma statics. */
UCLASS()
class UComaStatics: public UBlueprintFunctionLibrary {
    GENERATED_BODY()

public:
    /**
     * @brief	Gets unique component identifier.
     *
     * @param 	Component	Component to create the unique identifier for
     *
     * @returns	Created unique component identifier
     */
    static FString GetUniqueComponentId(const class UActorComponent* Component);

    /**
     * @brief	Returns the native class name for a given reflection class.
     *
     * @param 	Class	Reflected class
     *
     * @returns	Native class name
     */
    static FString GetNativeClassName(const UClass* Class);

    /**
     * @brief	Checks if the owner of the subject is a blueprint and if it is returns the blueprint reference.
     *
     * @param 	Component	Component to check for
     *
     * @returns	Null if it fails, else a pointer to a blueprint
     */
    static UBlueprint* IsOwnerBlueprint(const class UActorComponent* Component);

    /** @brief	Constant for a invalid component ID. */
    static const FString InvalidComponentId;
};
