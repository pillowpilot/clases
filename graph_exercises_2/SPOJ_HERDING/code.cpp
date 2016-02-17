/*
  Problema SPOJ - HERDING
  Solucionamos esto con Flood Fill para reconocer la cantidad de "componentes".
(El termino componentes no se utiliza correctamente, simplemente dividimos el grafo 
del problema en "componentes" tal que dos nodos U y V pertenecen a la misma "componente"
si y solo si existe un camino (definido por el mapa del problema) desde U a V o desde V a U ).

 El problema es suficientemente flexible para poder solucionarse de distintas maneras.
(Ver set).
 */
#include <iostream>
#include <string>
#include <vector>
#include <limits>

// Estado de un nodo (almacenado en "ids")
#define CURRENT_RUN -1
#define UNVISITED 0
// Si un nodo posee un id > 0, este id corresponde a su componente

using namespace std;

// Mapa (con las predicciones de las direcciones)
vector< string> map;
// Identificadores de componentes
vector< vector<int> > ids;
// Cantidad total de componentes
int total_components;

// Movimientos
int dy[] = {0, 0, 1, -1}; // N S E W
int dx[] = {-1, 1, 0, 0};

// Algoritmo de Flood Fill
// Retorna el Identificador del nodo (x, y)
// Nodos con distinto identificador pertenecen a distintos componentes
int ff(int x, int y){
  if( ids[x][y] == CURRENT_RUN ){   // Si ya fue visitado y es parte del camino actual
    // Aqui entramos si descubrimos una nueva componente (un ciclo nuevo)
    
    total_components++; // Encontramos una nueva componente
    int current_component_id = total_components; // Definimos el identificador
    ids[x][y] = current_component_id;  // Asignamos este identificador al nodo actual
    return current_component_id; // Retornamos el identificador
    
  }else if( ids[x][y] != UNVISITED ){ // Si ya fue visitado y no es parte del camino actual
    // Aqui entramos si encontramos otro camino perteneciente a una componente anteriormente descubierta
    
    int current_component_id = ids[x][y];
    return current_component_id; // Retornamos el identificador correspondiente
    
  }else{ // Si no fue visitado
    // Aqui entramos si hemos descubierto nada, seguimos por el camino indicado
    
    int a, b; // Posición a donde iremos
    //cout << x << ", " << y << "(" << map[x][y] << ")" << " > ";
    switch( map[x][y] ){
    case 'N':
      a = x + dx[0]; b = y + dy[0]; break;
    case 'S':
      a = x + dx[1]; b = y + dy[1]; break;
    case 'E':
      a = x + dx[2]; b = y + dy[2]; break;
    case 'W':
      a = x + dx[3]; b = y + dy[3]; break;
    }
    //cout << a << ", " << b << endl;

    ids[x][y] = CURRENT_RUN; // Temporalmente, marcamos el nodo para (posiblemente) identificar mas adelante un ciclo
    int next_node_component_id = ff(a, b); // Recorremos el resto del camino y obtenemos el identificador del nodo siguiente
    // Evidentemente el nodo actual pertenece a la misma componente que el nodo siguiente
    int current_component_id = next_node_component_id; // Definimos el identificador del nodo actual
    ids[x][y] = current_component_id; // Almacenamos 
    return current_component_id; // Y retornamos
    
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  int n, m;
  cin >> n >> m; // Leemos n y m (dimensiones)

  cin.ignore( numeric_limits<streamsize>::max(), '\n' ); // Ignorar todo hasta '\n';
  // ignore(N, C): ignora hasta encontrar el caracter C o hasta ignorar un maximo de N caracteres
  // numeric_limits<streamsize>: el tamaño maximo de un stream (la # maxima de caracteres ignorables)
  // Tambien char c; while( cin >> c && c != '\n' );

  // Leemos el mapa
  for(int i = 0; i < n; i++){
    string line;
    getline(cin, line);
    map.push_back(line);
  }

  // c++11
  //for(auto s: map)
  //cout << s << endl;

  // Inicializamos los nodos como no visitados
  ids = vector< vector<int> >(n, vector<int>(m, UNVISITED));

  // Recorremos todos los nodos
  total_components = 0;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      // Si no hemos visitado este nodo descubrimos si
      // 1. pertenece a una nueva componente o
      // 2. pertenece a una componente anteriormente descubierta
      // La informacion sobre el nodo es actualizada dentro de "ff" y tambien la # de componentes
      if( ids[i][j] == UNVISITED ){
	ff(i, j);
      }
    }
  }

  // Imprimimos el resultado
  cout << total_components << endl;
  
  return 0;
}

// AC
