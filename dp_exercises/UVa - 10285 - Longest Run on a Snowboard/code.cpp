#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

vvi map;
vvi memo;

bool isValid(int i, int j){
  return (0 <= i && i < map.size() && 0 <= j && j < map[i].size());
}

int dp(int i, int j){
  if( memo[i][j] == -1 ){
    int llen = 0;
    if( isValid(i-1, j) && map[i-1][j] < map[i][j] && llen < dp(i-1, j) + 1) llen = dp(i-1, j) + 1;
    if( isValid(i, j+1) && map[i][j+1] < map[i][j] && llen < dp(i, j+1) + 1) llen = dp(i, j+1) + 1;
    if( isValid(i+1, j) && map[i+1][j] < map[i][j] && llen < dp(i+1, j) + 1) llen = dp(i+1, j) + 1;
    if( isValid(i, j-1) && map[i][j-1] < map[i][j] && llen < dp(i, j-1) + 1) llen = dp(i, j-1) + 1;
    memo[i][j] = llen;
  }
  return memo[i][j];
}

int solve(){
  int maxLen = 0;
  for( int i = 0; i < map.size(); i++ ){
    for( int j = 0; j < map[i].size(); j++ ){
      //printf("%3d", dp(i, j));
      if( maxLen < dp(i, j) ) maxLen = dp(i, j);
    }
  }
  return maxLen + 1;
}

void init(int r, int c){
  memo.clear();
  map.clear();

  memo = vvi(r, vi(c, -1));
  map = vvi(r, vi(c));
}

int main(){
  int cases, r, c;
  string name;
  
  cin >> cases;
  while( cases-- > 0 ){
    cin >> name >> r >> c;

    init(r, c);
    for( int i = 0; i < r; i++ ){
      for( int j = 0; j < c; j++ ){
	int h;
	cin >> h;
	map[i][j] = h;
      }
    }
    printf("%s: %d\n", name.data(), solve());
    
  }
}
