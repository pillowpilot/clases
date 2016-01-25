#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Para algoritmo de ordenamiento entre cadenas

std::vector<size_t> suffixArray(const std::string& s);
std::vector<size_t> lcpArray(const std::string& s, const std::vector<size_t>& suffi_array);

int main(){
  using namespace std;
  
  ios_base::sync_with_stdio(false);
  int tests;
  cin >> tests;
  while( tests-- > 0 ){
    string s;
    cin >> s;
    auto sa = suffixArray(s);
    auto lcp = lcpArray(s, sa);

    unsigned long long ans = s.size() - sa[0];
    for(size_t index = 1; index < sa.size(); index++){
      ans += (s.size() - sa[index]) - lcp[index];
    }
    cout << ans << endl;
  }
  
  return 0;
}

// Algoritmo O(n*lg(n)^2) para la construccion del Suffix Array
std::vector<size_t> suffixArray(const std::string& s){
  using namespace std;

  // Se define una 3-tupla compuesta de
  // sa: correspondiente a los valores del SA.
  // msd: el digito mas significativo (msd) para el ordenamiento.
  // lsd: el digito menos significativo (lsd) para el ordenamiento
  // Se define los metodos de orden e igualdad.
  struct Triple{
    size_t sa;
    int msd;
    int lsd;
    // Constructor
    Triple(size_t sa, int msd, int lsd): sa(sa), msd(msd), lsd(lsd){}
    // Funcion a utilizarse por std::sort de <algorithm>
    bool operator<(const Triple& t) const{
      if( msd == t.msd ){
	if( lsd == t.lsd )
	  return false;
	else
	  return (lsd < t.lsd);
      }else
	return (msd < t.msd);
    }
    // Funcion de igualdad
    bool operator==(const Triple& t) const{
      return (msd == t.msd && lsd == t.lsd);
    }
  };

  // Se inicializa los valores
  auto v = vector<Triple>();
  for(size_t index = 0; index < s.size(); index++){
    size_t sa = index;
    // Se define la relacion entre el primer caracter y el msd
    int msd = (int)(s[index]);
    // El segundo caracter con lsd y si no existe, se indica el menor valor posible
    int lsd = (index < s.size() - 1)?(int)(s[index+1]):-1; 
    v.push_back( Triple(sa, msd, lsd) );
  }

  // Se repite lg(n) veces 
  for(int gap = 2; gap < 2*s.size(); gap *= 2){

    // Se ordena segun msd y lsd
    sort(v.begin(), v.end());

    // Se redefinen los msd manteniendo el orden
    int msd = 0;
    for(size_t index = 0; index < v.size() - 1; index++){
      if( !(v[index] == v[index+1]) ){
	v[index].msd = msd;
	msd++;
      }else{
	v[index].msd = msd;
      }
    }
    v[v.size()-1].msd = msd;

    // Se inicializa el vector auxiliar
    // Tal que es el inverso del SA
    // aux[ sa[i] ] = i
    auto aux = vector<size_t>(v.size());
    for(size_t index = 0; index < aux.size(); index++)
      aux[ v[index].sa ] = index;

    // Se calculan los valores de los lsd segun el invariante
    // (La parte complicada!!)
    for(size_t index = 0; index < v.size(); index++){
      size_t value_index = v[index].sa + gap;
      if( value_index < aux.size() )
	v[index].lsd = v[ aux[value_index] ].msd;
      else
	v[index].lsd = -1;
    }
    

  }

  // Se prepara el SA y se retorna
  auto suffix_array = vector<size_t>();
  for(Triple t: v)
    suffix_array.push_back( t.sa );

  return suffix_array;
}

// Algoritmo O(n) para la contruccion del LCP Array
std::vector<size_t> lcpArray(const std::string& s, const std::vector<size_t>& suffix_array){
  using namespace std;

  // Se reserva espacio suficiente para el LCP Array
  auto lcp_array = vector<size_t>(s.size());

  // Se inicializa el vector auxiliar
  // Es el inverso de Suffix Array
  auto aux = vector<size_t>(suffix_array.size());
  for(size_t index = 0; index < suffix_array.size(); index++)
    aux[ suffix_array[index] ] = index;

  // Se inicializa la longitud del prefijo a cero.
  size_t length = 0;
  for(size_t index = 0; index < aux.size(); index++){
    // Se recorren las subcadenas el orden en que se encuentran en la cadena principal
    size_t lcp_index = aux[index];
    // Se reduce en uno la longitud del prefijo,
    // así no se realizan comparaciones innecesarias
    // Pero siempre manteniendolo no negativo
    // (Parte complicada de explicar POR QUE!!!)
    if( lcp_index != 0 ){ // lcp_index == 0 implica que no existe un antecesor.
      if( length > 0 )
	length--;

      // Se comparan los caracteres de
      // la subcadena A,
      // y la subcadena B, la antecesor de A.
      size_t index_substr_a = index;
      // Con aux[index] obtenemos el orden de la subcadena A
      // Restamos 1 para obtener el orden de la subcadena B (su antecesor)
      // Con suffix_array[aux[index]-1] obtenemos el indice del inicio de B
      // (Parte complicada de entender el codigo)
      size_t index_substr_b = suffix_array[aux[index] - 1];
      while( index_substr_a < s.size() &&
	     index_substr_b < s.size() &&
	     s[index_substr_a + length] == s[index_substr_b + length]
	     ){
	// Incrementamos en uno, mientras se incremente el prefijo
	length++;
      }

      // Al finalizar, guardamos el resultado
      lcp_array[lcp_index] = length;
    }
  }

  return lcp_array;
}


// AC
