// Copyright (c) fivefingergames GmbH. All rights reserved.

#include "Core/Context/Subjects/Adder.h"

#include "Components/ActorComponent.h"
#include "Core/Context/Context.h"
#include "Core/Context/Subjects/Reflector.h"
#include "Core/Utils/ComaStatics.h"
#include "Core/Types/Metadata.h"

#if WITH_EDITOR
    #include "Engine/Blueprint.h"
    #include "Kismet2/BlueprintEditorUtils.h"
    #include "Kismet2/KismetEditorUtilities.h"
#endif

void UAdder::AddToParentBlueprint(const TArray<class UActorComponent*>& Components) const {
#if WITH_EDITOR
    UBlueprint* Blueprint = UComaStatics::IsOwnerBlueprint(Context->GetSubject());
    if (Blueprint && Components.Num() > 0) {
        FKismetEditorUtilities::AddComponentsToBlueprint(Blueprint, Components);
    }
#endif
}

void UAdder::AddDependencyVariables(UBlueprint* Blueprint) const {
#if WITH_EDITOR
    if (UActorComponent* Subject = Context->GetSubject()) {
        TArray<FDependency> Dependencies = Context->GetReflector()->ReflectDependencies(Blueprint);
        for (FDependency& Dependency : Dependencies) {
            AddDependencyVariable(Blueprint, Dependency);
        }


        for (int32 i = Blueprint->NewVariables.Num() - 1; i >= 0; i--) {
            if (Blueprint->NewVariables.IsValidIndex(i)) {
                FBPVariableDescription& Variable = Blueprint->NewVariables[i];
                FDependency Dependency           = *Dependencies.FindByPredicate([Variable](FDependency D) {
                    return D.DisplayName == Variable.VarName;
                });

                bool bIsVarContained = Dependencies.ContainsByPredicate([Variable](FDependency D) {
                    return D.DisplayName == Variable.VarName;
                });

                if (Variable.Category.ToString() == "Coma" && !bIsVarContained) {
                    FBlueprintEditorUtils::RemoveMemberVariable(Blueprint, Variable.VarName);
                }
            }
        }
    }
#endif
}

bool UAdder::AddDependencyVariable(UBlueprint* Blueprint, FDependency Dependency) const {
#if WITH_EDITOR
    bool Result = false;

    FEdGraphPinType Type;
    Type.bIsReference         = true;
    Type.PinCategory          = UEdGraphSchema_K2::PC_Object;
    Type.PinSubCategory       = NAME_None;
    Type.PinSubCategoryObject = *Dependency.Class;

    Result = FBlueprintEditorUtils::AddMemberVariable(Blueprint, Dependency.DisplayName, Type);
    if (Result) {
        const int32 Index = FBlueprintEditorUtils::FindNewVariableIndex(Blueprint, Dependency.DisplayName);
        if (Index != INDEX_NONE) {
            FBPVariableDescription& Variable = Blueprint->NewVariables[Index];
            Variable.SetMetaData(FComaMetadata::MD_Inject, "");
            Variable.Category = FText::FromString("Coma");
        }
    }

    return Result;
#endif
}
