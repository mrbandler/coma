<div align="center">

<img src="Resources/Icon128.png" alt="Coma Logo" width="128" height="128">

# Coma

### **Co**mponent **Ma**nager

*Unity-style `[RequireComponent]` for Unreal Engine*

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Unreal Engine 4](https://img.shields.io/badge/Unreal%20Engine-4-blue.svg)](https://www.unrealengine.com/)
[![Status: Proof of Concept](https://img.shields.io/badge/Status-Proof%20of%20Concept-orange.svg)](#known-limitations)

</div>

---

**Coma is an Unreal Engine plugin that brings Unity-style `[RequireComponent]` functionality to Unreal. It provides automatic component dependency management and injection for actor components.**

> **⚠️ Proof of Concept - Editor Only**
> 
> This plugin works in the Unreal Editor but **does not work in packaged/shipped builds**. It is released as a proof of concept and learning resource.
>
> **📦 Legacy Code**
> 
> This is old code written for **Unreal Engine 4** and has not been updated or tested with Unreal Engine 5.

## Motivation

Developers coming from Unity are familiar with the `[RequireComponent(typeof(T))]` attribute, which automatically adds required components when you add a component to a GameObject. Unreal Engine doesn't have a built-in equivalent - Coma aims to fill that gap.

### Unity

```csharp
[RequireComponent(typeof(Rigidbody))]
[RequireComponent(typeof(BoxCollider))]
public class MyComponent : MonoBehaviour {
    // Rigidbody and BoxCollider are automatically added
}
```

### Coma (Unreal)

```cpp
UCLASS()
class UMyComponent : public UManagedActorComponent {
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category = "Coma")
    TMap<FName, TSubclassOf<UActorComponent>> Dependencies = {
        { TEXT("Physics"), UMyPhysicsComponent::StaticClass() }
    };
};
```

## Features

- **Declarative Dependencies** - Define component dependencies using a simple `TMap` property
- **Automatic Creation** - Dependency components are automatically created when the managed component is added
- **Dependency Injection** - Component references are automatically injected via Unreal's reflection system
- **Lifecycle Management** - Optionally destroy dependencies when the managed component is destroyed
- **Blueprint Support** - Works with Blueprint components in the editor

## Installation

1. Clone or download this repository
2. Copy the `Coma` folder to your project's `Plugins` directory
3. Regenerate project files and build

## Usage

### Basic Usage

Inherit from `UManagedActorComponent` and declare your dependencies:

```cpp
#pragma once

#include "Components/ManagedActorComponent.h"
#include "MyManagedComponent.generated.h"

UCLASS()
class UMyManagedComponent : public UManagedActorComponent {
    GENERATED_BODY()

public:
    UMyManagedComponent() {
        // Define dependencies
        Dependencies.Add(TEXT("Health"), UHealthComponent::StaticClass());
        Dependencies.Add(TEXT("Combat"), UCombatComponent::StaticClass());
    }
};
```

### Configuration

The `UManagedActorComponent` base class provides the following configuration:

| Property | Description |
|----------|-------------|
| `Dependencies` | A map of display names to component classes that should be automatically created |
| `bDestroyDependenciesOnOwnDestruction` | When `true`, destroys all managed dependency components when this component is destroyed |

### Reflection-Based Injection

Coma can automatically inject component references into properties marked with injection metadata. This uses Unreal's reflection system to discover and populate component references.

## Architecture

The plugin is built around a Context pattern with specialized subjects:

- **Creator** - Creates dependency components
- **Adder** - Adds components to actors
- **Injector** - Injects component references into properties
- **Remover** - Removes components from actors
- **Destroyer** - Destroys components
- **Reflector** - Handles reflection-based dependency discovery
- **LifetimeHooker** - Manages component lifecycle hooks

The main API is exposed through the `UComa` class.

## Known Limitations

> **🚨 Critical: This plugin does not work in packaged builds.**

The current implementation relies on editor-only functionality and reflection mechanisms that don't properly persist through the cooking/packaging process. This makes it unsuitable for production use.

Other limitations:

- **Unreal Engine 4 only** - Written for UE4, not updated for UE5
- Heavy reliance on Unreal's reflection system
- Editor module dependencies (`UnrealEd`, `BlueprintGraph`)
- Timing-sensitive lifecycle hooks that can behave differently outside the editor

## Example

The plugin includes a Blueprint example in `Content/BlueprintExample/` demonstrating a chess board setup with various managed components:

- `BP_Board` - Board component with dependencies
- `BP_Tile` - Tile components
- `BP_Pawn` - Chess pawn with spawner dependencies

## Contributing

This is a proof of concept released for educational purposes. Feel free to fork and experiment, but be aware of the fundamental limitations with packaged builds.

If you find a way to make this work in shipped games, contributions are welcome!

## License

MIT License - see [LICENSE](LICENSE) for details.

## Acknowledgments

- Inspired by Unity's `[RequireComponent]` attribute
- Built for developers transitioning from Unity to Unreal Engine
