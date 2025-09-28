#include <stdio.h>
void printTable(char x[], char y[], int s[7][11], int row, int col){
    for(int i = -1; i < row; i++){
        for(int j = -1; j < col; j++){
            if(i==-1){
                if (j==-1){
                    printf("  |X ");
                } else {
                    printf("%c ", y[j]);
                }
            } else{
                if(j==-1){
                    printf("%c |", x[i]);
                } else {
                    printf("%d ", s[i][j]);
                }
            }
        }
        printf("\n");
    }
}
int main(){
    char x[] = {'G', 'A', 'C', 'C', 'T', 'G'};
    char y[] = {'A', 'G', 'T', 'A', 'A', 'C', 'G', 'C', 'T', 'A'};
    int row = (sizeof(x)/ sizeof(char))+1;
    int col = (sizeof(y)/ sizeof(char))+1;
    int s[7][11];
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(i == 0 || j == 0)s[i][j] = 0;
            else if(x[i] == y[j]){
                s[i][j] = s[i-1][j-1]+1;
            } else {
                if(s[i-1][j] < s[i][j-1]){
                    s[i][j] = s[i][j-1];
                } else {
                    s[i][j] = s[i-1][j];
                }
            }
        }
    }
    printf("Tamanho da LCS = %d\n", s[row-1][col-1]);
    printTable(x, y, s, row, col);
    return 0;
}