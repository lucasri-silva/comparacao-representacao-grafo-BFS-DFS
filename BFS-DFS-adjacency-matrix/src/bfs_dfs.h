#ifndef BFS_DFS_H 
#define BFS_DFS_H

#include<stdio.h>
#include<stdlib.h>

typedef struct graph *Graph;
typedef struct TipoVertex *Vertex;

typedef struct TipoItem Item;
typedef struct TipoFila Fila;

// -------------- GRAFO
struct TipoVertex{
  int value;
};

struct graph{
  int V; // vertices
  int E; // arestas
  Vertex **adjMatrix;
};

Vertex VertexInitialize(int value);
Graph GraphInitialize(int V);
void GraphInsertEdge(Graph G, int v1, int v2);
void ImprimeGraph(Graph G);

// ------------- FILA
struct TipoItem{
  int data;
  Item *prox;
};

struct TipoFila{
  Item *head;
  Item *tail;
  int size;
};

Fila* FFVazia();
void Queue(Fila *f, int vertex);
Item* Dequeue(Fila *f);

// ------------- BFS
void BFS(Graph G, int s);

// ------------ DFS
void DFS(Graph G, int s);
void DFS_VISIT(Graph G, int i, int *cor, int *d, int *f, int *tempo);

#endif
