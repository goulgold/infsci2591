TARGETS=Floyd_matrix Dijkstra_matrix Floyd_list Dijkstra_list Floyd_array Dijkstra_array
all: ${TARGETS}

${TARGETS}: util.h


Floyd_matrix: Floyd_matrix.cc Graph_Matrix.cc Graph_Matrix.h
	g++ Floyd_matrix.cc Graph_Matrix.cc Graph_Matrix.h -o Floyd_matrix -g

Floyd_list: Floyd_list.cc Graph_List.cc Graph_List.h
	g++ Floyd_list.cc Graph_List.cc Graph_List.h -o Floyd_list -g -std=c++11

Floyd_array: Floyd_array.cc Graph_Array.cc Graph_Array.h
	g++ Floyd_array.cc Graph_Array.cc Graph_Array.h -o Floyd_array -g

Dijkstra_matrix: Dijkstra_matrix.cc Graph_Matrix.cc Graph_Matrix.h
	g++ Dijkstra_matrix.cc Graph_Matrix.cc Graph_Matrix.h -o Dijkstra_matrix -g

Dijkstra_list: Dijkstra_list.cc Graph_List.cc Graph_List.h
	g++ Dijkstra_list.cc Graph_List.cc Graph_List.h -o Dijkstra_list -g -std=c++11

Dijkstra_array: Dijkstra_array.cc Graph_Array.cc Graph_Array.h
	g++ Dijkstra_array.cc Graph_Array.cc Graph_Array.h -o Dijkstra_array -g

clean:
	rm -f ${TARGETS}

