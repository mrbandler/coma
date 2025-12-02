// Copyright (c) fivefingergames GmbH. All rights reserved.

#include "Core/Context/Subjects/Remover.h"

#include "Core/Context/Context.h"
#include "Core/Context/Subjects/Reflector.h"
#include "Core/Utils/ComaStatics.h"

#if WITH_EDITOR
    #include "Engine/Blueprint.h"
    #include "Engine/SCS_Node.h"
    #include "Engine/SimpleConstructionScript.h"
#endif

void URemover::Remove(const TArray<UActorComponent*>& Components) const {
    RemoveFromMetadata(Components);
    RemoveFromBlueprint(Components);
}

void URemover::RemoveFromBlueprint(const TArray<UActorComponent*>& Components) const {
#if WITH_EDITOR
    UActorComponent* Subject = Context->GetSubject();
    if (IsValid(Subject)) {
        UBlueprint* Blueprint = UComaStatics::IsOwnerBlueprint(Context->GetSubject());
        if (Blueprint && Components.Num() > 0) {
            USimpleConstructionScript* SCS = Blueprint->SimpleConstructionScript;

            TArray<USCS_Node*> Nodes = SCS->GetAllNodes();
            for (UActorComponent* const Component : Components) {
                USCS_Node* Node = *Nodes.FindByPredicate([Component](USCS_Node* N) {
                    return N->GetVariableName().ToString() == Component->GetName();
                });

                if (Node) {
                    SCS->RemoveNode(Node);
                }
            }
        }
    }
#endif
}

void URemover::RemoveFromMetadata(const TArray<UActorComponent*>& Components) const {
    Context->GetReflector()->RemoveInstances(Components);
}
