#include <cstdio>

using namespace std;

void pprint(char* line){
  while( *line != '\0' ){
    if( *line == '\n' )
      printf("\\n");
    else
      printf("%c", *line);
    line++;
  }
}

int main(){
  char str[30];

  // Mientras no se llegue al fin de archivo (^D)
  while( fgets(str, sizeof str, stdin) != NULL ){
    printf(">>");
    pprint(str);
    printf("\n");
  }

  // Probar entrada con espacios y entrada muy larga (>30)
  
  return 0;
}
