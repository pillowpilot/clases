#include <iostream>
#include <string>
#include <map>

using namespace std;

typedef map<string, bool> msb;

int main(){
  msb set;
  string s;
  cin >> s;
  
  for(int i = 0; i < s.size(); i++){
    for(int j = 0; j < s.size(); j++){
      set[ s.substr(i, s.size() - j) ] = true;
    }
  }

  cout << set.size() << endl;
  return 0;
}
