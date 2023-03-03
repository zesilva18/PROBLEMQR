#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> recebeInput(vector<int> &vec, int n){
    int numero;
    for (int i = 0; i < n; i++)
    {
        cin >> numero;
        vec.push_back(numero);
    }
    return vec;
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

void generateArrays(int n, int array[][30], int i, int j) {
    if (i == n) { // encontrou uma combinação válida
        if(countNumbers1(array, n) == 2){
            cout<<"achou possivel"<<endl;
        }
        return;
    }
    if (j == n) { // passou da última coluna, muda para a próxima linha
        generateArrays(n, array, i+1, 0);
        return;
    }
    array[i][j] = 0; // tenta colocar 0 na posição (i,j)
    generateArrays(n, array, i, j+1); // faz chamada recursiva para a próxima coluna
    array[i][j] = 1; // tenta colocar 1 na posição (i,j)
    generateArrays(n, array, i, j+1); // faz chamada recursiva para a próxima coluna
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int qr;

    int numero;
    cin >> qr;
    for (int i = 0; i < qr; i++) //cada qr code
    {
        int n; //tamanho do array
        int pretos = 0;

        cin >> n;

        //print n
        cout << n << endl;


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

        //print lb
        for (int i = 0; i < 4; i++)
        {
            pretos = pretos + qb[i];
        }

        int array[30][30] = {0}; // inicializa a matriz com zeros

        generateArrays(n, array, 0, 0);

    }

    return 0;
}
