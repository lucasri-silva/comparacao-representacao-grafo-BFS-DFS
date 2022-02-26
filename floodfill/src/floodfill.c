#include "floodfill.h"
 
// check if it is possible to go to pixel (x, y) from the
// current pixel. The function returns false if the pixel
// has a different color, or it's not a valid pixel
bool isTargetColor(Graph G, int *color, int x, int y, char target) {
  if((x >= 0 && x < G->V) && (y >= 0 && y < G->V)) {
    Vertex v = G->adjMatrix[x][y];
    if(*((color+x*G->V) + y) == 0 && v->value == target) {
      *((color+x*G->V) + y) = 1;
      return true;
    } else {
      *((color+x*G->V) + y) = -1;
      return false;
    }
  }
  return false;
}

// check eight possible movements (adjacent squares)
int row[] = { -1, -1, -1,  0,  0,  1,  1,  1 };
int col[] = { -1,  0,  1, -1,  1, -1,  0,  1 };

// ----------------------------- FLOODFILL BFS
// white (color=0): v has not been visited yet
// gray (color=1): v has target color but has not been visited yet
// black (color=2): v has target color and has been visited
// red (color=-1): v has not target color

void floodfillBFS(Graph G, int x, int y, char replacement) {
  // get the target color
  Vertex v = G->adjMatrix[x][y];
  char target = v->value;

  // target color is same as replacement
  if(target == replacement)
    return;
  
  // BFS
  int color[G->V][G->V];
  
  for(int i=0; i<G->V; i++) {
    for(int j=0; j<G->V; j++)
        color[i][j] = 0;
  }

  color[x][y] = 1;
  
  Fila *f = FFVazia();
  Queue(f, x, y);

  // break when the queue becomes empty
  while(f->size > 0) {
    // dequeue front node and process it
    Item *u = Dequeue(f);

    // (x, y) represents the current pixel 
    int x = u->x, y = u->y;
    v = G->adjMatrix[x][y];

    // replace the current pixel color with that of replacement
    v->value = replacement;

    // process all eight adjacent pixels of the current pixel and enqueue each valid pixel
    for(int k = 0; k < 8; k++) {
      // if the adjacent pixel at position (x + row[k], y + col[k]) is is valid and has the same color as the current pixel
      if(isTargetColor(G, (int *)color, x + row[k], y + col[k], target)) {
        // enqueue adjacent pixel
        Queue(f, x + row[k], y + col[k]);
      }
    }
    color[x][y] = 2;
  }
}

// ----------------------------- FLOODFILL DFS
// white (color=0): v has not been visited yet
// gray (color=1): v has target color but has not been visited yet
// black (color=2): v has target color and has been visited
// red (color=-1): v has not target color

void floodfillDFS(Graph G, int x, int y, char replacement) {
  // get the target color
  Vertex v = G->adjMatrix[x][y];
  char target = v->value;

  // target color is same as replacement
  if(target == replacement)
    return;
  
  // DFS
  int color[G->V][G->V];
  // int d[G->V];   // Tempo de descoberta
  // int f[G->V];   // Tempo de finalização
  // int tempo = 0;

  for(int i=0; i<G->V; i++) {
    for(int j=0; j<G->V; j++)
        color[i][j] = 0;
  }

  DFS_VISIT(G, x, y, (int *)color, target, replacement);
}

void DFS_VISIT(Graph G, int x, int y, int *color, char target, char replacement){
  *((color+x*G->V) + y) = 1;
  // (x, y) represents the current pixel 
  Vertex v = G->adjMatrix[x][y];

  // replace the current pixel color with that of replacement
  v->value = replacement;

  // process all eight adjacent pixels of the current pixel and enqueue each valid pixel
  for(int k = 0; k < 8; k++) {
    // if the adjacent pixel at position (x + row[k], y + col[k]) is is valid and has the same color as the current pixel
    if(isTargetColor(G, (int *)color, x + row[k], y + col[k], target)) {
      // enqueue adjacent pixel
      DFS_VISIT(G, x + row[k], y + col[k], (int *)color, target, replacement);
    }
  }
  *((color+x*G->V) + y) = 2;
}

// ---------------------------- GRAPH

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
  Vertex v = malloc(sizeof(Vertex));
  v->value = value;
  return v;
}

void GraphInsertEdge(Graph G, int v1, int v2, char *token){
  Vertex v = G->adjMatrix[v1][v2];
  v->value = *token;
  G->E++;
}

void GraphInsertEdgeAux(Graph G) {
  FILE *file;
  char *token;
  int i=0, j;
  char buffer[1024];
  file = fopen("./arquivos/exemplo", "r");
  
  if(file == NULL)
        printf( "\nFailed to open file" );
  else { 
         while(fgets(buffer, BUFFER_SIZE, file) != NULL) {
           j=0;
           token = strtok(buffer, ",");
           while(token != NULL) {
             GraphInsertEdge(G, i, j, token);
             token = strtok(NULL, ",");
             j++;
           }
           i++;
       }
  }
  fclose(file);
}

void ImprimeGraph(Graph G){
  Vertex aux;
  
  for(int i = 0; i<G->V; i++) {
    for(int j = 0; j<G->V; j++) {
      aux = G->adjMatrix[i][j];
      printf("%c ", aux->value);
    }
    printf("\n");
  }
}

// ------------------- QUEUE

Fila* FFVazia(){
  Fila *f = (Fila*) malloc(sizeof(Fila));
  f->head = NULL;
  f->tail = NULL;
  return f;
}

void Queue(Fila *f, int x, int y){
  Item *d = (Item *) malloc (sizeof(Item));
  d->x = x;
  d->y = y;
  d->prox = NULL;

  if(f->head == NULL){
    f->head = d;
    f->tail = d;
  } else {
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