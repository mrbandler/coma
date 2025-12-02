// Copyright (c) fivefingergames GmbH. All rights reserved.

#include "Core/Context/Context.h"

#include "Core/ComponentManager.h"
#include "Core/Context/Subjects/Adder.h"
#include "Core/Context/Subjects/Creator.h"
#include "Core/Context/Subjects/Destroyer.h"
#include "Core/Context/Subjects/Injector.h"
#include "Core/Context/Subjects/LifetimeHooker.h"
#include "Core/Context/Subjects/Reflector.h"
#include "Core/Context/Subjects/Remover.h"
#include "Core/Storage/DependencyStorage.h"
#include "Core/Utils/ComaStatics.h"

void UContext::Init(UActorComponent* Component) {
    this->Subject   = Component;
    this->SubjectId = UComaStatics::GetUniqueComponentId(Component);
}

UActorComponent* UContext::GetSubject() const {
    return Subject;
}

const FString& UContext::GetSubjectId() const {
    return SubjectId;
}

ULifetimeHooker* UContext::GetLifetimeHooker() {
    if (!LifetimeHooker) {
        LifetimeHooker = NewObject<ULifetimeHooker>(this);
        LifetimeHooker->Init(this);
    }

    return LifetimeHooker;
}

UReflector* UContext::GetReflector() {
    if (!Reflector) {
        Reflector = NewObject<UReflector>(this);
        Reflector->Init(this);
    }

    return Reflector;
}

UCreator* UContext::GetCreator() {
    if (!Creator) {
        Creator = NewObject<UCreator>(this);
        Creator->Init(this);
    }

    return Creator;
}

UAdder* UContext::GetAdder() {
    if (!Adder) {
        Adder = NewObject<UAdder>(this);
        Adder->Init(this);
    }

    return Adder;
}

UInjector* UContext::GetInjector() {
    if (!Injector) {
        Injector = NewObject<UInjector>(this);
        Injector->Init(this);
    }

    return Injector;
}

URemover* UContext::GetRemover() {
    if (!Remover) {
        Remover = NewObject<URemover>(this);
        Remover->Init(this);
    }

    return Remover;
}

UDestroyer* UContext::GetDestroyer() {
    if (!Destroyer) {
        Destroyer = NewObject<UDestroyer>(this);
        Destroyer->Init(this);
    }

    return Destroyer;
}

TArray<FDependency> UContext::GetDependencies() const {
    return UComa::Storage->GetDependencies(SubjectId);
}

void UContext::AddDependencies(TArray<FDependency>& Dependencies) const {
    UComa::Storage->AddDependencies(SubjectId, Dependencies);
}

void UContext::AddDependency(const FDependency& Dependency) const {
    UComa::Storage->AddDependency(SubjectId, Dependency);
}

void UContext::RemoveDependencies() const {
    UComa::Storage->RemoveDependencies(SubjectId);
}
