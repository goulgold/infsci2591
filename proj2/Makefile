OSNAME= $(shell uname)
vpath %.h include

ifeq ($(OSNAME), Linux)
	CC=g++
else ifeq ($(OSNAME), Darwin)
	CC=clang++
else
	echo "Use Linux or MacOS to compile, please."
	exit
endif

TARGETS=Floyd_matrix Dijkstra_matrix Floyd_list Dijkstra_list Floyd_array Dijkstra_array
all: ${TARGETS}

${TARGETS}: include/*.h


Floyd_matrix: Floyd_matrix.cc Graph_Matrix.cc 
	${CC} Floyd_matrix.cc Graph_Matrix.cc  -o Floyd_matrix -g

Floyd_list: Floyd_list.cc Graph_List.cc 
	${CC} Floyd_list.cc Graph_List.cc  -o Floyd_list -g -std=c++11

Floyd_array: Floyd_array.cc Graph_Array.cc 
	${CC} Floyd_array.cc Graph_Array.cc  -o Floyd_array -g -std=c++11

Dijkstra_matrix: Dijkstra_matrix.cc Graph_Matrix.cc 
	${CC} Dijkstra_matrix.cc Graph_Matrix.cc  -o Dijkstra_matrix -g

Dijkstra_list: Dijkstra_list.cc Graph_List.cc 
	${CC} Dijkstra_list.cc Graph_List.cc  -o Dijkstra_list -g -std=c++11

Dijkstra_array: Dijkstra_array.cc Graph_Array.cc 
	${CC} Dijkstra_array.cc Graph_Array.cc  -o Dijkstra_array -g

clean:
	rm -f ${TARGETS}

