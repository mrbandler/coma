// Copyright (c) fivefingergames GmbH. All rights reserved.
//
#pragma once

#include "Core/Context/ContextSubject.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Remover.generated.h"

UCLASS()
class URemover: public UContextSubject {
    GENERATED_BODY()

public:
    /**
     * @brief	Injects the given components to inject
     *
     * @param 	Components	Components to inject
     */
    void Remove(const TArray<class UActorComponent*>& Components) const;

    /**
     * @brief	Injects components into blueprint.
     *
     * @param 	Components	Components to inject
     */
    void RemoveFromBlueprint(const TArray<class UActorComponent*>& Components) const;

    /**
     * @brief	Injects components into metadata.
     *
     * @param 	Components	Components to inject
     */
    void RemoveFromMetadata(const TArray<class UActorComponent*>& Components) const;

};
