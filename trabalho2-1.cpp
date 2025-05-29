#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

// Yago Nascimento do Prado - 1972348
// Lucas Rebouças de Souza - 1924755

// Função para ler um arquivo e criar a lista de adjacência
map<string, vector<pair<string, int>>> lerGrafo(const string& nomeArquivo, bool direcionado = false) {
    map<string, vector<pair<string, int>>> adj;
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo: " << nomeArquivo << endl;
        return adj;
    }
    string linha;
    while (getline(arquivo, linha)) {
        // Remove o ';' do final da linha, se existir
        if (!linha.empty() && linha.back() == ';') {
            linha.pop_back();
        }
        // Divide a linha pelos ';'
        vector<string> partes;
        stringstream ss(linha);
        string item;
        while (getline(ss, item, ';')) {
            if (!item.empty()) partes.push_back(item);
        }
        if (partes.size() >= 2) {
            string u = partes[0];
            string v = partes[1];
            int peso = 1;
            if (partes.size() >= 3) {
                peso = stoi(partes[2]);
            }
            adj[u].push_back({v, peso});
            if (!direcionado) {
                adj[v].push_back({u, peso});
            }
        }
    }
    return adj;
}

// Função para imprimir a lista de adjacência
void imprimirAdj(const map<string, vector<pair<string, int>>>& adj) {
    for (const auto& par : adj) {
        cout << par.first << ": ";
        vector<pair<string, int>> vizinhos = par.second;
        sort(vizinhos.begin(), vizinhos.end());
        for (const auto& vizinho : vizinhos) {
            cout << vizinho.first;
            if (vizinho.second != 1) // Mostra peso só se diferente de 1
                cout << "(" << vizinho.second << ")";
            cout << " ";
        }
        cout << endl;
    }
}

int main() {
    // g1: não direcionado
    auto g1 = lerGrafo("c:\\Users\\yagon\\codigos\\trabalho-felipe\\g1.txt", false);
    // g2: direcionado
    auto g2 = lerGrafo("c:\\Users\\yagon\\codigos\\trabalho-felipe\\g2.txt", true);
    // g3: não direcionado com peso
    auto g3 = lerGrafo("c:\\Users\\yagon\\codigos\\trabalho-felipe\\g3.txt", false);

    cout << "Grafo 1:" << endl;
    imprimirAdj(g1);

    cout << "\nGrafo 2:" << endl;
    imprimirAdj(g2);

    cout << "\nGrafo 3:" << endl;
    imprimirAdj(g3);

    return 0;
}