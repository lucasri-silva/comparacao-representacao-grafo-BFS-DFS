#include "bfs_dfs.h"

// ------------ GRAFO

Graph GraphInitialize(int V) {
  Graph G = malloc(sizeof(Graph));
  G->V = V;
  G->E = 0;
  
  G->adjMatrix = (Vertex **)malloc(V * sizeof(Vertex));
  for(int i=0; i<V; i++)
    G->adjMatrix[i] = (Vertex*)malloc(V * sizeof(Vertex));
  
  for(int i=0; i<V; i++) {
    for(int j=0; j<V; j++)
      G->adjMatrix[i][j] = VertexInitialize(0);
  }
  return G;
}

Vertex VertexInitialize(int value){
  Vertex v = malloc (sizeof(Vertex));
  v->value = value;
  return v;
}

void GraphInsertEdge(Graph G, int v1, int v2){
  Vertex v = G->adjMatrix[v1][v2];
  
  v->value = 1;
  G->E ++;
}

void ImprimeGraph(Graph G){
  Vertex aux;
  
  for(int i = 0; i<G->V; i++) {
    for(int j = 0; j<G->V; j++) {
      aux = G->adjMatrix[i][j];
      printf("%d ", aux->value);
    }
    printf("\n");
  }
}

// ------------------- FILA BFS

Fila* FFVazia(){
  Fila *f = (Fila*) malloc(sizeof(Fila));
  f->head = NULL;
  f->tail = NULL;
  return f;
}

void Queue(Fila *f, int vertex){
  Item *d = (Item *) malloc (sizeof(Item));
  d->data = vertex;
  d->prox = NULL;

  if(f->head == NULL){
    f->head = d;
    f->tail = d;
  }else{
    f->tail->prox = d;
    f->tail = d;
  }

  f->size ++;
}

Item* Dequeue(Fila *f){
  Item *aux;

  if(f->head == NULL)
    return NULL;

  aux = f->head;
  f->head = f->head->prox;
  f->size --;

  return aux;
}

// ----------------- BFS

// branco: v não visitado/conhecido 
// cinza: v conhecido mas não visitado (seus adjacentes ainda não foram inseridos na fila)
// preto: v conhecido e visitado (todos seus adjacentes já foram add na fila e já são conhecidos)

void BFS(Graph G, int s){ //u vértice do vetor; s vertice que se deseja iniciar a pesquisa
  int cor[G->V];
  int d[G->V];
  int *pi = (int*) malloc(G->V * sizeof(int));
  Fila *f = FFVazia();
  
  for(int i=0; i<G->V; i++) {
    if(i != s){
      cor[i] = 0;
      d[i]   = -1;
      pi[i]  = -1;
    }
  }

  cor[s] = 1;
  d[s]   = 0;
  pi[s]  = -1;

  Queue(f, s);

  while(f->size > 0) {
    Item *u = Dequeue(f);
    for(int j=0; j<G->V; j++) {
      Vertex v = G->adjMatrix[u->data][j];
      if(v->value == 1 && cor[j] == 0) {
        cor[j] = 1;
        d[j]   = d[u->data] + 1;
        pi[j]  = u->data;
        Queue(f, j);
      }
    }
    cor[u->data] = 2;
    printf("Vertex:%d\n", u->data);
/*    printf("cor:%d\n", cor[u->data]);*/
/*    printf("pai:%d\n", pi[u->data]);*/
/*    printf("distância:%d\n", d[u->data]);*/
/*    printf("\n");*/
  }
  free(pi);
}

// ---------------------- DFS

// branco: v não visitado/conhecido 
// cinza: v conhecido mas não visitado
// preto: v conhecido e visitado

void DFS(Graph G, int s){ 
  int cor[G->V]; // Branco 0, Cinza 1, Preto 2
  int d[G->V];   // Tempo de descoberta
  int f[G->V];   // Tempo de finalização
  int tempo = 0;

  for(int v=0; v<G->V; v++)
    cor[v] = 0;
  
  DFS_VISIT(G, s, cor, d, f, &tempo);
}

void DFS_VISIT(Graph G, int j, int *cor, int *d, int *f, int *tempo){
  cor[j]  = 1; // v acabou de ser conhecido
  *tempo  += 1;
  d[j]    = *tempo;

  for(int k=0; k<G->V; k++) {
    Vertex u = G->adjMatrix[j][k];
    if(u->value == 1 && cor[k] == 0)
      DFS_VISIT(G, k, cor, d, f, tempo);
  }

  cor[j] = 2;
  *tempo += 1;
  f[j] = *tempo;
  printf("Vertex:%d D:%d, F:%d \n", j, d[j], f[j]);
}
