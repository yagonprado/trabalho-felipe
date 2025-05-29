#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

// Yago Nascimento do Prado - 1972348
// Lucas Rebouças de Souza - 1924755

// Função para ler o grafo G2
map<string, vector<string>> lerGrafoG2(const string& nomeArquivo) {
    map<string, vector<string>> adj;
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo: " << nomeArquivo << endl;
        return adj;
    }
    string linha;
    while (getline(arquivo, linha)) {
        if (!linha.empty() && linha.back() == ';') {
            linha.pop_back();
        }
        size_t pos = linha.find(';');
        if (pos != string::npos) {
            string u = linha.substr(0, pos);
            string v = linha.substr(pos + 1);
            adj[u].push_back(v);
        }
    }
    // Ordena os vizinhos
    for (auto& par : adj) {
        sort(par.second.begin(), par.second.end());
    }
    return adj;
}

// Busca em profundidade
void busca(const map<string, vector<string>>& adj, const string& atual, set<string>& visitado, vector<string>& ordem) {
    visitado.insert(atual);
    ordem.push_back(atual);
    auto it = adj.find(atual);
    if (it != adj.end()) {
        for (const string& vizinho : it->second) {
            if (visitado.find(vizinho) == visitado.end()) {
                busca(adj, vizinho, visitado, ordem);
            }
        }
    }
}

int main() {
    auto g2 = lerGrafoG2("c:\\Users\\yagon\\codigos\\trabalho-felipe\\g2.txt");
    set<string> visitado;
    vector<string> ordem;
    busca(g2, "a", visitado, ordem); // 'a' é o vértice inicial - substitua pelo vértice desejado

    cout << "Ordem de visitação a partir de 'a': ";
    for (size_t i = 1; i < ordem.size(); ++i) { // começa do 1 para pular 'a'
        cout << ordem[i] << " ";
    }
    cout << endl;
    return 0;
}