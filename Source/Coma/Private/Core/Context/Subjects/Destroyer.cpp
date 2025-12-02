// Copyright (c) fivefingergames GmbH. All rights reserved.

#include "Core/Context/Subjects/Destroyer.h"

#include "Core/Context/Context.h"
#include "Core/Types/Dependency.h"
#include "GameFramework/Actor.h"

void UDestroyer::DestroyDependencyInstances(const TArray<FDependency>& Dependencies, bool bDestroyingHierarchy) const {
    if (const UActorComponent* Subject = Context->GetSubject()) {
        if (AActor* Owner = Subject->GetOwner()) {
            for (const FDependency Dependency : Dependencies) {
                Destroy(Owner, Dependency, bDestroyingHierarchy);
            }
        }
    }
}

void UDestroyer::Destroy(AActor* Owner, const FDependency& Dependency, bool bDestroyingHierarchy) const {
    UActorComponent* Component = Owner->GetComponentByClass(Dependency.Class);
    if (Dependency.DisplayName.ToString() == Component->GetName()) {
        if (Component->HasBeenInitialized()) {
            Component->InitializeComponent();
        }

        Component->UnregisterComponent();
        Component->OnComponentDestroyed(bDestroyingHierarchy);
    }
}
