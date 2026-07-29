# Unreal Engine 5 Modular Interaction System

A performant, server-validated C++ interaction system for Unreal Engine 5. Designed for decoupled logic, easy Blueprint extension, and safe actor lifecycle management.

https://github.com/user-attachments/assets/d37ef92c-44a6-469e-902b-2ae7beac00de

## Key Features

*   **Optimized Tracing:** Uses `FTimerHandle` instead of `Event Tick` for local controller line tracing.
*   **Network Authority:** Client-side prediction with server-side distance validation (`ServerTryInteract`) prevents interaction exploits.
*   **Safe Lifecycle Handling:** Automatically nullifies interaction pointers if the target actor is destroyed (e.g., consumable pickups).
*   **Blueprint Ready:** Interaction logic and UI text are exposed via `BlueprintNativeEvent`, allowing non-programmers to create interactable objects.

https://github.com/user-attachments/assets/2464b177-a56a-48fa-b2fe-342fae3ed32d

## Demo Map Included

The project includes a ready-to-play map demonstrating three core interaction paradigms:
1.  **C++ Implementation (Door):** A C++ actor using a `USceneComponent` hinge to manage open/close state.
2.  **Blueprint Implementation (Light):** A fully Blueprint-implemented actor demonstrating interface inheritance without C++ logic.
3.  **Actor Lifecycle (Pickup):** A C++ item that broadcasts its data and calls `Destroy()` upon interaction, showcasing safe pointer cleanup.

## Easy Blueprint Extension

The interaction system is fully decoupled and exposed to Blueprints via `IInteractableInterface`. Designers and non-programmers can easily create new interactable objects and custom logic without writing a single line of C++ code.

For example, here is the complete implementation of `BP_LightSwitch` using **Event Interact**:
<img width="815" height="370" alt="image" src="https://github.com/user-attachments/assets/dbff6c90-7296-4d89-b4d2-f8acdcef3d19" />
<img width="815" height="370" alt="image" src="https://github.com/user-attachments/assets/eec438d9-c4f7-4cd9-8e2b-19bdff491446" />

## Core Architecture

*   `UInteractorComponent`: The brain of the system. Attach to any Pawn/Character. Configurable trace distance (default: `450.f`) and timer intervals.
*   `IInteractableInterface`: Requires targets to implement `Interact()` and `GetInteractText() const`.

## Quick Setup

1.  Clone the repository and open `.uproject`.
2.  Ensure your project uses the `Interactable` Collision Channel (default response: Ignore, block on target actors).
3.  Open the included Demo Map to test BP and C++ interactable examples.
