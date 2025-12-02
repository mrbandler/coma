// Copyright (c) fivefingergames GmbH. All rights reserved.

#include "Components/ManagedActorComponent.h"

#include "Core/ComponentManager.h"

#include "Classes/Engine/Blueprint.h"

UManagedActorComponent::UManagedActorComponent() {
    bDestroyDependenciesOnOwnDestruction = true;
    UComa::OnComponentConstructor(this);
}

void UManagedActorComponent::BeginPlay() {
    UComa::OnBeginPlay(this);
    UActorComponent::BeginPlay();
}

void UManagedActorComponent::OnComponentCreated() {
    UActorComponent::OnComponentCreated();

    TArray<FDependency> Deps = GetDependencies();
    UComa::AddDependencies(this, Deps);
    UComa::OnComponentCreated(this);
}

void UManagedActorComponent::OnComponentDestroyed(bool bDestroyingHierarchy) {
    UActorComponent::OnComponentDestroyed(bDestroyingHierarchy);

    if (bDestroyDependenciesOnOwnDestruction) {
        UComa::OnComponentDestroyed(this, bDestroyingHierarchy);
    }
}

void UManagedActorComponent::OnRegister() {
    UActorComponent::OnRegister();
    UComa::OnRegister(this);
}

TArray<FDependency> UManagedActorComponent::GetDependencies() const {
    TArray<FDependency> Result;

    for (TPair<FName, TSubclassOf<UActorComponent>> Dependency : Dependencies) {
        FDependency Dep;
        Dep.DisplayName = Dependency.Key;
        Dep.Class       = Dependency.Value;

        Result.Add(Dep);
    }

    return Result;
}
