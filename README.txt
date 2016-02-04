//==================================================
//	CONTROLS
//==================================================

MOVE						-	WASD
SHOOT						-	LCLICK OR SPACE
AIM						-	MOUSE
REVIVE						-	R
FLASHY BLUE DOTS THAT FOLLOWS YOUR MOUSE	-	RCLICK

//==================================================
//	FEATURES
//==================================================

- Component system (Add Sprite, Collider, Text, Transform to GameObject)
- GameObjects can be childed
- QuadTree and Cell-based spatial partitioning for collision with AABB and Circle
- Sprites (Can scale, color, rotate, and animate)
- Serializable tiled sprite using tile sheet
- UI score text display using SDL_ttf
- Texture Manager to recycle textures
- Input Manager (gets keyboard, mouse inputs)
- Timer (calculates global time, delta time, and FPS)
- Bullet Factory (recylce bullets)
- Serializable Enemy Spawner
- 3 types of enemy: Enemy, Enemy2, Boss
- Enemy moves in one direction
- Enemy2 follows pre-defined path using Spline Interpolation
- Boss is stationary and have over 9000 health points
- Scrolling background
- Bullet sites (childed to GameObjects)
- Rendering layer system using a render queue (heap data structure)
- Debug mode to view spatial partitioning

//==================================================
//	KNOWN BUGS
//==================================================

- Cell-based paritioning not handling overlapping objects