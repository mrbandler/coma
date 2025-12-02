// Copyright (c) fivefingergames GmbH. All rights reserved.

#include "Core/Context/ContextFactory.h"

#include "Core/Context/Context.h"

UContext* UContextFactory::GetContext(UActorComponent* Component) {
    UContext* Result = NewObject<UContext>(UContextFactory::StaticClass());
    Result->Init(Component);

    return Result;
}
