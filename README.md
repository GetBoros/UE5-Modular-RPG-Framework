# UE5 Modular RPG Framework

A professional-grade, data-driven framework for Unreal Engine 5, designed for RPGs and visual novels.
Focuses on modularity, loose coupling, and designer-friendly workflows.

## 🏗 Architecture
The framework is built using a **Plugin-based architecture** to ensure zero coupling between game systems.
- **GBCore:** Base interfaces and core subsystems.
- **GBUI_Core:** Decoupled UI management.
- **TLGame:** Game-specific logic, utilizing GAS and Data Assets.

## 🚀 Key Features
- **Data-Driven Design:** Locations, enemies, and events are configured via `PrimaryDataAssets`. No hardcoding.
- **GAS Integration:** Full Gameplay Ability System support for dynamic attribute management.
- **Modular Gameplay:** Systems are isolated and communicate via interfaces.
- **Runtime Localization:** Dynamic string table support.

## 🛠 Tech Stack
- Unreal Engine 5.7.4
- C++ / GAS
- StateTree / EQS

---
*Showcase video: [https://youtu.be/ujgZAM4Y9Ug?si=6r8nUWehWgZi68Ry]*