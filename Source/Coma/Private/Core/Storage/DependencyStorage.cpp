// Copyright (c) fivefingergames GmbH. All rights reserved.

#include "Core/Storage/DependencyStorage.h"

#include "Core/Types/Dependency.h"
#include "Core/Utils/ComaStatics.h"

void UDependencyStorage::AddDependency(const FString& ComponentId, FDependency Dependency) {
    if (ComponentId != UComaStatics::InvalidComponentId) {
        if (Dependencies.Contains(ComponentId)) {
            TSet<FDependency>& FoundDeps = *Dependencies.Find(ComponentId);

            Dependency.Type = EDependencyType::Manual;
            FoundDeps.Add(Dependency);
        } else {
            TSet<FDependency> NewDeps;
            NewDeps.Add(Dependency);

            Dependencies.Add(ComponentId, NewDeps);
        }
    }
}

void UDependencyStorage::AddDependencies(const FString& ComponentId, TArray<FDependency>& DependenciesToAdd) {
    if (DependenciesToAdd.Num() <= 0) {
        return;
    }

    if (ComponentId != UComaStatics::InvalidComponentId) {
        if (Dependencies.Contains(ComponentId)) {
            TSet<FDependency>& FoundDeps = *Dependencies.Find(ComponentId);
            for (FDependency& ToAdd : DependenciesToAdd) {
                ToAdd.Type = EDependencyType::Manual;
                FoundDeps.Add(ToAdd);
            }
        } else {
            Dependencies.Add(ComponentId, TSet<FDependency>(DependenciesToAdd));
        }
    }
}

TArray<FDependency> UDependencyStorage::GetDependencies(const FString& ComponentId) {
    TArray<FDependency> Result;

    if (ComponentId != UComaStatics::InvalidComponentId) {
        if (Dependencies.Contains(ComponentId)) {
            TSet<FDependency>& FoundDeps = *Dependencies.Find(ComponentId);

            Result = FoundDeps.Array();
        }
    }

    return Result;
}

void UDependencyStorage::RemoveDependencies(const FString& ComponentId) {
    if (ComponentId != UComaStatics::InvalidComponentId) {
        if (Dependencies.Contains(ComponentId)) {
            Dependencies.FindAndRemoveChecked(ComponentId);
        }
    }
}
