#include <cstdio>
#include <vector>

using namespace std;

// Para evitar ciclos, marcamos los nodos
vector<bool> visited;
// Lista de adyacencia para mejor rendimiento
// Usualmente, O(V+E) vs O(V^2) (contra matriz de incidencia)
vector< vector<int> > graph;

// Depth First Search
void dfs(int node){
  // Marcamos el nodo actual
  visited[node] = true;

  // Recorremos sus vecinos
  for(int index = 0; index < graph[node].size(); index++){
    int neighbor = graph[node][index];
    // Si el vecino no fue visitado, recorremos desde el
    if( visited[neighbor] == false ){
      dfs(neighbor);
    }
  }
}

int main(){
  // Buffer de entrada, para poder discriminar tipos de lineas
  char line[10];
  int tests;

  // Leemos la cantidad de problemas
  scanf("%d\n\n", &tests); // "%d "
  for(int test = 1; test <= tests; test++){
    // Entre problemas, una linea en blanco
    if( test > 1 ) printf("\n");
    char largest;
    // Leemos una linea a "line" desde la entrada estandard
    fgets(line, sizeof line, stdin);
    // Desde la linea obtenemos los datos y deducimos la cantidad de nodos
    sscanf(line, "%c\n", &largest);
    int node_counter = largest - 'A' + 1;
    // Inicializamos el vector de visitas y el grafo.
    visited = vector<bool>(node_counter, false);
    graph = vector< vector<int> >(node_counter);

    // Mientras no se llegue al fin del archivo y la linea no sea vacia.
    // fgets lee hasta encontrar un fin de linea ('\n') y tambien lo almacena en la cadena
    // char* fgets(char* cadenaDondeGuargar, size_t tamañoMaximo (evita overflow), FILE* entrada)
    while( fgets(line, sizeof line, stdin) != NULL && line[0] != '\n' ){
      char u, v;
      // Leemos datos desde la cadena (informacion sobre arista/arco)
      sscanf(line, "%c%c\n", &u, &v);
      int u_id = u - 'A';
      int v_id = v - 'A';
      // Agregamos los arcos (es un grafo no dirigido)
      graph[u_id].push_back(v_id);
      graph[v_id].push_back(u_id);
    }

    // Contador
    int maximal_subgraphs = 0;
    for(int root = 0; root < graph.size(); root++){
      // Si no se visito este nodo, implica otra componente
      if( visited[root] == false ){
	maximal_subgraphs++;
	// Marcamos todos los nodos alcanzables
	dfs(root);
      }
    }

    printf("%d\n", maximal_subgraphs);
  }
  return 0;
}
// AC
