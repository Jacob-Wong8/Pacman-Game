# Pacman-Game
Pacman game final project for a programming course in university

## Features

- **👻 Dynamic Ghost AI:**
  - Ghosts intelligently chase the player using line-of-sight detection.
  - If a ghost sees the player (without walls in between), it moves toward the player.
  - Otherwise, it moves randomly within valid map bounds.

- **🧍‍♂️ Player Movement System:**
  - The player can move in four directions (up, down, left, right) using keyboard input.
  - Invalid or blocked movements are safely handled (no out-of-bounds or wall collisions).

- **🗺️ Map Loading from File:**
  - The map layout is dynamically loaded from an external `map.txt` file.
  - Map size (height and width) is automatically determined at runtime.
  - Spaces, walls, dots, player, and ghost positions are all parsed and stored in memory.

- **💾 Dynamic Memory Management:**
  - Memory for the map and dot map is allocated dynamically using `malloc()`.
  - All allocated memory is freed at the end of the program to prevent memory leaks.

- **🧠 Game State Tracking:**
  - Tracks remaining dots (win condition).
  - Detects ghost-player collisions (loss condition).
  - Updates and redraws the map after every turn.

---

## ⚙️ Technical Details
 - C, File I/O, Pointers, Dynamic Memory

---

### 🧾 Summary
A C-based Pac-Man–style terminal game that combines dynamic memory allocation, file-based map loading, and real-time color rendering.  
Built with modular design principles, pointer arithmetic, and ANSI color output for an engaging text-based gameplay experience.
