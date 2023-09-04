#include <iostream>
#include <fstream>
#include <string>
#define TAM 10

using namespace std;

void Listafile();
void inserirInicio();

typedef struct
{
    string rg;
    string nome;
}no;

int main ()
{
    string nome;
    string rg;

    no lista[TAM];


    return 0;
}

void inserirInicio()
{
    int i = 0;

    while(!(lista[i].rg.empty()))
    {
        i++;
    }

    cout << "RG: \n" << endl;
    cin >> lista[i].rg;

    cout << "NOME: \n" << endl;
    cin >> lista[i].nome;


}

void Listafile()
{
    ifstream myfile ("NomeRG10.txt");

    if (myfile.is_open())
    {
        while (getline (myfile, rg, ',') && getline (myfile, nome, ','))
        {
          cout << rg << endl;

          cout << nome << endl;
        }
        else
        {
        }
    }

    myfile.close();


    else cout << "Unable to open file";
}

