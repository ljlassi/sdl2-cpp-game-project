# C++ SDL2 game project
I realized that I had been long neglecting improving my skills with C++ so I did this little game project. It was quite fun and I might continue the project one way or another. The game is built on top of SDL2 using C++, it's intentionally done a at a low level in terms of programming.

### Idea of the game
In this game you (square) spawn in the middle and shoot blue bullets (press space) at incoming enemies (rectangles) that follow you where-ever you go. The texture assets are intentionally like they are and I kept the buggy rotation (A&D) mechanism because it creates some challenge for the player :)
### Gameplay image
![Alt text](gameplay_image.png?raw=true "Gameplay image")

### Licensing

Please first contact me if you intend to utilize this code elsewhere. More info can be found within licensing.txt

### Compilation instructions

Make sure you have the SDL2 and SDL2_Image libraries properly set up if you intend to compile this. I finally made a makefile so for compilation you can just run:

```
make
```
Run `make` in the project's main folder. The game will be compiled into a single binary named `shooter01` in the `build` folder. If you want to clear/remove the build, you can run:

```
make clean
```

Which will delete the build folder.