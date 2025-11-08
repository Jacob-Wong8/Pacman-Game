# Pacman-Game
Pacman game final project for a programming course in university

👻 Dynamic Ghost AI :

Ghosts intelligently chase the player using line-of-sight detection.
If a ghost sees the player directly (without walls in between), it moves toward the player.
Otherwise, it moves randomly within valid map bounds.

🧍‍♂️ Player Movement System :

The player can move in four directions (up, down, left, right) using keyboard input.
Invalid or blocked movements are safely handled (no out-of-bounds or wall collisions).

🗺️ Map Loading from File :

The map layout is dynamically loaded from an external map.txt file.
Map size (height and width) is automatically determined at runtime.
Spaces, walls, dots, player, and ghost positions are all parsed and stored in memory.

🎨 Colored Terminal Output :

Each character on the map (walls, ghosts, player, dots) is printed in color using ANSI terminal color codes.
The game visually differentiates all entities for clarity in the terminal interface.

💾 Dynamic Memory Management :

Memory for the map and dot map is allocated dynamically using malloc().
Allocated memory is properly freed at the end of the program to prevent memory leaks.
