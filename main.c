#include <stdio.h>
#include <stdlib.h>

/**
 * 
 *  @author uross
 */

void printTable(int s[][9]) {
    printf("+-----------------+\n");
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i) {
            printf("|-----+-----+-----|\n");
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0) {
                printf("|");
            }
            printf("%d", s[i][j]);
            if ((j + 1) % 3 != 0) {
                printf(" ");
            }
        }
        printf("|\n");
    }
    printf("+-----------------+\n");
}

void loadTable(int sudoku[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            scanf("%d", &sudoku[i][j]);
        }
    }
}

/* proverava da li broj num moze biti na poziciji [row][col] */
int isPossible(int s[][9], int row, int col, int num) {
    // koordinate gornjeg levog coska bloka 3x3 u kom se nalazi tacka koju posmatramo
    int row1 = (row / 3) * 3;
    int col1 = (col / 3) * 3;

    for (int i = 0; i < 9; i++) {
        if (s[row][i] == num) return 0; // nema duplikata u redu
        if (s[i][col] == num) return 0; // nema duplikata u koloni
        if (s[row1 + i % 3][col1 + i / 3] == num) return 0; //nema duplikata u bloku 3x3
    }
    return 1;
}

int fillSudoku(int s[][9], int row, int col) {
    if (s[row][col] != 0) { // ako je polje vec popunjeno
        if (col + 1 < 9) {
            return fillSudoku(s, row, col + 1); // popunjavati dalje taj red
        } else if (row + 1 < 9) {
            return fillSudoku(s, row + 1, 0); // ako smo dosli do kraja reda, prelazimo na sledeci
        } else {
            return 1; // ako nema vise redova ni kolona, znaci da smo zavrsili
        }
    } else { // ako polje nije popunjeno
        for (int num = 1; num <= 9; num++) { // vrtimo sve opcije od 1 do 9
            if (isPossible(s, row, col, num)) { // ako je dozvoljeno staviti ovaj broj na ovu poziciju
                s[row][col] = num; // postavljamo taj broj
                if (fillSudoku(s, row, col)) { // i proveravamo da li to moze dovesti do resenja
                    return 1; // ako moze, to je to
                } else { // ako ne,
                    s[row][col] = 0; // stavljamo broj na 0, tj. isprobavamo sledecu opciju
                }
            }
        }
    }
    return 0;
}

int main() {

    int sudoku[9][9];

    loadTable(sudoku);
    printTable(sudoku);

    printf("\n");
    printf("*******************\n\n");

    if (fillSudoku(sudoku, 0, 0)) {
        printTable(sudoku);
    } else {
        printf("NEMA RESENJA!\n");
    }

    return (0);
}

