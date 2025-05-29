#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

// Yago Nascimento do Prado - 1972348
// Lucas Rebouças de Souza - 1924755

// Função para ler o grafo G1
map<string, vector<string>> lerGrafoG1(const string& nomeArquivo) {
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
            adj[v].push_back(u);
        }
    }
    // Ordena os vizinhos
    for (auto& par : adj) {
        sort(par.second.begin(), par.second.end());
    }
    return adj;
}

// Busca em largura
void busca(const map<string, vector<string>>& adj, const string& inicio) {
    set<string> visitado;
    queue<string> fila;
    vector<string> ordem;

    fila.push(inicio);
    visitado.insert(inicio);

    while (!fila.empty()) {
        string atual = fila.front();
        fila.pop();
        ordem.push_back(atual);

        for (const string& vizinho : adj.at(atual)) {
            if (visitado.find(vizinho) == visitado.end()) {
                fila.push(vizinho);
                visitado.insert(vizinho);
            }
        }
    }

    cout << "Ordem de visitação a partir de '" << inicio << "': ";
    for (size_t i = 1; i < ordem.size(); ++i) { // começa do 1 para pular 'b'
        cout << ordem[i] << " ";
    }
    cout << endl;
}

int main() {
    auto g1 = lerGrafoG1("c:\\Users\\yagon\\codigos\\trabalho-felipe\\g1.txt");
    busca(g1, "b"); // 'b' é o vértice inicial - substitua pelo vértice desejado
    return 0;
}