/*
Problema SPOJ HERBING
Transformar grafo direccional a grafo no direccionado [1] y contar componentes.

[1] Si en el grafo direccional existe el arco dirigido (u, v) o (v, u), entonces 
en el grafo no dirigido existe el arco no dirigido (u, v).
 */
#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

// Mapa (con las predicciones de las direcciones)
vector< string > map;
vector< vector< bool > > visited;

bool isValid(int i, int j){
  return 0 <= i && 0 <= j && i < map.size() && j < map[i].size() ;
}

// Movimientos
int dy[] = {0, 0, 1, -1}; // N S E W
int dx[] = {-1, 1, 0, 0};
char c1[] = "SNWE";
char c2[] = "NSEW";

void dfs(int x, int y){
  
  visited[x][y] = true; // Se marca como visitado
  for(int i = 0; i < 4; i++){ // Se mira en todas direcciones
    int a = x+dx[i];
    int b = y+dy[i];
    if( isValid(a, b) && // Si la posición es valida
	visited[a][b] == false && // Y no se ha visitado ese nodo
	(map[a][b] == c1[i] || map[x][y] == c2[i]) ){ // Y existe un arco entre ellos
      // map[a][b] == c1[i] comprueba la existencia de (vecino, actual)
      // map[x][y] == c2[i] comprueba la existencia de (actual, vecino)
      dfs(a, b);
    }
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
  visited = vector< vector<bool> >(n, vector<bool>(m, false));

  // Recorremos todos los nodos
  int total_components = 0;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      if( visited[i][j] == false ){ // Si se encontró un nodo no visitado
	total_components++; // Se encontró una nueva componente
	dfs(i, j);
      }
    }
  }

  // Imprimimos el resultado
  cout << total_components << endl;
  
  return 0;
}

// AC
