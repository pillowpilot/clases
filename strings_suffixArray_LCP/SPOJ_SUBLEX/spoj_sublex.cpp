#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<size_t> suffixArray(const string& s){
  using namespace std;
  
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

  auto v = vector<Triple>();
  for(size_t index = 0; index < s.size(); index++){
    size_t sa = index;
    int msd = (int)(s[index]);
    int lsd = (index < s.size() - 1)?(int)(s[index+1]):-1; 
    v.push_back( Triple(sa, msd, lsd) );
  }

  for(int gap = 2; gap < 2*s.size(); gap *= 2){
    sort(v.begin(), v.end());

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

    auto aux = vector<size_t>(v.size());
    for(size_t index = 0; index < aux.size(); index++)
      aux[ v[index].sa ] = index;
    
    for(size_t index = 0; index < v.size(); index++){
      size_t value_index = v[index].sa + gap;
      if( value_index < aux.size() )
	v[index].lsd = v[ aux[value_index] ].msd;
      else
	v[index].lsd = -1;
    }
  }

  auto suffix_array = vector<size_t>();
  for(Triple t: v)
    suffix_array.push_back( t.sa );

  return suffix_array;
}

int main(){
  
  ios_base::sync_with_stdio(false);
  int q;
  string str;

  cin >> str >> q;
  auto sa = suffixArray(str);
  
  while(q-->0){
    int k;
    cin >> k;
    k--;
    cout << str.substr(sa[k]) << endl;
  }
  /*
  string s;
  cin >> s;

  cout << s << endl;
  cout << 500 << endl;
  for(int i = 1; i <= 500; i++){
    cout << i << endl;
  }
  */
  return 0;
}
