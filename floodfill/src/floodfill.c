#include "floodfill.h"
 
// ----------------------------- FLOODFILL BFS

 
 // check if it is possible to go to pixel (x, y) from the
// current pixel. The function returns false if the pixel
// has a different color, or it's not a valid pixel
bool isSafe(Graph G, int x, int y, char target, char replacement) {
    Vertex v = G->adjMatrix[x][y];
    if((x >= 0 && x < 10) && (y >= 0 && y < 10) && (v->value == target)) {
/*      printf("\nx = %d , y = %d , v->value = %c", x, y, v->value);stop();*/
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
/*        Vertex v = G->adjMatrix[u->x][u->y];*/
/*        printf("Dequeue = %d %d", u->x, u->y);*/
        // replace the current pixel color with that of replacement
/*        v->value = replacement;*/
        printf("\n\n");
        ImprimeGraph(G);
        stop();
        // process all eight adjacent pixels of the current pixel and enqueue each valid pixel
        for (int k = 0; k < 8; k++) {
            // if the adjacent pixel at position (x + row[k], y + col[k]) is is valid and has the same color as the current pixel
            if (isSafe(G, u->x + row[k], u->y + col[k], target, replacement)) {
                // enqueue adjacent pixel
                Queue(f, u->x + row[k], u->y + col[k]);
/*                printf("\nf->size = %d row %d col %d", f->size, row[k], col[k]);stop();*/
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

// ----------------- BFS

/*void BFS(Graph G, int s){ //u vértice do vetor; s vertice que se deseja iniciar a pesquisa*/
/*  int cor[G->V];*/
/*  int d[G->V];*/
/*  int *pi = (int*) malloc(G->V * sizeof(int));*/
/*  Fila *f = FFVazia();*/
/*  */
/*  for(int i=0; i<G->V; i++) {*/
/*    if(i != s){*/
/*      cor[i] = 0;*/
/*      d[i]   = -1;*/
/*      pi[i]  = -1;*/
/*    }*/
/*  }*/

/*  cor[s] = 1;*/
/*  d[s]   = 0;*/
/*  pi[s]  = -1;*/

/*  Queue(f, s);*/

/*  while(f->size > 0) {*/
/*    Item *u = Dequeue(f);*/
/*    for(int j=0; j<G->V; j++) {*/
/*      Vertex v = G->adjMatrix[u->data][j];*/
/*      if(v->value == 1 && cor[j] == 0) {*/
/*        cor[j] = 1;*/
/*        d[j]   = d[u->data] + 1;*/
/*        pi[j]  = u->data;*/
/*        Queue(f, j);*/
/*      }*/
/*    }*/
/*    cor[u->data] = 2;*/
/*    printf("Vertex:%d\n", u->data);*/
/*    printf("cor:%d\n", cor[u->data]);*/
/*    printf("pai:%d\n", pi[u->data]);*/
/*    printf("distância:%d\n", d[u->data]);*/
/*    printf("\n");*/
/*  }*/
/*  free(pi);*/
/*}*/

// ---------------------- DFS

// branco: v não visitado/conhecido 
// cinza: v conhecido mas não visitado
// preto: v conhecido e visitado

// void DFS(Graph G, int s){ 
//   int cor[G->V]; // Branco 0, Cinza 1, Preto 2
//   int d[G->V];   // Tempo de descoberta
//   int f[G->V];   // Tempo de finalização
//   int tempo = 0;

//   for(int v=0; v<G->V; v++)
//     cor[v] = 0;
  
//   DFS_VISIT(G, s, cor, d, f, &tempo);
// }

// void DFS_VISIT(Graph G, int j, int *cor, int *d, int *f, int *tempo){
//   cor[j]  = 1;
//   *tempo  += 1;
//   d[j]    = *tempo;

//   for(int k=0; k<G->V; k++) {
//     Vertex u = G->adjMatrix[j][k];
//     if(u->value == 1 && cor[k] == 0)
//       DFS_VISIT(G, k, cor, d, f, tempo);
//   }

//   cor[j] = 2;
//   *tempo += 1;
//   f[j] = *tempo;
//   printf("Vertex:%d D:%d, F:%d \n", j, d[j], f[j]);
// }

void stop() {
  printf("\nSTOP...");getchar();while(getchar() != '\n');
}
