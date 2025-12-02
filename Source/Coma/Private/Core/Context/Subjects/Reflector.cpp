// Copyright (c) fivefingergames GmbH. All rights reserved.

#include "Core/Context/Subjects/Reflector.h"

#if WITH_EDITOR
    #include "Kismet2/KismetEditorUtilities.h"
#endif

#include "Coma.h"
#include "Core/Context/Context.h"
#include "Core/Types/DependencyMetadata.h"
#include "Core/Types/Metadata.h"
#include "Core/Utils/ComaStatics.h"
#include "UObject/UObjectIterator.h"

TArray<FDependencyMetadata> UReflector::GetNativeDependencies() const {
    TArray<FDependencyMetadata> Result;

    if (Context->GetSubject()) {
        Result = ReflectInjectMetadata();
        ReflectNativeClasses(Result);
    }

    return Result;
}

void UReflector::InjectInstances(const TArray<UActorComponent*>& Instances) const {
    if (UActorComponent* Subject = Context->GetSubject()) {
        for (TFieldIterator<UProperty> It(Subject->GetClass()); It; ++It) {
            UProperty* Property = *It;

            if (Property->HasMetaData(FComaMetadata::MD_Inject)) {
                FString ClassName;
                Property->GetCPPMacroType(ClassName);

                UActorComponent* Instance = GetComponentInstance(Instances, ClassName);
                if (Instance) {
                    if (UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property)) {
                        void* ValuePtr  = ObjectProperty->ContainerPtrToValuePtr<void>(Subject);
                        UObject* Object = Cast<UObject>(Instance);

                        ObjectProperty->SetObjectPropertyValue(ValuePtr, Object);
                    }
                }
            }
        }
    }
}

void UReflector::RemoveInstances(const TArray<UActorComponent*>& Instances) const {
    if (UActorComponent* Subject = Context->GetSubject()) {
        UClass* Class = Subject->GetClass();
        if (IsValid((Class))) {
            for (TFieldIterator<UProperty> It(Class); It; ++It) {
                UProperty* Property = *It;

                if (Property->HasMetaData(FComaMetadata::MD_Inject)) {
                    FString ClassName;
                    Property->GetCPPMacroType(ClassName);

                    UActorComponent* Instance = GetComponentInstance(Instances, ClassName);
                    if (Instance) {
                        if (UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property)) {
                            void* ValuePtr  = ObjectProperty->ContainerPtrToValuePtr<void>(Subject);

                            ObjectProperty->SetObjectPropertyValue(ValuePtr, nullptr);
                        }
                    }
                }
            }
        }
    }
}

TArray<struct FDependency> UReflector::ReflectDependencies(UBlueprint* Blueprint) const {
    TArray<FDependency> Result;

    if (UActorComponent* Subject = Context->GetSubject()) {
        for (TFieldIterator<UProperty> It(Blueprint->GeneratedClass); It; ++It) {
            UProperty* Property = *It;

            if (Property->GetFName() == FName("Dependencies")) {
                if (UMapProperty* MapProperty = Cast<UMapProperty>(Property)) {
                    void* ValuePtr             = MapProperty->ContainerPtrToValuePtr<void>(Subject);
                    FScriptMapHelper MapHelper = FScriptMapHelper(MapProperty, MapProperty->GetPropertyValuePtr(ValuePtr));
                    Result                     = CreateDependencies(MapHelper);
                }

                break;
            }
        }
    }

    return Result;
}

TArray<FDependencyMetadata> UReflector::ReflectInjectMetadata() const {
    TArray<FDependencyMetadata> Result;

    if (const UActorComponent* Subject = Context->GetSubject()) {
        const UClass* Class = Subject->GetClass();
        for (TFieldIterator<UProperty> It(Class); It; ++It) {
            UProperty* Property = *It;

            if (Property->HasMetaData(FComaMetadata::MD_Inject) && Property->IsNative()) {
                FString ClassName;
                Property->GetCPPMacroType(ClassName);

                const FDependencyMetadata* Found = Result.FindByPredicate([ClassName](FDependencyMetadata MD) {
                    return MD.ClassName == ClassName;
                });

                if (!Found) {
                    FDependencyMetadata MetadataDependency;
                    MetadataDependency.ClassName   = ClassName;
                    MetadataDependency.DisplayName = *Property->GetName();

                    if (Property->HasMetaData(FComaMetadata::MD_InjectDisplayName)) {
                        const FString DisplayName      = Property->GetMetaData(FComaMetadata::MD_InjectDisplayName);
                        MetadataDependency.DisplayName = *DisplayName;
                    }

                    Result.Add(MetadataDependency);
                }
            }
        }
    }

    return Result;
}

void UReflector::ReflectNativeClasses(TArray<FDependencyMetadata>& InOutMetadataDependencies) const {
    if (InOutMetadataDependencies.Num() <= 0) {
        return;
    }

    if (const UActorComponent* Subject = Context->GetSubject()) {
        for (TObjectIterator<UClass> It; It; ++It) {
            UClass* Class = *It;

#if WITH_EDITOR
            if (FKismetEditorUtilities::IsClassABlueprintSkeleton(Class)) {
                continue;
            }
#endif

            const bool bIsNative      = Class->IsNative();
            const bool bCanBeUsed     = !Class->HasAnyClassFlags(CLASS_Deprecated | CLASS_NewerVersionExists | CLASS_Abstract);
            const bool bSpawnable     = Class->HasMetaData(TEXT("BlueprintSpawnableComponent"));

            //UE_LOG(LogComa,
            //       Warning,
            //       TEXT("%s -> bIsNative: %i, bCanBeUsed: %i, bSpawnable: %i"),
            //       *Class->GetName(),
            //       bIsNative,
            //       bCanBeUsed,
            //       bSpawnable)

            if (bIsNative && bCanBeUsed && bSpawnable) {
                const FString NativeClassName = UComaStatics::GetNativeClassName(Class);

                for (FDependencyMetadata& MetadataDependency : InOutMetadataDependencies) {
                    if (MetadataDependency.ClassName == NativeClassName) {
                        MetadataDependency.Component = TSubclassOf<UActorComponent>(Class);

                        break;
                    }
                }

                const bool bSomeComponentsNull = InOutMetadataDependencies.ContainsByPredicate([](FDependencyMetadata MD) {
                    return MD.Component == nullptr;
                });

                if (!bSomeComponentsNull) {
                    return;
                }
            }
        }
    }
}

UActorComponent* UReflector::GetComponentInstance(const TArray<UActorComponent*>& Instances, const FString& ClassName) {
    UActorComponent* Result = nullptr;

    for (UActorComponent* Instance : Instances) {
        const UClass* InstanceClass = Instance->GetClass();
        if (InstanceClass) {
            if (UComaStatics::GetNativeClassName(InstanceClass) == ClassName) {
                Result = Instance;

                break;
            }
        }
    }

    return Result;
}

TArray<FDependency> UReflector::CreateDependencies(FScriptMapHelper& MapHelper) const {
    TArray<FDependency> Result;

    for (int32 i = 0; i < MapHelper.Num(); i++) {
        if (MapHelper.IsValidIndex(i)) {
            TPair<FName, TSubclassOf<UActorComponent>>* pair = reinterpret_cast<TPair<FName, TSubclassOf<UActorComponent>>*>(MapHelper.GetPairPtr(i));

            FDependency Dependency;
            Dependency.DisplayName = pair->Key;
            Dependency.Class       = pair->Value;
            Dependency.Type        = EDependencyType::Manual;

            Result.Add(Dependency);
        }
    }

    return Result;
}
