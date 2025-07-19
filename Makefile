CORE_FILES = back/src/terminal.cpp back/src/main.cpp back/src/graph.cpp
FLAGS = -Wall

FORCE:

main: FORCE
	g++ $(CORE_FILES) $(FLAGS) -o main
