#include <iostream>
#include <vector>

using namespace std;

int main(){
  int n, k;
  cin >> n >> k; // Leemos n y k

  vector<int> heights = vector<int>();
  for(int i = 0; i < n; i++){
    int h;
    cin >> h; // Leemos una altura (h)
    heights.push_back(h); // Y guardamos
  }

  vector<int> dp = vector<int>(n); // Inicializamos el vector dp con tamaño n
  
  int sum = 0;
  for(int i = 0; i < k; i++){ // Obtenemos el caso base, la primera suma
    sum += heights[i];
  }
  dp[k-1] = sum; // Guardamos

  for(int i = k; i < n; i++){
    dp[i] = dp[i-1] + heights[i] - heights[i-k];
    // Para cada problema dp[i], utilizamos el optimo del problema dp[i-1]
  }

  // Buscamos el minimo dentro de dp[k-1..n-1]
  // Es decir, desde k-1 hasta el final, manteniendo el indice del menor
  int minSum = dp[n-1];
  int minIndex = n-1;
  for(int i = k-1; i < n; i++){
    if( minSum > dp[i] ){
      minSum = dp[i];
      minIndex = i;
    }
  }

  // Imprimimos el minimo en el formato correcto.
  cout << minIndex - k + 2 << endl;
  return 0;
}

// AC
