#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#define FIRST_PART 0x000001FF
#define SECOND_PART 0x0003FE00

int check2pow(int);
void checkEntropy(int sudoku[][9]);
int powerTwo(int);
int countEntropy(int);
int findLessEntropy(int sudoku[][9]);
void backTrack(int sudoku[][9], int row,int col,int target);
int nPowerTwo(int num,int n);
int isValid(int sudoku[][9],int row,int col);
int solveCell(int  sudoku[][9]);

int main(){
    clock_t start = clock();

    int startRow,startCol,coor;
    int solved = 0;
    int sudoku[9][9];
    memset(sudoku, INT_MAX, sizeof(sudoku));
    int input, in, number, row, col;
    scanf("%d", &input);

    solved += input;

    while (input --) {
        scanf("%d", &in);
        in -- ;
        row = in / 9;
        col = in % 9;
        scanf("%d", &number);
        sudoku[row][col] = (1 << (number - 1));
        sudoku[row][col] |= (1 << (number - 1 + 9));
    }
    
    for(int i = 0;i<9;i++){
        for (int j = 0;j<9;j++) {
           if(!check2pow(sudoku[i][j])) sudoku[i][j] &= FIRST_PART;
            printf("%d ",check2pow(sudoku[i][j]) ? powerTwo(sudoku[i][j]):0);
        }    
        printf("\n");
    }
    printf("\n");
    checkEntropy(sudoku);
    coor = findLessEntropy(sudoku);
    //if (coor == 0) printf("aiiz ");
    //printf("ha\n");
    startRow = powerTwo(coor);
    startCol = powerTwo(coor >> 9);
    
    //printf("%d %d", startRow,startCol);


    if(solveCell(sudoku)) {
        printf("solved\n\n");
    } else {
        printf("Cant\n");
    }
    for (int i = 0;i<9;i++){
        for(int j = 0; j<9;j++){
            printf("%d ", check2pow(sudoku[i][j])?powerTwo(sudoku[i][j]) : powerTwo(sudoku[i][j] >> 9));
        }
        printf("\n");
    }
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nTime Taken: %f second(s)\n", time_spent);

    return 0;
}

int check2pow(int num){
    return (num & (num - 1)) == 0;
}

void checkEntropy(int sudoku[][9]){
    for (int i = 0;i<9;i++){
        for (int j = 0;j<9;j++){
            if (!check2pow(sudoku[i][j])) {
                //printf("%d ", check2pow(sudoku[i][j]));
                //printf("%d ",countEntropy(sudoku[i][j] & FIRST_PART));
                continue;
            }
            //printf("%d ", powerTwo(sudoku[i][j])); 
            for (int n = 0;n<9;n++){
                if(n!=i){
                    sudoku[n][j] &= ~(sudoku[i][j] & FIRST_PART);
                }
                if(n!=j){
                    sudoku[i][n] &= ~(sudoku[i][j] & FIRST_PART);
                }
            }
            for(int k = (i / 3) * 3;k < (i/3) * 3 + 3;k++){
                for (int l = (j/3)*3;l<(j/3)*3+3;l++){
                    if (k==i && l==j) continue;
                    sudoku[k][l] &= ~(sudoku[i][j] & FIRST_PART);
                }
            }
               // printf("0 ");
        }
        //printf("\n");
    }
}

int countEntropy(int num){
    int count = 0;
    for (int i = 0;i<9;i++) count += ((num >> i) & 1) == 1;
    return count;
}

int solveCell(int  sudoku[][9]){
    int coor = findLessEntropy(sudoku);
    if(coor == 0) return 1;
    int row = powerTwo(coor) - 1;
    int col = powerTwo(coor >> 9) - 1;
    //printf("%d %d\n",row,col);
    int entropy = countEntropy(sudoku[row][col]);
    //printf("%d\n", entropy);
    for(int  i = 1;i<=entropy;i++){
        int target = nPowerTwo(sudoku[row][col], i);
        //printf("%d ", target);
        sudoku[row][col] |= (1 << (target + 9));
        if(isValid(sudoku, row, col)){
            if(solveCell(sudoku)) return 1;
        }
        sudoku[row][col] &= FIRST_PART;
    }

    return 0;
}
int isValid(int sudoku[][9],int row,int col){
     for (int i =0;i<9;i++){
        if(i != row){
            if (((sudoku[i][col] & SECOND_PART) & (sudoku[row][col] & SECOND_PART)) > 0) return 0;
        }
        if(i !=col){
            if (((sudoku[row][i] & SECOND_PART) & (sudoku[row][col] & SECOND_PART)) > 0) return 0;
        }
    }
    for (int i = (row/3)*3;i<(row/3)*3+3;i++){
        for (int j = col/3*3;j<(col/3*3)+3;j++){
            if(i == row && j == col)continue;
            if(((sudoku[i][j] & SECOND_PART) & (sudoku[row][col] & SECOND_PART)) > 0) return 0;
            
        }
    }
    return 1;
}
int nPowerTwo(int num,int n){
    int i, count = 0;
    for(i = 0;count<n;i++){
        if(((num >> i) & 1) == 1)count ++;
    }
    return i - 1;
}
int powerTwo(int num){
    int power = 1;
    while ((num & 1) == 0) {
        num>>=1;
        power++;
    }
    return power;
}
int findLessEntropy(int sudoku[][9]){
    int count = INT_MAX, coor = 0;
    for(int i = 0;i<9;i++){
        for (int j = 0;j<9;j++){
            int entropy = countEntropy(sudoku[i][j]);
            //printf("%d ", entropy);
            if(entropy == 1 || ((sudoku[i][j] & SECOND_PART) > 0))continue;
            //printf("a\n");
            if (count > entropy){
                coor &= 0;
                count = entropy;
                coor |= 1<<i;
                coor |= 1<<(j+9);
            }
        }
      //  printf("\n");
    }
    //printf("\n");
    return coor;
}
