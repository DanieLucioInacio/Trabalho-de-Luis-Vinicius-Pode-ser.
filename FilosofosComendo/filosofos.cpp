
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

using namespace std;

mutex ThungMutex;
condition_variable ThungEspera;

queue<int> ThungFila;

bool ThungGarfos[5] = {false, false, false, false, false};
int ThungRefeicoes[5] = {0, 0, 0, 0, 0};

void pegarGarfos(int ThungId) {

    unique_lock<mutex> lock(ThungMutex);

    ThungFila.push(ThungId);

    cout << "Filosofo " << ThungId << " entrou na fila." << endl;

    ThungEspera.wait(lock, [&]() {

        int ThungG1 = ThungId;
        int ThungG2 = (ThungId + 1) % 5;

        return ThungFila.front() == ThungId &&
               !ThungGarfos[ThungG1] &&
               !ThungGarfos[ThungG2];
    });

    ThungFila.pop();

    ThungGarfos[ThungId] = true;
    ThungGarfos[(ThungId + 1) % 5] = true;

    cout << "Filosofo " << ThungId << " esta comendo." << endl;

    ThungEspera.notify_all();
}

void devolverGarfos(int ThungId) {

    lock_guard<mutex> lock(ThungMutex);

    ThungGarfos[ThungId] = false;
    ThungGarfos[(ThungId + 1) % 5] = false;

    ThungRefeicoes[ThungId]++;

    cout << "Filosofo " << ThungId << " terminou de comer." << endl;

    ThungEspera.notify_all();
}

void filosofo(int ThungId) {

    for (int ThungI = 0; ThungI < 3; ThungI++) {

        cout << "Filosofo " << ThungId << " esta pensando." << endl;

        this_thread::sleep_for(chrono::milliseconds(200));

        pegarGarfos(ThungId);

        this_thread::sleep_for(chrono::milliseconds(300));

        devolverGarfos(ThungId);
    }
}

int main() {

    thread ThungThreads[5];

    cout << "Inicio do jantar dos filosofos!" << endl;

    // Criando os cinco filosofos
    for (int ThungI = 0; ThungI < 5; ThungI++) {
        ThungThreads[ThungI] = thread(filosofo, ThungI);
    }

    // Esperando todos terminarem
    for (int ThungI = 0; ThungI < 5; ThungI++) {
        ThungThreads[ThungI].join();
    }

    cout << "\n===== TESTES =====" << endl;

    int ThungTotal = 0;
    bool ThungTodosComeram = true;

    for (int ThungI = 0; ThungI < 5; ThungI++) {

        cout << "Filosofo " << ThungI
             << " comeu " << ThungRefeicoes[ThungI]
             << " vezes." << endl;

        ThungTotal += ThungRefeicoes[ThungI];

        if (ThungRefeicoes[ThungI] != 3) {
            ThungTodosComeram = false;
        }
    }

    cout << "\nTotal de refeicoes: " << ThungTotal << "/15" << endl;

    if (ThungTodosComeram && ThungTotal == 15) {
        cout << "[OK] Todos conseguiram comer 3 vezes!" << endl;
    } else {
        cout << "[ERRO] Nem todos conseguiram comer." << endl;
    }

    cout << "Fim do programa!" << endl;

    return 0;
}
