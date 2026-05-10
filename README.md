# snake+ (Windows)

```
                         _              
                        | |         _   
         ___ _ __   __ _| | _____ _| |_ 
        / __| '_ \ / _` | |/ / _ \_   _|
        \__ \ | | | (_| |   <  __/ |_|  
        |___/_| |_|\__,_|_|\_\___|      
                                                  
```

A minimalist Snake clone built with **C** and **raylib**. It is a snake clone but with modern graphics and powerups. It will also include modding abilities in the future.

## Requirements
- **OS:** Windows 10/11
- **Compiler:** MinGW-w64 / GCC
- **Tools:** Make

## Build & Run
The project uses a `Makefile` to link local dependencies found in `/dependencies`.

```powershell
make         # Compiles src/main.c to bin/snake.exe
make run     # Launches the game from the bin folder
```

## Controls
- WASD: Move Snake
- Esc: Exit Game

## Project Structure
- ```src/```: Source code files.
- ```bin/```: Compiled executable.
- ```dependencies/```: Local raylib headers and libraries.

## License
- MIT license
