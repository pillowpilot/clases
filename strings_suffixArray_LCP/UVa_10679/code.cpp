#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Algoritmo O(n*lg(n)^2) para la construccion del Suffix Array
void suffixArray(const std::string& s, std::vector<size_t>& sa){
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

  for(size_t index = 0; index < v.size(); index++){
    sa.push_back( v[index].sa );
  }

}

// Algoritmo O(m*lg(n)) para encontrar una subcadena de longitud m
// donde se dispone el suffix array de la cadena principal de longitud n
bool findSubstr(const string& s, const std::vector<size_t>& sa, const string& subs){
  size_t lowIndex = 0, highIndex = sa.size(), index = 0;

  // Suponemos que buscamos en el intervalo [lowIndex, highIndex], inclusive!.
  while( index < subs.size() && lowIndex <= highIndex ){
    size_t midPoint = lowIndex + (highIndex - lowIndex) / 2;

    // Comparamos las cadenas, m comparaciones como maximo.
    index = 0;
    while( index < subs.size() && sa[midPoint] + index < s.size() && s[ sa[midPoint] + index ] == subs[ index ] )
      index++;

    // Si se encontro un caracter distinto...
    if( index < subs.size() && sa[midPoint] + index < s.size() ){
      // Se modifica los limites 
      if( s[ sa[midPoint] + index ] < subs[ index ] )
	lowIndex = midPoint + 1; // Como midPoint se comprobo (y es distinto) se incrementa +1.
      else if( s[ sa[midPoint] + index ] > subs[ index ] )
	highIndex = midPoint - 1; // Al igual aqui

      //Si se llego al final de la cadena principal, por la longitud se decide que s[i..] < subs.
    }else if( sa[midPoint] + index >= s.size() ){
      lowIndex = midPoint + 1;
    }
  }

  // Si la comparacion llego al final, entonces se encontro (una) instancia de la subcadena.
  // No necesariamente es la primera ni la ultima!!. 
  if( index < subs.size() )
    return false;
  else
    return true;
}

int main(){
  ios_base::sync_with_stdio(false);
  int cases;

  cin >> cases;
  while( cases-- > 0 ){
    int q;
    string s;
    cin >> s >> q;
    
    vector<size_t> sa;
    suffixArray(s, sa);
    
    while( q-- > 0 ){
      string subs;
      cin >> subs;

      //cout << s << " - " << subs << endl;
      bool f = findSubstr(s, sa, subs);
      if( f )
	cout << 'y' << endl;
      else
	cout << 'n' << endl;
    }
  }
  
  return 0;
}

// AC
