#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

//crete a struct with an int and array bidimensional
struct Resultado {
    int n;
    int qr[30][30];
};

vector<int> recebeInput(vector<int> &vec, int n){
    int numero;
    int somaTotal = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> numero;
        somaTotal += numero;
        vec.push_back(numero);
    }
    vec.push_back(somaTotal);

    return vec;
}


void printArray(int array[][30], int n) {

    cout << "+";
    for (int j = 0; j < n; j++) {
        cout << "-";
    }
    cout << "+" << endl;

    for (int i = 0; i < n; i++) {
        cout << "|";
        for (int j = 0; j < n; j++) {
            if(array[i][j] == 1){
                cout << "#";
            }
            if(array[i][j] == 0){
                cout << " ";
            }
        }
        cout << "|" << endl;
    }

    cout << "+";
    for (int j = 0; j < n; j++) {
        cout << "-";
    }
    cout << "+" << endl;


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

bool verifyTrue(int array[][30], int n, vector<int> &linhas, vector<int> &colunas, vector<int> &diagonais, vector<int> &difflinhas, vector<int> &diffcolunas, vector<int> &quadrants){

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

void generateArrays(int n, int array[][30], int i, int j, vector<int> &linhas, vector<int> &colunas, vector<int> &diagonais, vector<int> &difflinhas, vector<int> &diffcolunas, vector<int> &quadrants, int pretos, Resultado& res) {

    if (i == n) { // encontrou uma combinação válida
        if(countNumbers1(array, n) == pretos && verifyTrue(array, n, linhas, colunas, diagonais, difflinhas, diffcolunas, quadrants) == true){
            res.n++;
            memcpy(res.qr, array, sizeof(res.qr));
        }
        return;
    }
    if (j == n) { // passou da última coluna, muda para a próxima linha
        generateArrays(n, array, i+1, 0, linhas, colunas, diagonais, difflinhas, diffcolunas, quadrants, pretos, res);
        return;
    }
    array[i][j] = 0; // tenta colocar 0 na posição (i,j)
    generateArrays(n, array, i, j+1, linhas, colunas, diagonais, difflinhas, diffcolunas, quadrants, pretos, res); // faz chamada recursiva para a próxima coluna
    array[i][j] = 1; // tenta colocar 1 na posição (i,j)
    generateArrays(n, array, i, j+1,linhas, colunas, diagonais, difflinhas, diffcolunas, quadrants, pretos, res); // faz chamada recursiva para a próxima coluna
}


int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int qr;

    int aceita = 0;



    int numero;
    cin >> qr;

    for (int i = 0; i < qr; i++) //cada qr code
    {
        aceita = 0;
        int array[30][30] = {0}; // inicializa a matriz com zeros
        int n; //tamanho do array
        int pretos = 0;

        int valida = 0;

        cin >> n;

        vector<int> lb;
        vector<int> cb;
        vector<int> lt;
        vector<int> ct;
        vector<int> qb;
        vector<int> db;

        recebeInput(lb, n);
        recebeInput(cb, n);
        recebeInput(lt, n);
        recebeInput(ct, n);
        recebeInput(qb, 4);
        recebeInput(db, 2);

        pretos = lb[n];

        if(cb[n] != pretos || qb[4] != pretos){ //opha isto resolveu mais casos de teste +20 pontitos
            valida = 1;
            cout << "DEFECT: No QR Code generated!" << endl;
        }

        if (valida == 0){
            Resultado res;
            res.n = aceita;
            memcpy(res.qr, array, sizeof(res.qr));

            generateArrays(n, array, 0, 0, lb, cb, db, lt, ct, qb, pretos, res);

            if(res.n == 0){
                cout << "DEFECT: No QR Code generated!" << endl;
            }
            else if(res.n == 1){
                cout << "VALID: 1 QR Code generated!" << endl;
                printArray(res.qr, n);

            }
            else if(res.n > 1){
                cout << "INVALID: " << res.n << " QR Codes generated!" << endl;
            }
        }

    }
    return 0;
}