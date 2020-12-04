//
// Created by juan on 23/10/20.
//
#include "Tools.h"
/*Realiza la lectura de una matriz, se hace paso por referencia.
M: es la matriz que tiene los valores.
datafile: es el fichero donde está almacenada la matriz
*/

/*
   Realiza la lectura del vector, se hace paso por referencia.
   V: es el vector que tiene los valores.
   datafile: es el fichero donde está almacenada el vector
*/



void WriteMatrix(const vector< vector<double > > &M, string filename, bool flag_append)
{
    std::fstream fout;

    if(flag_append)
        fout.open(filename,fstream::app|fstream::out );
    else
        fout.open(filename,std::ios::out);
    fout << (int)M.size() << " " << (int)M[0].size() <<endl;
    for(int i = 0; i < M.size(); i++){
        for(int j = 0; j < M[i].size(); j++)
            if (j!= M[0].size()-1)
                fout << M[i][j]<<  setw(15);
            else
                fout << M[i][j];
        fout << endl;
    }
    fout.close();
}
void WriteVector(const vector<double> &V, string filename, bool flag_append)
{
    std::fstream fout;
    if(flag_append)
        fout.open(filename,fstream::app|fstream::out );
    else
        fout.open(filename,std::ios::out);
    fout << (int)V.size() << " 1 "<<endl;
    for(int i = 0; i < V.size(); i++)
        fout <<V[i]<< endl;
    fout.close();

}

ostream &operator<<(ostream &os, const vector< vector<double> > &M)
{
    for(int i = 0; i < M.size(); i++)
    {
        for(auto x:M[i])
        {
            os << setw(15) << x << setw(15);
        }
        os <<endl;
    }
    return os;
}
ostream &operator<<(ostream &os, const vector<double> &V)
{
    for(auto x:V)
        os << x << " ";
    os <<endl;
    return os;
}



// tools to print data
ostream &operator<<(ostream &os, const vector<vector<unsigned char> > &M) {
    for (unsigned long i = 0; i < M.size(); i++) {
        for (auto x:M[i]) {
            os << setw(5) << (int)x << setw(5);
        }
        os << endl;
    }
    return os;
}

ostream &operator<<(ostream &os, const vector<unsigned char> &V) {
    for (auto x:V)
        os << x << " ";
    os << endl;
    return os;
}