// Copyright (c) fivefingergames GmbH. All rights reserved.

#include "Core/Context/Subjects/LifetimeHooker.h"

#include "Coma.h"
#include "Core/Context/Context.h"
#include "Core/Context/Subjects/Adder.h"
#include "Core/Context/Subjects/Creator.h"
#include "Core/Context/Subjects/Destroyer.h"
#include "Core/Context/Subjects/Injector.h"
#include "Core/Context/Subjects/Reflector.h"
#include "Core/Context/Subjects/Remover.h"
#include "Core/Types/DependencyInstance.h"
#include "Core/Types/DependencyMetadata.h"
#include "Engine/World.h"

void ULifetimeHooker::OnBeginPlay() const {
    const TArray<UActorComponent*> Instances = GetInstances();
    Context->GetInjector()->Inject(Instances);
}

void ULifetimeHooker::OnComponentCreated() const {
    const TArray<FDependency> ReflectedDependencies = GetDependencies(EDependencyType::Reflected);
    if (ReflectedDependencies.Num() <= 0) {
        TArray<FDependency> DependenciesToAdd;
        TArray<FDependencyMetadata> MetadataDependencies = Context->GetReflector()->GetNativeDependencies();
        for (FDependencyMetadata& MetadataDependency : MetadataDependencies) {
            DependenciesToAdd.Add(MetadataDependency.ToDependency());
        }

        Context->AddDependencies(DependenciesToAdd);
    }

    if (IsPlaying()) {
        const TArray<FDependency> Dependencies = Context->GetDependencies();
        Context->GetCreator()->CreateOrRetrieveDependencyInstances(Dependencies);
    }
}

void ULifetimeHooker::OnBlueprintChanged(UBlueprint* Blueprint) const {
    if (!IsPlaying()) {
        Context->GetAdder()->AddDependencyVariables(Blueprint);
    }
}

void ULifetimeHooker::OnComponentDestroyed(bool bDestroyingHierarchy) const {
    const TArray<UActorComponent*> Instances = GetInstances();

    if (Instances.Num() > 0) {
        Context->GetRemover()->Remove(Instances);
    }

    const TArray<FDependency> Dependencies = Context->GetDependencies();
    if (Dependencies.Num() > 0) {
        Context->GetDestroyer()->DestroyDependencyInstances(Dependencies, bDestroyingHierarchy);
        Context->RemoveDependencies();
    }
}

void ULifetimeHooker::OnRegister() const {
    const TArray<UActorComponent*> Instances = GetInstances(EInstanceType::Created);
    if (!IsPlaying()) {
        Context->GetAdder()->AddToParentBlueprint(Instances);
    }
}

bool ULifetimeHooker::IsPlaying() const {
    bool Result = false;

    if (const UActorComponent* Subject = Context->GetSubject()) {
        if (UWorld* World = Subject->GetWorld()) {
            Result = World->WorldType == EWorldType::Game || World->WorldType == EWorldType::PIE;
        }
    }

    return Result;
}

TArray<UActorComponent*> ULifetimeHooker::GetInstances(EInstanceType Type /*= EInstanceType::None*/) const {
    const TArray<FDependency> Dependencies                = Context->GetDependencies();
    TArray<FDependencyInstance> Instances = Context->GetCreator()->CreateOrRetrieveDependencyInstances(Dependencies);

    if (Type != EInstanceType::None) {
        Instances = Instances.FilterByPredicate([Type](FDependencyInstance DI) {
            return DI.Type == Type;
        });
    }

    return DependencyInstancesToInstances(Instances);
}

TArray<FDependency> ULifetimeHooker::GetDependencies(EDependencyType Type /*= EDependencyType::None*/) const {
    TArray<FDependency> Dependencies = Context->GetDependencies();

    if (Type != EDependencyType::None) {
        Dependencies = Dependencies.FilterByPredicate([Type](FDependency D) {
            return D.Type == Type;
        });
    }

    return Dependencies;
}

TArray<UActorComponent*> ULifetimeHooker::DependencyInstancesToInstances(const TArray<FDependencyInstance>& DependencyInstances) {
    TArray<UActorComponent*> Result;

    for (const FDependencyInstance DependencyInstance : DependencyInstances) {
        if (DependencyInstance.Instance) {
            Result.Add(DependencyInstance.Instance);
        }
    }

    return Result;
}
