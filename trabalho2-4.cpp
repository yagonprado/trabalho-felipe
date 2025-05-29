#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
#include <sstream>
#include <climits>
#include <set>

using namespace std;

// Yago Nascimento do Prado - 1972348
// Lucas Rebouças de Souza - 1924755

// Função para ler o grafo G3
map<string, vector<pair<string, int>>> lerGrafoG3(const string& nomeArquivo) {
    map<string, vector<pair<string, int>>> adj;
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
        vector<string> partes;
        stringstream ss(linha);
        string item;
        while (getline(ss, item, ';')) {
            if (!item.empty()) partes.push_back(item);
        }
        if (partes.size() >= 3) {
            string u = partes[0];
            string v = partes[1];
            int peso = stoi(partes[2]);
            adj[u].push_back({v, peso});
            adj[v].push_back({u, peso});
        }
    }
    return adj;
}

// Algoritmo de Dijkstra para menor caminho
void dijkstra(const map<string, vector<pair<string, int>>>& adj, const string& origem, const string& destino) {
    map<string, int> dist;
    map<string, string> prev;
    set<string> visitado;
    for (const auto& par : adj) {
        dist[par.first] = INT_MAX;
    }
    dist[origem] = 0;

    // Min-heap: (distância, vértice)
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> fila;
    fila.push({0, origem});

    while (!fila.empty()) {
        auto [d, u] = fila.top();
        fila.pop();
        if (visitado.count(u)) continue;
        visitado.insert(u);

        for (const auto& [v, peso] : adj.at(u)) {
            if (dist[v] > dist[u] + peso) {
                dist[v] = dist[u] + peso;
                prev[v] = u;
                fila.push({dist[v], v});
            }
        }
    }

    if (dist[destino] == INT_MAX) {
        cout << "Não existe caminho entre " << origem << " e " << destino << "." << endl;
        return;
    }

    // Reconstruir caminho
    vector<pair<string, string>> caminho_arestas;
    string atual = destino;
    while (atual != origem) {
        string ant = prev[atual];
        caminho_arestas.push_back({ant, atual});
        atual = ant;
    }
    reverse(caminho_arestas.begin(), caminho_arestas.end());

    cout << "Custo do menor caminho entre " << origem << " e " << destino << ": " << dist[destino] << endl;
    cout << "Arestas do caminho: ";
    for (const auto& aresta : caminho_arestas) {
        cout << "(" << aresta.first << "," << aresta.second << ") ";
    }
    cout << endl;
}

int main() {
    auto g3 = lerGrafoG3("c:\\Users\\yagon\\codigos\\trabalho-felipe\\g3.txt");
    dijkstra(g3, "x", "t"); // 'x' é o vértice de origem e 't' é o destino - substituir conforme necessário
    return 0;
}