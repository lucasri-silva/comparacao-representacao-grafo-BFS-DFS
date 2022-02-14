#include "floodfill.h"

int main() {
  Graph G = GraphInitialize(10);
  GraphInsertEdgeAux(G);
  ImprimeGraph(G);

 
  // start node
  int x = 3, y = 9;    // having target color `X`

  // replacement color
  char replacement = 'C';

  // replace the target color with a replacement color
  floodfill(G, x, y, replacement);

  // print the colors after replacement
  printf("\n\nGRAFO depois da substituição de cor: \n\n");
  ImprimeGraph(G);
 
    return 0;
}
