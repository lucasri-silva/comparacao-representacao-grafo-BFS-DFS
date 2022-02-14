#ifndef FLOODFILL_H
#define FLOODFILL_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define BUFFER_SIZE 1024

typedef struct graph *Graph;
typedef struct TipoVertex *Vertex;

typedef struct TipoItem Item;
typedef struct TipoFila Fila;

// ----- FLOODFILL
void floodfill(Graph G, int x, int y, char replacement);
bool isSafe(Graph G, int x, int y, char target, char replacement);

// -------------- GRAFO
struct TipoVertex{
  char value;
  int cor;
};

struct graph{
  int V; // vertices
  int E; // arestas
  Vertex **adjMatrix;
};

Vertex VertexInitialize(int value);
Graph GraphInitialize(int V);
void GraphInsertEdge(Graph G, int v1, int v2, char *token);
void GraphInsertEdgeAux(Graph G);
void ImprimeGraph(Graph G);

// ------------- FILA
struct TipoItem{
  int x;
  int y;
  Item *prox;
};

struct TipoFila{
  Item *head;
  Item *tail;
  int size;
};

Fila* FFVazia();
void Queue(Fila *f, int x, int y);
Item* Dequeue(Fila *f);

// ------------- BFS
void BFS(Graph G, int s);

// ------------ DFS
void DFS(Graph G, int s);
void DFS_VISIT(Graph G, int i, int *cor, int *d, int *f, int *tempo);

void stop();

#endif
