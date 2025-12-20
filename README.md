# 🎮 Board Games Framework (C++)

A modular **C++ board games framework** that implements multiple classic and custom board games using **Object-Oriented Programming (OOP)** principles.  
The project is designed to be **extensible**, **well-documented**, and easy to maintain.

---

## ✨ Features

- 🧩 **11 fully implemented board games**
- 🧠 Unified **game engine** shared across all games
- 🧑 Human vs Human, Human vs Computer, Computer vs Computer
- 📋 Interactive text-based menu
- 📐 Clean OOP design (Inheritance, Polymorphism, Abstraction)
- 📄 Full **Doxygen HTML documentation**
- 🧪 Validated input handling and win/draw detection

---

## 🏗️ Project Architecture

The project is built around a **generic board-game engine**, which allows new games to be added with minimal effort.

### Core Components
- `Board<T>` – Abstract board representation
- `Player<T>` – Handles player data and type
- `Move<T>` – Encapsulates a move
- `UI<T>` – Manages user interaction
- `GameManager<T>` – Controls the game loop and rules

Each game:
- Inherits from the core classes
- Implements its own rules and logic
- Reuses the same engine and menu system

---

## 🎲 Implemented Games

The project includes the following games:

1. SUS
2. Four-in-a-row
3. 5x5 TicTacToe
4. Word TicTacToe
5. Misère TicTacToe
6. Diamond TicTacToe
7. 4x4 TicTacToe
8. Pyramid TicTacToe
9. Numerical TicTacToe
10. Obstacles TicTacToe
11. Infinity TicTacToe
