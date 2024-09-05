# Raylib C++ Platformer Movement

A simple platformer movement that i made using basic aabb collisions, the repo includes:
  1. State machine for the player
  2. Movement (right and left)
  3. Jump
  4. Wall slide
  5. Wall jump

***Notes***: The collision detection is discrete. therefore, if the speed is very high or the physics update rate is too low, collision detection may not work accurately

## Building
Building requirments:
  1. c++17 or higher
  2. raylib
  3. raylib-cpp
