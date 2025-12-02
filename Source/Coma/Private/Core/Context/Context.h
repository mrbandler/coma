// Copyright (c) fivefingergames GmbH. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types/Dependency.h"
#include "UObject/NoExportTypes.h"

#include "Context.generated.h"

/** @brief	Managed component context; encapsulates the logic building blocks for a managed component. */
UCLASS()
class UContext: public UObject {
    GENERATED_BODY()

public:
    /**
     * @brief	Initializes defaults.
     *
     * @param [in,out]	Component	Component to manage
     */
    void Init(UActorComponent* Component);

    /**
     * @brief	Returns the subject of the context; namely the managed component.
     *
     * @returns	Subject for this context
     */
    class UActorComponent* GetSubject() const;

    /**
     * @brief	Returns subject identifier for this context.
     *
     * @returns	Subject identifier for this context
     */
    const FString& GetSubjectId() const;

    /**
     * @brief	Returns the lifetime hooker for this context.
     *
     * @returns	Lifetime hooker for this context
     */
    class ULifetimeHooker* GetLifetimeHooker();

    /**
     * @brief	Returns the reflector for this context.
     *
     * @returns	Reflector for this context
     */
    class UReflector* GetReflector();

    /**
     * @brief	Returns the creator for this context.
     *
     * @returns	Creator for this context
     */
    class UCreator* GetCreator();

    /**
     * @brief	Returns the adder for this context.
     *
     * @returns	Adder for this context
     */
    class UAdder* GetAdder();

    /**
     * @brief	Returns the injector for this context.
     *
     * @returns	Injector for this context
     */
    class UInjector* GetInjector();

    /**
     * @brief	Returns the remover for this context.
     *
     * @returns	Remover for this context
     */
    class URemover* GetRemover();

    /**
     * @brief	Returns the destroyer for this context.
     *
     * @returns	destroyer for this context
     */
    class UDestroyer* GetDestroyer();

    /**
     * @brief	Returns component dependencies for this context.
     *
     * @returns	Component dependencies for this context
     */
    TArray<FDependency> GetDependencies() const;

    /**
     * @brief	Adds dependencies.
     *
     * @param [in,out]	Dependencies	Dependencies to add
     */
    void AddDependencies(TArray<FDependency>& Dependencies) const;

    /**
     * @brief	Adds a dependency.
     *
     * @param 	Dependency	Dependency to add
     */
    void AddDependency(const FDependency& Dependency) const;

    /** @brief	Removes all dependencies. */
    void RemoveDependencies() const;

private:
    /** @brief	Subject of this context; managed actor component. */
    UPROPERTY()
    class UActorComponent* Subject;

    /** @brief	Identifier for the subject of this context. */
    UPROPERTY()
    FString SubjectId;

    /** @brief	Cached lifetime hooker for this context. */
    UPROPERTY()
    class ULifetimeHooker* LifetimeHooker;

    /** @brief	Cached reflector for this context. */
    UPROPERTY()
    class UReflector* Reflector;

    /** @brief	Cached creator for this context. */
    UPROPERTY()
    class UCreator* Creator;

    /** @brief	Cached adder for this context. */
    UPROPERTY()
    class UAdder* Adder;

    /** @brief	Cached injector for this context. */
    UPROPERTY()
    class UInjector* Injector;

    /** @brief	Cached remover for this context. */
    UPROPERTY()
    class URemover* Remover;

    /** @brief	Cached destroyer for this context. */
    UPROPERTY()
    class UDestroyer* Destroyer;
};
