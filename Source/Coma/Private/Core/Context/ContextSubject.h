// Copyright (c) fivefingergames GmbH. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "ContextSubject.generated.h"


/** @brief Context subject base class; all classes that need to implement logic in the managed component context need to derive from this class. */
UCLASS(Abstract)
class UContextSubject: public UObject {
    GENERATED_BODY()

public:
    /**
     * @brief	Initializes defaults.
     *
     * @param ComponentContext   Component context
     */
    virtual void Init(class UContext* ComponentContext);

protected:
    /** @brief	 Context this instance is a subject of. */
    UPROPERTY()
    class UContext* Context;
};
