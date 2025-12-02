// Copyright (c) fivefingergames GmbH. All rights reserved.

#include "Core/Utils/ComaStatics.h"

#include "Coma.h"
#include "GameFramework/Actor.h"

const FString UComaStatics::InvalidComponentId(TEXT("CI"));

FString UComaStatics::GetUniqueComponentId(const UActorComponent* Component) {
    FString Result = InvalidComponentId;

    if (IsValid(Component)) {
        if (AActor* ComponentOwner = Component->GetOwner()) {
            UClass* ComponentClass = Component->GetClass();
            UClass* OwnerClass     = ComponentOwner->GetClass();

            if (ComponentClass && OwnerClass) {
                const FString ComponentId = FString::FromInt(ComponentClass->GetUniqueID());
                const FString OwnerId     = FString::FromInt(OwnerClass->GetUniqueID());

                const FString Id = ComponentId + ":" + OwnerId;

                Result = FMD5::HashAnsiString(*Id);
            }
        }
    }

    return Result;
}
FString UComaStatics::GetNativeClassName(const UClass* Class) {
    FString Result = "";

    if (Class) {
        Result = Class->GetPrefixCPP() + Class->GetName();
    }

    return Result;
}

UBlueprint* UComaStatics::IsOwnerBlueprint(const UActorComponent* Component) {
    UBlueprint* Result = nullptr;

    if (IsValid(Component)) {
        AActor* Owner = Component->GetOwner();
        if (IsValid(Owner)) {
            UClass* Class = Owner->GetClass();
            if (IsValid(Class) && IsValid(Class->ClassGeneratedBy)) {
                Result = Cast<UBlueprint>(Class->ClassGeneratedBy);
            }
        }
    }

    return Result;
}
