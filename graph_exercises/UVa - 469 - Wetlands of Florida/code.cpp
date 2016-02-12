#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// Mapa del problema
vector< string > map;
// Para evitar ciclos, se marca un punto como visitado
vector< vector<bool> > visited;

// Para no salirse de los limites de la matriz
bool isValid(int i, int j){
  return 0 <= i && 0 <= j && i < map.size() && j < map[i].size();
}

// Para evitar una cadena de if-elses
int dx[] = {1,1,0,-1,-1,-1, 0, 1};
int dy[] = {0,1,1, 1, 0,-1,-1,-1};

// Muy similar a DFS (es DFS sobre un grafo implicito en la matriz)
int floodfill(int x, int y){
  // Se marca el nodo, para ciclos
  visited[x][y] = true;
  // El area debe incluir al nodo actual
  int ans = 1;
  // Para todos los vecinos
  for(int i = 0; i < 8; i++){
    int a = x + dx[i]; // Componente en x de la posicion del vecino
    int b = y + dy[i]; // Componente en y de la posicion del vecino
    // Si no nos salimos de la matriz y no hemos visitado el nodo y es un nodo de agua
    if( isValid(a, b) && visited[a][b] == false && map[a][b] == 'W' ){
      // Resolvemos el subproblema
      ans += floodfill(a, b);
    }
  }
  // Retornamos la respuesta
  return ans;
}

int main(){
  // Para hacer una lectura mas comoda desde cadenas se usa ISTRINGSTREAM (Input STRING STREAM)
  // Asi podemos usar el operador >> para leer desde cadenas.
  istringstream iss; // Flujo (Stream)
  string line; // Cadena
  int tests; // Cantidad de problemas
  getline(cin, line); // Leemos una linea (hasta el FIN DE LINEA, sin incluirlo!)
  iss.str(line); // Definimos la cadena como un flujo de entrada
  iss >> tests; // Leemos los datos desde la cadena...!!
  // Utilizar una cadena como flujo de datos es util para casos donde
  // se debe reconocer el "tipo de cadena" segun alguna caracteristica
  // y leer datos a partir de el. Por ejemplo, en este problema no se define el limite
  // de la matriz del mapa por ello debemos decidir si la linea que leimos es parte del mapa
  // o es la primera linea de consulta
  // "LLLWWWWLLLL" vs "2 5".

  getline(cin, line);// Leemos la primera linea vacia y la ignoramos
  for(int test = 1; test <= tests; test++){
    if( test > 1 ) cout << endl; // Entre problemas imprimimos una linea en blanco (probar sin el)
    int n = 0; // Obtendremos la cantidad de filas de la matriz
    map = vector< string >(); // Inicializamos el mapa como vector de string
    // Esencialmente es lo mismo que vector< vector< char> >, sin embargo es mas comodo de leer
    // y la lectura es identica, map[i][j]!!

    // Leemos linea y vemos si es parte del mapa (si empieza con 'L' o 'W', las otras comienzan con numeros)
    while( getline(cin, line) && (line[0] == 'L' || line[0] == 'W') ){
      // Agregamos al final del mapa
      map.push_back( line );
      // Aumentamos la cantidad de filas
      n++;
    }
    // Deducimos la cantidad de columas
    int m = map[0].size();
        
    do{
      // Limpiamos el flujo (banderas y posiciones anteriores...
      iss.clear();
      // Definimos la linea a utilizar
      // La primera vez que entramos en el ciclo, "line" fue cargado en el "getline" del ciclo anterior
      iss.str(line);
      int i, j;
      // Leemos los datos (como si fuera una entrada estandard)
      iss >> i >> j;
      i--; j--;

      // Reiniciamos las visitas (muy costoso, pero obtiene AC)
      visited = vector< vector<bool> >(n, vector<bool>(m, false));
      // Solucionamos e imprimimos
      cout << floodfill(i, j) << endl;
      
    }while( getline(cin, line) && line.size() > 0 );
  }

  return 0;
}

// AC
