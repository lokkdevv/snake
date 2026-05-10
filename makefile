default:
	gcc src/main.c -o bin/snake.exe -I"dependencies/include" -L"dependencies/lib" -lraylib -lopengl32 -lgdi32 -lwinmm

run:
	./bin/snake