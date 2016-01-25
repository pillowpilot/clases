#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void suffixArray(const std::string& s, vector<size_t>& sa){
  
  struct Triple{
    size_t sa;
    int msd;
    int lsd;
  
    Triple(size_t sa, int msd, int lsd): sa(sa), msd(msd), lsd(lsd){}
    
    bool operator<(const Triple& t) const{
      if( msd == t.msd ){
	if( lsd == t.lsd )
	  return false;
	else
	  return (lsd < t.lsd);
      }else
	return (msd < t.msd);
    }
    
    bool operator==(const Triple& t) const{
      return (msd == t.msd && lsd == t.lsd);
    }
  };

  auto v = vector<Triple>();
  v.reserve( s.size() ); // *
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

  // *
  sa = vector<size_t>();
  sa.reserve(s.size());
  for(auto t: v)
    sa.push_back(t.sa);
}

int main(){
  ios_base::sync_with_stdio(false);
  
  string s;
  cin >> s;
  auto sa = vector<size_t>();
  suffixArray(s, sa);
  for(size_t i: sa)
    cout << i << ' ';
  cout << endl;
  
  return 0;
}

// AC
