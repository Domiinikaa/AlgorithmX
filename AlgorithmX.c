#include <stdio.h>
#include <stdlib.h>

#define MaxRowLenght    300
#define MaxNumberOfRows 200

/*
 * This is the structure of one element in the help table, which is a temporary solution.
 */
typedef struct element{
    char c;
    int was;
}element;

/*
 * We count the number of characters in a row and return it via the pointer `d`.
 * This function loads the first line into a table named Filter.
 */
void LoadFilter(size_t * d, int * Filter){
    int k = getchar();
    size_t i = 0;
    while(k != '\n'){
        if(k == '+'){
            Filter[i] = 1;
        } 
        else if(k == '-') { 
            Filter[i] = 0;
        }
        i++;
        k = getchar();
    }
    *d = i;
}

/*
 * This function uses the filter to print data held in the help table according to its pattern.
 */
void printDataWithFilter(element * Help, int * Filter, size_t d){
    for(size_t i = 0; i < d; i++){
        if(Filter[i])
            printf("%c", Help[i].c);
    }
    printf("\n");
}

/*
 * This function creates a two-dimensional array of size MaxNumbersOfRows × d,
 * then iterates over the lines and loads the data into the array.
 * The function returns the number of rows via a pointer.
 */
char ** LoadData(size_t d, int * Rows){
    int rows = 0; 

    char ** matrix = (char**)malloc(MaxNumberOfRows * sizeof(char*)); 
    if (!matrix) return NULL;

    int c = getchar();
    while(rows < MaxNumberOfRows && c != EOF){

        char *row = (char *)malloc(d * sizeof(char));
        if (!row) return NULL; 

        int j = 0;
        while(c != '\n' ){
            row[j] = (char)c;
            j++;
            c = getchar();
        }
        c = getchar();

        matrix[rows++] = row;
    }
    *Rows = rows;
    return matrix;
}

/*
 * Function that frees the memory of a two-dimensional array
 */
void FreeMatrix(char ** matrix, int rows){
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

/*
 * Function that checks whether a row from a two-dimensional array can be added to our (incomplete) solution. 
 */
size_t DoTheyCollide(char * ROW, element * help, size_t d){
    for(size_t i = 0; i < d; i++){
        if(help[i].was && ROW[i] != '_') return 1;
    }
    return 0;
}

/*
 * Function that adds a row from the matrix to our temporary solution stored in the help array, 
 * returning the number of words added and updating the start variable, which moves to the next column.
 */
size_t check(element * help, char * ROW, size_t d, size_t * start){
    size_t k = 0;
    for(size_t i = 0; i < d; i++){
        if(ROW[i] != '_'){
            help[i].c = ROW[i];
            help[i].was = 1;
            k++;
        }
    }
    (*start)++;
    return k;
}

/*
 * Function that undoes changes made by the check function
 */
size_t uncheck(element * help, char * ROW, size_t d, size_t * start){
    size_t k = 0;
    for(size_t i = 0; i < d; i++){
        if(ROW[i] != '_'){
            help[i].was = 0;
            k++;
        }
    }
    (*start)--;
    return k;
}

/*
 * Our stopping point is when the word count in the temporary solution stored in the help table equals one row
 * (i.e., the row is completely covered). If we are in a column and the temporary solution already has a word at that 
 * position, we move to the next column. If not, we look at all possible symbols different from '_' and, 
 * if they do not collide when adding complete rows together, we add them to the solution, perform recursion, 
 * and then backtrack to explore all possibilities.
 */
void Recursive(char ** matrix, element * Help, size_t d, size_t count, int * Filter, int rows, size_t start){
    if(count == d){
        printDataWithFilter(Help, Filter, d);
        return;
    }
    if(Help[start].was == 1){
        start++;
        Recursive(matrix, Help, d, count, Filter, rows, start);
        start--;
    } else {
        for(int j = 0; j < rows; j++){

            char temp = matrix[j][start];
            int tmp  = Help[start].was;

            if((temp != '_' && tmp == 0)){

            if(!DoTheyCollide(matrix[j], Help, d)){
                    count += check(Help, matrix[j], d, &start);
                    Recursive(matrix, Help, d, count, Filter, rows, start);
                    count -= uncheck(Help, matrix[j], d, &start);
                }
            }
        }
    }
}

int main(void) {
    size_t d = 0;
    int rows = 0;

    int Filter[MaxRowLenght];
    LoadFilter(&d, Filter);

    char ** matrix = LoadData(d, &rows);

    element * Help  = (element*)malloc((size_t)d * sizeof(element)); 
    if (!Help) return 1;

    for(size_t i = 0; i < d; i++){
        Help[i].was = 0;
    }
   
    Recursive(matrix, Help, d, 0, Filter, rows, 0);


    FreeMatrix(matrix, rows);
    free(Help);

    return 0;
}
