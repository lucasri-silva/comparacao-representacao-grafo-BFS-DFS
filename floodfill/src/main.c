#include "floodfill.h"

int main() {
  bool option=true;
  char answer;
  int algorithm;
  int x, y;
  char replacement;

  Graph G = GraphInitialize(10);
  GraphInsertEdgeAux(G);

  while(option) {
    system("cls || clear");

    printf("\n\nGRAPH: \n\n");
    ImprimeGraph(G);

    printf("\n\n\nChoose a pixel (x y): \t"); // start node
    scanf("%d %d", &x, &y);
    printf("Enter the replacement color: \t");
    scanf(" %c", &replacement);

    // replace the target color with a replacement color
    printf("\n\n(1) - BFS\n(2) - DFS\nWhich algorithm do you want use?\t");
    scanf("%d", &algorithm);
    switch(algorithm) {
      case 1:
        floodfillBFS(G, x, y, replacement);
        break;
      case 2:
        floodfillDFS(G, x, y, replacement);
        break;
    }

    // print the colors after replacement
    printf("\n\nGRAPH after color %c replacement: \n\n", replacement);
    ImprimeGraph(G);

    printf("\n\n\nDo you wish to paint again (y/n)? \t");
    scanf(" %c", &answer);
    if(answer == 'n') option = false;
  }

  return 0;
}