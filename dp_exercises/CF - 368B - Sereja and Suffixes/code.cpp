#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(){
  int n, m;
  cin >> n >> m; // Leer n y m
  
  vector<int> aa = vector<int>();
  for(int i = 0; i < n; i++){
    int a;
    cin >> a; // Leemos a_i
    aa.push_back(a); // Y vamos agregando al vector aa
  }

  map<int, bool> set = map<int, bool>();
  set[ aa[n-1] ] = true; // Agregamos el ultimo elemento al conjunto

  vector<int> dp = vector<int>(n);
  dp[n-1] = 1; // Inicializamos el caso base dentro del vector dp
  for(int i = n - 2; i >= 0; i--){ // Avanzamos desde el penultimo elemento hacia el primero
    if( set.find(aa[i]) == set.end() ){ // Si no se agrego el elemento aa[i] anteriormente
      set[aa[i]] = true; // Nos encontramos con un nuevo elemento y lo agregamos
      dp[i] = dp[i+1] + 1; // Resolvemos el problema utilizando el optimo anterior
    }else{
      dp[i] = dp[i+1]; // Resolvemos el problema utilizando el optimo anterior
    }
  }

  for(int i = 0; i < m; i++){
    int l;
    cin >> l; // Leemos las solicitudes
    cout << dp[l-1] << '\n'; // Imprimimos las soluciones
    // Considerando que nuestros indices empiezan en cero (0-based).
  }
  cout << endl; // Innecesario (cout << flush)
  
  return 0;
}

// AC
