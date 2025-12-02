// Copyright (c) fivefingergames GmbH. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "ContextFactory.generated.h"


/** @brief	Context factory. */
UCLASS()
class UContextFactory: public UObject {
    GENERATED_BODY()

public:
    static class UContext* GetContext(class UActorComponent* Component);

};
