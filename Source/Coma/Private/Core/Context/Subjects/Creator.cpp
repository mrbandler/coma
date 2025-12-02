// Copyright (c) fivefingergames GmbH. All rights reserved.

#include "Core/Context/Subjects/Creator.h"

#include "Core/Context/Context.h"
#include "Core/Types/Dependency.h"
#include "Core/Types/DependencyInstance.h"
#include "GameFramework/Actor.h"

TArray<FDependencyInstance> UCreator::CreateOrRetrieveDependencyInstances(const TArray<FDependency>& Dependencies) const {
    TArray<FDependencyInstance> Result;

    if (const UActorComponent* Subject = Context->GetSubject()) {
        if (AActor* Owner = Subject->GetOwner()) {
            for (const FDependency Dependency : Dependencies) {
                if (Dependency.Class != nullptr) {
                    FDependencyInstance Instance = GetCachedOrCreate(Owner, Dependency);
                    Result.Add(Instance);
                }
            }
        }
    }

    return Result;
}

FDependencyInstance UCreator::GetCachedOrCreate(AActor* Owner, const FDependency& Dependency) const {
    FDependencyInstance Result;

    Result.Type     = EInstanceType::Cached;
    Result.Instance = Owner->GetComponentByClass(Dependency.Class);
    if (!Result.Instance) {
        Result.Type     = EInstanceType::Created;
        Result.Instance = NewObject<UActorComponent>(Owner, Dependency.Class, Dependency.DisplayName);

        Result.Instance->OnComponentCreated();
        Result.Instance->RegisterComponent();
        if (Result.Instance->bWantsInitializeComponent) {
            Result.Instance->InitializeComponent();
        }
    }

    return Result;
}
