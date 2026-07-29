# Unreal Engine 5 Modular Interaction System

A performant, server-validated C++ interaction system for Unreal Engine 5. Designed for decoupled logic, easy Blueprint extension, and safe actor lifecycle management.

https://github.com/user-attachments/assets/b373fb49-28cb-47c4-899f-b3e6443d426f

## Key Features

*   **Optimized Tracing:** Uses `FTimerHandle` instead of `Event Tick` for local controller line tracing.
*   **Network Authority:** Client-side prediction with server-side distance validation (`ServerTryInteract`) prevents interaction exploits.
*   **Safe Lifecycle Handling:** Automatically nullifies interaction pointers if the target actor is destroyed (e.g., consumable pickups).
*   **Blueprint Ready:** Interaction logic and UI text are exposed via `BlueprintNativeEvent`, allowing non-programmers to create interactable objects.

## Demo Map Included

The project includes a ready-to-play map demonstrating three core interaction paradigms:
1.  **C++ Implementation (Door):** A C++ actor using a `USceneComponent` hinge to manage open/close state.
2.  **Blueprint Implementation (Light):** A fully Blueprint-implemented actor demonstrating interface inheritance without C++ logic.
3.  **Actor Lifecycle (Pickup):** A C++ item that broadcasts its data and calls `Destroy()` upon interaction, showcasing safe pointer cleanup.

## Core Architecture

*   `UInteractorComponent`: The brain of the system. Attach to any Pawn/Character. Configurable trace distance (default: `450.f`) and timer intervals.
*   `IInteractableInterface`: Requires targets to implement `Interact()` and `GetInteractText() const`.

## Quick Setup

1.  Clone the repository and open `.uproject`.
2.  Ensure your project uses the `Interactable` Collision Channel (default response: Ignore, block on target actors).
3.  Open the included Demo Map to test BP and C++ interactable examples.
