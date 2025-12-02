// Copyright (c) fivefingergames GmbH. All rights reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "Core/Types/Dependency.h"
#include "CoreMinimal.h"

#include "ManagedActorComponent.generated.h"

/** @brief	Managed actor component. */
UCLASS(Abstract, Blueprintable)
class COMA_API UManagedActorComponent: public UActorComponent {
    GENERATED_BODY()

public:
    /** @brief	Default constructor. */
    UManagedActorComponent();

    /** @brief	Will be called when the game starts. */
    void BeginPlay() override;

    /** @brief	Handles the component created event. */
    void OnComponentCreated() override;

    /**
     * @brief	Handles the component destroyed event.
     *
     * @param 	bDestroyingHierarchy	True to destroying hierarchy
     */
    void OnComponentDestroyed(bool bDestroyingHierarchy) override;

protected:

    /** @brief	Handles the on register event. */
    void OnRegister() override;

private:

    /**
     * @brief	Returns the dependencies of the managed object
     *
     * @returns	Dependencies
     */
    TArray<struct FDependency> GetDependencies() const;

    /** Destroys all managed dependency components when this component is destroyed. */
    UPROPERTY(EditDefaultsOnly, Category = "Coma", meta = (AllowPrivateAccess))
    bool bDestroyDependenciesOnOwnDestruction;

    /** @brief	Component dependencies. */
    UPROPERTY(EditDefaultsOnly, Category = "Coma", meta = (AllowPrivateAccess))
    TMap<FName, TSubclassOf<class UActorComponent>> Dependencies;

};
