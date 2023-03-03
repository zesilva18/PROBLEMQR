#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


int GLOBAL = 0;
int MAX = 30;

void printArray(int array[][30], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << array[i][j] << " "; // imprime o array
        }
        cout << endl;
    }
    cout << endl;
}

int countNumbers1(int array[][30], int n){
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(array[i][j] == 1){
                count++;
            }
        }
    }
    return count;

}

bool linhasColunasCheck(int array[][30], int n, vector<int> &linhas, vector<int> &colunas, vector<int> &diagonais, vector<int> &difflinhas, vector<int> &diffcolunas){

    int line = 0;
    int column = 0;
    int diagonal = 0;
    int inversediagonal = 0;
    int countTransLinhas = 0;
    int countTransColunas = 0;

    for (int i = 0; i < n; i++) {

        int valorLinha = array[i][0];
        countTransLinhas = 0;
        int valorColuna = array[0][i];
        countTransColunas = 0;

        for (int j = 0; j < n; j++) {

            if(array[i][j] == 1){ //linhas
                line++;
            }
            if(array[j][i] == 1){ //colunas
                column++;
            }

            if(i == j && array[i][j] == 1){ //diagonias
                diagonal++;
            }

            if(n - 1 == j + i && array[i][j] == 1){ //inversediagonais
                inversediagonal++;

            }

            if(array[i][j] != valorLinha){ //transições de linhas
                countTransLinhas++;
            }

            if(array[j][i] != valorColuna){ //transições de colunas
                countTransColunas++;
            }

            valorColuna = array[j][i];
            valorLinha = array[i][j];

        }
        if(line != linhas[i] || column != colunas[i]){
            return false;
        }

        if(countTransLinhas != difflinhas[i]){
            return false;
        }

        if(countTransColunas != diffcolunas[i]){
            return false;
        }
        line = 0;
        column = 0;
    }

    if(diagonal != diagonais[0] || inversediagonal != diagonais[1]){
        return false;
    }

    return true;
}

void generateArrays(int n, int array[][30], int i, int j, vector<int> &linhas, vector<int> &colunas, vector<int> &diagonais, vector<int> &difflinhas, vector<int> &diffcolunas) {
    if (i == n) { // encontrou uma combinação válida
        if(countNumbers1(array, n) == 2 && linhasColunasCheck(array, n, linhas, colunas, diagonais, difflinhas, diffcolunas) == true){
            printArray(array, n); // imprime o array
            GLOBAL++;
        }
        return;
    }
    if (j == n) { // passou da última coluna, muda para a próxima linha
        generateArrays(n, array, i+1, 0, linhas, colunas, diagonais, difflinhas, diffcolunas);
        return;
    }
    array[i][j] = 0; // tenta colocar 0 na posição (i,j)
    generateArrays(n, array, i, j+1, linhas, colunas, diagonais, difflinhas, diffcolunas); // faz chamada recursiva para a próxima coluna
    array[i][j] = 1; // tenta colocar 1 na posição (i,j)
    generateArrays(n, array, i, j+1,linhas, colunas, diagonais, difflinhas, diffcolunas); // faz chamada recursiva para a próxima coluna
}


int main() {
    int n = 3; // tamanho do array
    int array[30][30] = {0}; // inicializa a matriz com zeros
    vector <int> linhas;
    vector <int> colunas;
    vector <int> diagonais;
    vector <int> difflinhas;
    vector <int> diffcolunas;
    linhas.push_back(1);
    linhas.push_back(0);
    linhas.push_back(1);
    colunas.push_back(1);
    colunas.push_back(0);
    colunas.push_back(1);

    difflinhas.push_back(1);
    difflinhas.push_back(0);
    difflinhas.push_back(1);

    diffcolunas.push_back(1);
    diffcolunas.push_back(0);
    diffcolunas.push_back(1);

    diagonais.push_back(2);
    diagonais.push_back(0);

    generateArrays(n, array, 0, 0, linhas, colunas, diagonais, difflinhas, diffcolunas);
    cout << GLOBAL << endl;
    return 0;
}