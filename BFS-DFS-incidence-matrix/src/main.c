#include "bfs_dfs.h"

int main(){

	Graph G = GraphInitialize(5, 7);
	GraphInsertEdge(G, 0, 1);
	GraphInsertEdge(G, 0, 4);
	GraphInsertEdge(G, 1, 0);
	GraphInsertEdge(G, 1, 2);
	GraphInsertEdge(G, 1, 3);
	GraphInsertEdge(G, 1, 4);
	GraphInsertEdge(G, 2, 1);
	GraphInsertEdge(G, 2, 3);
	GraphInsertEdge(G, 3, 1);
	GraphInsertEdge(G, 3, 2);
	GraphInsertEdge(G, 3, 4);
	GraphInsertEdge(G, 4, 0);
	GraphInsertEdge(G, 4, 1);
	GraphInsertEdge(G, 4, 3);

/*	Graph G = GraphInitialize(8, 10);*/
/*	GraphInsertEdge(G, 0, 2);*/
/*	GraphInsertEdge(G, 0, 1);*/
/*	GraphInsertEdge(G, 1, 0);*/
/*	GraphInsertEdge(G, 1, 4);*/
/*	GraphInsertEdge(G, 1, 5);*/
/*	GraphInsertEdge(G, 2, 0);*/
/*	GraphInsertEdge(G, 2, 3);*/
/*	GraphInsertEdge(G, 3, 2);*/
/*	GraphInsertEdge(G, 4, 1);*/
/*	GraphInsertEdge(G, 4, 5);*/
/*	GraphInsertEdge(G, 4, 6);*/
/*	GraphInsertEdge(G, 5, 1);*/
/*	GraphInsertEdge(G, 5, 4);*/
/*	GraphInsertEdge(G, 5, 6);*/
/*	GraphInsertEdge(G, 5, 7);*/
/*	GraphInsertEdge(G, 6, 4);*/
/*	GraphInsertEdge(G, 6, 5);*/
/*	GraphInsertEdge(G, 6, 7);*/
/*	GraphInsertEdge(G, 7, 6);*/
/*	GraphInsertEdge(G, 7, 5);*/
	
	ImprimeGraph(G);
	
	printf("\n------ BFS\n");
	BFS(G, 0);
	
	printf("\n------ DFS\n");
	DFS(G, 0);
	
	return 0;
}
