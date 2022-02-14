#include "floodfill.h"
 
// ----------------------------- FLOODFILL BFS

 
// check if it is possible to go to pixel (x, y) from the
// current pixel. The function returns false if the pixel
// has a different color, or it's not a valid pixel
bool isSafe(Graph G, int x, int y, char target, char replacement) {
    Vertex v = G->adjMatrix[x][y];
    if((x >= 0 && x < 10) && (y >= 0 && y < 10) && (v->value == target)) {
      v->value = replacement;
      return true;
    }
    return false;
}

// Below arrays detail all eight possible movements
int row[] = { -1, -1, -1,  0,  0,  1,  1,  1 };
int col[] = { -1,  0,  1, -1,  1, -1,  0,  1 };

void floodfill(Graph G, int x, int y, char replacement) {
    // create a queue and enqueue starting pixel
    Fila *f = FFVazia();
    Queue(f, x, y);
 
    // get the target color
    Vertex v = G->adjMatrix[x][y];
    char target = v->value;

    // target color is same as replacement
    if (target == replacement)
        return;
   
    v->value = replacement;
    // break when the queue becomes empty
    while (f->size > 0) {
        // dequeue front node and process it
        Item *u = Dequeue(f);
        
        // (x, y) represents the current pixel 
        printf("\n\n");
        ImprimeGraph(G);
        stop();
        // process all eight adjacent pixels of the current pixel and enqueue each valid pixel
        for (int k = 0; k < 8; k++) {
            // if the adjacent pixel at position (x + row[k], y + col[k]) is is valid and has the same color as the current pixel
            if (isSafe(G, u->x + row[k], u->y + col[k], target, replacement)) {
                // enqueue adjacent pixel
                Queue(f, u->x + row[k], u->y + col[k]);
            }
        }
    }
}

// ---------------------------- GRAFO

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

void GraphInsertEdge(Graph G, int v1, int v2, char *token){
  Vertex v = G->adjMatrix[v1][v2];
  
  v->value = *token;
  v->cor = 0;
  G->E++;
}

void GraphInsertEdgeAux(Graph G) {
  FILE *file;
  char *token;
  int i=0, j;
  char buffer[1024];
  file = fopen("./arquivos/exemplo", "r");
  
  if ( file == NULL )
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

// ------------------- FILA

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
