#include <iostream>
#include <fstream>
using namespace std;

struct Cor{
    int cod;
};

class MiniCout {
private:
    ofstream arquivo;

public:

    MiniCout(const string& nomeArquivo){
        arquivo.open(nomeArquivo);
    }

    template<typename T>
    MiniCout& operator<<(const T& valor) {
        cout << valor;
        if(arquivo.is_open()){
            arquivo << valor;
        }
        return *this;
    }

    MiniCout& operator<<(ostream& (*func)(ostream&)) {
        func(cout);
        if (arquivo.is_open()) {
            func(arquivo);
        }
        return *this;
    }
    // 👇 operador para Cor
    MiniCout& operator<<(const Cor& c) {
        cout << "\033[" << c.cod << "m";
        return *this;
    }
};

Cor cor(int codigo) {
    return {codigo};
}
ostream& vermelho(ostream & os){
    return os << "\033[31m";
}

ostream& reset(ostream & os){
    return os << "\033[0m";
}

int main() {
    MiniCout mc("log.txt");
    struct Cor colour;

    mc << vermelho << "Numero:" << reset << 42 << endl;
    mc << cor(30) << "produzindo meu proprio cout " << cor(0)  << 42 << " eh louco" << endl;
}