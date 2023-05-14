# Airplane Shooting

> Inspired by a classic game named Plane Battle. Just a simple game made in C++ and using SDL2 library. This game project is also the major assignment for my Advanced Programming course.

## Installation

Clone this project or download directly [here](https://github.com/SliferSkyd/airplane-shooting).

The executable file is called `main`. 

Tested in Window 10. 

Double-click on the executable file to run.

If you want to change anything in my code, recompile by this command:

```
mingw32-make
```

**NOTE**: Other OS haven't be considered yet.

## How to play

Use your mouse and keyboard to interact with the game.
- Move the mouse to direct your character following it.   
- Shoot bullets by clicking the left or right mouse button.

This game contains 3 small levels and a final level. During the first 3 levels, the number of enemies is increasing and in the last level, you have to fight with a boss.

Initially, you have 5 health points and it will reset when you pass the current level. Each time being shot or colliding with an enemy, your health point is decreased by 1 and if it reaches 0, you will lose. 

There are two types of enemy. Some of them will follow you no matter where you are and you can only avoid by kill them before being killed. Meanwhile, the rest simply move in a straight line.   

The boss (dragon) has 10 health points and it breathes 5 fireballs at once. Moreover, it heals 1 health point every 7 seconds.

Besides, some bonus items may be helpful that you can collect during the game:
- Heart: heal 1 health point.
- Shield: protect you from all damage for 5 seconds.
- Nuclear Bomb: collect one special item allowing you to shoot 5 bullets simultaneously. It's quite hard to explain, therefore experience it during the game. Middle-click whenever you want to use it.

**NOTE**: Additional features for testers:
- `SPACE` to turn on/ off safe mode so you have unlimited time shield and  
- `BACKSPACE` to pass the current level immediately. 

Please don't use these keys to enjoy my game to the fullest. Good luck and have fun!

## Credit
This game project was made entirely by me, following the instructions from:
- [Lazyfoo](https://lazyfoo.net) for SDL2 tutorials.
- [Phattrienphanmem123az](https://phattrienphanmem123az.com) to build basic game features.  

All images, sounds and font types are downloaded from free sources.  

## Contributing
Due to being my first game project, it might be exist some bugs. If you find any, please feedback to me.

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License

[MIT](https://choosealicense.com/licenses/mit/)
