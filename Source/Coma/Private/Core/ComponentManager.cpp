// Copyright (c) fivefingergames GmbH. All rights reserved.

#include "Core/ComponentManager.h"

#include "Coma.h"
#include "Components/ActorComponent.h"
#include "Core/Context/ContextFactory.h"
#include "Core/Context/Context.h"
#include "Core/Context/Subjects/LifetimeHooker.h"
#include "Core/Storage/DependencyStorage.h"
#include "Core/Utils/ComaStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

#include "Core/Types/Metadata.h"

#if WITH_EDITOR
    #include "Engine/Blueprint.h"
    #include "Kismet2/BlueprintEditorUtils.h"
    #include "EdGraphSchema_K2.h"
#endif

UDependencyStorage* UComa::Storage = NewObject<UDependencyStorage>();
FTimerHandle UComa::OnDestroyedTimer = FTimerHandle();
FTimerHandle UComa::OnRegisterTimer = FTimerHandle();
bool UComa::bOnlyCompiled           = false;

void UComa::AddDependencies(UActorComponent* Component, TArray<FDependency>& Dependencies) {
    const FString ComponentId = UComaStatics::GetUniqueComponentId(Component);
    Storage->AddDependencies(ComponentId, Dependencies);
}

void UComa::AddDependency(UActorComponent* Component, const FDependency Dependency) {
    const FString ComponentId = UComaStatics::GetUniqueComponentId(Component);
    Storage->AddDependency(ComponentId, Dependency);
}

void UComa::OnComponentConstructor(UActorComponent* Component) {
    UBlueprint* Blueprint = Cast<UBlueprint>(Component->GetClass()->ClassGeneratedBy);
    if (Blueprint) {
        Blueprint->OnChanged().AddStatic(&UComa::OnBlueprintChanged);
    }
}

void UComa::OnBeginPlay(UActorComponent* Component) {
    UE_LOG(LogComa, Warning, TEXT("UComa::OnBeginPlay"))

    if (UContext* Context = UContextFactory::GetContext(Component)) {
        Context->GetLifetimeHooker()->OnBeginPlay();
    }
}

void UComa::OnComponentCreated(UActorComponent* Component) {
    UE_LOG(LogComa, Warning, TEXT("UComa::OnComponentCreated"))

    StopOnDestroyedTimer(Component);
    StopOnRegisterTimer(Component);

    if (UContext* Context = UContextFactory::GetContext(Component)) {
        Context->GetLifetimeHooker()->OnComponentCreated();
    }
}

void UComa::OnComponentDestroyed(UActorComponent* Component, bool bDestroyingHierarchy) {
    UE_LOG(LogComa, Warning, TEXT("UComa::OnComponentDestroyed"))

    StopOnRegisterTimer(Component);
    StartOnDestroyedTimer(Component, bDestroyingHierarchy);
}

void UComa::OnActualComponentDestroyed(UActorComponent* Component, bool bDestroyingHierarchy) {
    UE_LOG(LogComa, Warning, TEXT("UComa::OnActualComponentDestroyed"))

    if (bOnlyCompiled == false) {
        if (UContext* Context = UContextFactory::GetContext(Component)) {
            Context->GetLifetimeHooker()->OnComponentDestroyed(bDestroyingHierarchy);
        }
    } else {
        bOnlyCompiled = false;
    }
}

void UComa::OnBlueprintChanged(UBlueprint* Blueprint) {
    UE_LOG(LogComa, Warning, TEXT("UComa::OnBlueprintChanged"))

    bOnlyCompiled = true;

    if (UActorComponent* Component = Cast<UActorComponent>(Blueprint->GeneratedClass.GetDefaultObject())) {
        if (UContext* Context = UContextFactory::GetContext(Component)) {
            Context->GetLifetimeHooker()->OnBlueprintChanged(Blueprint);
        }
    }
}

void UComa::OnRegister(UActorComponent* Component) {
    UE_LOG(LogComa, Warning, TEXT("UComa::OnRegister"))

    if (!IsComponentDestroyedTimerActive(Component)) {
        StopOnRegisterTimer(Component);
        StartOnRegisterTimer(Component);
    }
}

void UComa::OnDeferredComponentRegister(UActorComponent* Component) {
    UE_LOG(LogComa, Warning, TEXT("UComa::OnDeferredComponentRegister"))

    StopOnRegisterTimer(Component);
    if (UContext* Context = UContextFactory::GetContext(Component)) {
        Context->GetLifetimeHooker()->OnRegister();
    }
}

void UComa::StartOnDestroyedTimer(UActorComponent* Component, bool bDestroyingHierarchy) {
    if (Component) {
        if (UWorld* World = Component->GetWorld()) {
            FTimerManager& TimerManager = World->GetTimerManager();

            const FTimerDelegate Delegate = FTimerDelegate::CreateStatic(&UComa::OnActualComponentDestroyed, Component, bDestroyingHierarchy);
            TimerManager.SetTimer(OnDestroyedTimer, Delegate, 0.05, false);
        }
    }
}

void UComa::StopOnDestroyedTimer(UActorComponent* Component) {
    if (Component) {
        if (UWorld* World = Component->GetWorld()) {
            FTimerManager& TimerManager = World->GetTimerManager();

            TimerManager.ClearTimer(OnDestroyedTimer);
        }
    }
}

bool UComa::IsComponentDestroyedTimerActive(UActorComponent* Component) {
    bool Result = false;

    if (Component) {
        if (UWorld* World = Component->GetWorld()) {
            FTimerManager& TimerManager = World->GetTimerManager();

            Result = TimerManager.IsTimerActive(OnDestroyedTimer);
        }
    }

    return Result;
}

void UComa::StartOnRegisterTimer(UActorComponent* Component) {
    if (Component) {
        if (UWorld* World = Component->GetWorld()) {
            FTimerManager& TimerManager = World->GetTimerManager();

            const FTimerDelegate Delegate = FTimerDelegate::CreateStatic(&UComa::OnDeferredComponentRegister, Component);
            TimerManager.SetTimer(OnRegisterTimer, Delegate, 0.05, false);
        }
    }
}

void UComa::StopOnRegisterTimer(UActorComponent* Component) {
    if (Component) {
        if (UWorld* World = Component->GetWorld()) {
            FTimerManager& TimerManager = World->GetTimerManager();

            TimerManager.ClearTimer(OnRegisterTimer);
        }
    }
}

