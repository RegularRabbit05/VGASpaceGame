# An arduino space shooter prototype

A game using an arduino and [vgax](https://github.com/smaffer/vgaxua) created for a school project
The game uses 2 digital buttons as controls to move the "spaceship" upwards and downwards. It will shoot automatically in front of it and the projectiles will retain the direction.
If a projectile (laser) hits an enemy (crosses) it will destroy it, 

![Bad picture of a tv with vga](https://user-images.githubusercontent.com/69511985/165601523-1040e464-25a4-420e-acd8-04bf656830a1.png)

but if an enemy reaches the spaceship X axis before getting shot the player loses, a gameover screen will appear and the game will restart shortly after.

![Another bad picture of a tv with vga](https://user-images.githubusercontent.com/69511985/165601891-dd87515b-5e70-4962-83a7-176bc24d5965.png)

## "How to build"

![schem](https://user-images.githubusercontent.com/69511985/165600625-1eeeef54-51cc-4e03-beb5-3309583d2c96.png)

Code tested using an Arduino MEGA 2560, may work using an UNO R3 or Nano (coordinates/screen size may vary)
