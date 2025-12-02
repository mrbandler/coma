// Copyright (c) fivefingergames GmbH. All rights reserved.

#pragma once

#include "Core/Context/ContextSubject.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Injector.generated.h"

/** @brief	Component injector; injects component instances into the managed component owner. */
UCLASS()
class UInjector: public UContextSubject {
    GENERATED_BODY()

public:
    /**
     * @brief	Injects the given components to inject
     *
     * @param 	Components	Components to inject
     */
    void Inject(const TArray<class UActorComponent*>& Components) const;
};
