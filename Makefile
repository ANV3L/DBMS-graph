CORE_FILES = src/terminal.cpp src/main.cpp
FLAGS = -Wall

FORCE:

main: FORCE
	g++ $(CORE_FILES) $(FLAGS) -o main
