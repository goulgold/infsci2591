all: Floyd_matrix Dijkstra_matrix

Floyd_matrix: Floyd_matrix.cc Graph_Matrix.cc Graph_Matrix.h
	g++ Floyd_matrix.cc Graph_Matrix.cc Graph_Matrix.h -o Floyd_matrix -g

Dijkstra_matrix: Dijkstra_matrix.cc Graph_Matrix.cc Graph_Matrix.h
	g++ Dijkstra_matrix.cc Graph_Matrix.cc Graph_Matrix.h -o Dijkstra_matrix -g

clean:
	rm -f Floyd_matrix

