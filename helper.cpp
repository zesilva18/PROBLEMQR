#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
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

bool linhasColunasCheck(int array[][30], int n, vector<int> &linhas, vector<int> &colunas, vector<int> &diagonais, vector<int> &difflinhas, vector<int> &diffcolunas, vector<int> &quadrants){

    int line = 0;
    int column = 0;
    int diagonal = 0;
    int inversediagonal = 0;
    int countTransLinhas = 0;
    int countTransColunas = 0;
    int quadrantsEqual[4] = {0,0,0,0};

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

            //quadrante 1
            if(i < floor(n/2) && j >= floor(n/2) && array[i][j] == 1){
                quadrantsEqual[0]++;
            }

            //quadrante 2
            else if(i < floor(n/2) && j < floor(n/2) && array[i][j] == 1){
                quadrantsEqual[1]++;
            }

            //quadrante 3
            else if(i >= floor(n/2) && j < floor(n/2) && array[i][j] == 1){
                quadrantsEqual[2]++;
            }

            //quadrante 4
            else if (i >= floor(n/2) && j >= floor(n/2) && array[i][j] == 1){
                quadrantsEqual[3]++;
            }

            valorColuna = array[j][i];
            valorLinha = array[i][j];

        }

        if(line != linhas[i] || column != colunas[i] || countTransLinhas != difflinhas[i] || countTransColunas != diffcolunas[i]){
            return false;
        }


        line = 0;
        column = 0;
    }

    if(diagonal != diagonais[0] || inversediagonal != diagonais[1]){
        return false;
    }

    for(int i = 0; i < 4; i++){
        if(quadrantsEqual[i] != quadrants[i]){
            return false;
        }
    }

    return true;
}

void generateArrays(int n, int array[][30], int i, int j, vector<int> &linhas, vector<int> &colunas, vector<int> &diagonais, vector<int> &difflinhas, vector<int> &diffcolunas, vector<int> &quadrants) {
    if (i == n) { // encontrou uma combinação válida
        if(countNumbers1(array, n) == 8 && linhasColunasCheck(array, n, linhas, colunas, diagonais, difflinhas, diffcolunas, quadrants) == true){
            printArray(array, n); // imprime o array
            GLOBAL++;
        }
        return;
    }
    if (j == n) { // passou da última coluna, muda para a próxima linha
        generateArrays(n, array, i+1, 0, linhas, colunas, diagonais, difflinhas, diffcolunas, quadrants);
        return;
    }
    array[i][j] = 0; // tenta colocar 0 na posição (i,j)
    generateArrays(n, array, i, j+1, linhas, colunas, diagonais, difflinhas, diffcolunas, quadrants); // faz chamada recursiva para a próxima coluna
    array[i][j] = 1; // tenta colocar 1 na posição (i,j)
    generateArrays(n, array, i, j+1,linhas, colunas, diagonais, difflinhas, diffcolunas, quadrants); // faz chamada recursiva para a próxima coluna
}


int main() {
    //AQUI TU METES AS MERDAS QUE TU QUERES TESTAR, SE QUERES UM ARRAY DE 5X5 TENS DE FAZER 5 PUSH PARA CADA MATRIZ MENOS AS DOS QUADRANTES E DAS COLUNAS
    //O QUE TENHO FEITO E PARA O EXEMPLO 2 DO ENUNCIADO, É SO CORRERES
    //ATENCAO LINHA 126, AQUELE 8 É O NUMERO DE 1S QUE TEM O ARRAY(CENAS PRETAS), NOS NO MAIN TEMOS UMA FUNCAO QUE CALCULA LOGO, MAS N ME APETECEU FAZER
    //O QUE PODES TENTAR FAZER É USANDO AS FUNCOES DO PROBLEMAA, EXPRIMENTAS E VE SE BATE, SUPOSTAMENTE TEM DE BATER PQ A UNICA DIFERENCA E QUE AQUI NAO LEIO O INPUT, APENAS METO LOGO NOS VETORES CORRESPONDENTES
    int n = 4; // tamanho do array
    int array[30][30] = {0}; // inicializa a matriz com zeros
    vector <int> linhas;
    vector <int> colunas;
    vector <int> diagonais;
    vector <int> difflinhas;
    vector <int> diffcolunas;
    vector <int> quadrants;

    linhas.push_back(2);
    linhas.push_back(2);
    linhas.push_back(2);
    linhas.push_back(2);

    colunas.push_back(2);
    colunas.push_back(2);
    colunas.push_back(2);
    colunas.push_back(2);

    difflinhas.push_back(3);
    difflinhas.push_back(3);
    difflinhas.push_back(3);
    difflinhas.push_back(3);


    diffcolunas.push_back(1);
    diffcolunas.push_back(1);
    diffcolunas.push_back(1);
    diffcolunas.push_back(1);


    quadrants.push_back(2);
    quadrants.push_back(2);
    quadrants.push_back(2);
    quadrants.push_back(2);

    diagonais.push_back(2);
    diagonais.push_back(2);

    generateArrays(n, array, 0, 0, linhas, colunas, diagonais, difflinhas, diffcolunas, quadrants);
    cout << GLOBAL << endl;
    return 0;
}