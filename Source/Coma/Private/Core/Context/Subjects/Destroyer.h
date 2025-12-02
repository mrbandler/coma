// Copyright (c) fivefingergames GmbH. All rights reserved.
//
#pragma once

#include "Core/Context/ContextSubject.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Destroyer.generated.h"

UCLASS()
class UDestroyer: public UContextSubject {
    GENERATED_BODY()

public:
    void DestroyDependencyInstances(const TArray<struct FDependency>& Dependencies, bool bDestroyingHierarchy) const;

private:
    void Destroy(class AActor* Owner, const struct FDependency& Dependency, bool bDestroyingHierarchy) const;

};
