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

// ----- FLOODFILL BFS
void floodfillBFS(Graph G, int x, int y, char replacement);
bool isTargetColor(Graph G, int *cor, int x, int y, char target);

// ----- FLOODFILL DFS
void floodfillDFS(Graph G, int x, int y, char replacement);
void DFS_VISIT(Graph G, int x, int y, int *cor, char target, char replacement);

// -------------- GRAPH
struct TipoVertex{
  char value;
};

struct graph{
  int V; // vertex
  int E; // edge
  Vertex **adjMatrix;
};

Vertex VertexInitialize(int value);
Graph GraphInitialize(int V);
void GraphInsertEdge(Graph G, int v1, int v2, char *token);
void GraphInsertEdgeAux(Graph G);
void ImprimeGraph(Graph G);

// ------------- QUEUE
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

#endif