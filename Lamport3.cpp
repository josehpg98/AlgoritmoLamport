#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
vector<vector<int>> criaMatriz(int colunas, int linhas)
{
    vector<vector<int>> m(linhas, vector<int>(colunas, 0));
    return m;
}
void contadorFrequenciaProcessos(vector<vector<int>>& pN, int quantProcessos)
{
    for (int j = 0; j < quantProcessos; j++)
    {
        int frequencia = rand() % 10 + 1;
        for (int i = 0; i < 10; i++)
        {
            pN[i][j] = i * frequencia;
        }
    }
}
void mostrarMatrizProcessos(const vector<vector<int>>& pN, int quantProcessos)
{
    cout << "\nMatriz de Processos:\n";
    for (int i = 0; i < quantProcessos; i++)
    {
        cout << "Processo " << i << ": ";
        for (int j = 0; j < 10; j++)
        {
            cout << pN[j][i] << "\t";
        }
        cout << endl;
    }
}
int ajustaContadorProcesso(vector<vector<int>>& pN, int tempoOrigem, int processoDestino, int tempoDestino)
{
    int frequencia = pN[1][processoDestino] - pN[0][processoDestino];
    int valorTrocado = 0;

    for (int i = 0; i < 10; i++)
    {
        if (tempoDestino == pN[i][processoDestino])
        {
            pN[i][processoDestino] = tempoOrigem + frequencia;
            valorTrocado = pN[i][processoDestino];
        }
        else if (tempoDestino < pN[i][processoDestino])
        {
            pN[i][processoDestino] = pN[i - 1][processoDestino] + frequencia;
        }
    }
    return valorTrocado;
}
void mostrarUltimoEvento(const vector<vector<int>>& eventos)
{
    int ultimoEvento = eventos.size() - 1;

    cout << endl;
    cout << "O processo " << eventos[ultimoEvento][0] << " enviou no tempo " << eventos[ultimoEvento][1];
    cout << " para o processo " << eventos[ultimoEvento][2] << " que recebeu no tempo " << eventos[ultimoEvento][3] << endl;

    if (eventos[ultimoEvento][4] != 0)
    {
        int frequencia = eventos[ultimoEvento][4] - eventos[ultimoEvento][1];
        cout << "Foi necessário trocar o tempo " << eventos[ultimoEvento][3] << " pelo tempo " << eventos[ultimoEvento][4];
        cout << " (tempo de envio " << eventos[ultimoEvento][1] << " mais a frequência do destino " << frequencia << ")" << endl;
    }

    cout << endl;
}
int main()
{
    srand(time(nullptr));
    int quantProcessos;
    cout << "Insira o número de processos desejados: ";
    cin >> quantProcessos;
    if (quantProcessos >= 2)
    {
        vector<vector<int>> pN = criaMatriz(quantProcessos, 10);
        contadorFrequenciaProcessos(pN, quantProcessos);
        vector<vector<int>> eventos = criaMatriz(5, 1);
        string acao;
        while (true)
        {
            mostrarMatrizProcessos(pN, quantProcessos);
            cout << "\n* Novo evento *\n";
            int processoOrigem, tempoOrigem, processoDestino, tempoDestino;
            cout << "Processo de origem: ";
            cin >> processoOrigem;
            if (processoOrigem >= 0 && processoOrigem < quantProcessos)
            {
                cout << "Tempo de origem: ";
                cin >> tempoOrigem;

                if (tempoOrigem >= 0 && tempoOrigem <= (tempoOrigem * 9) && tempoOrigem % (pN[1][processoOrigem] - pN[0][processoOrigem]) == 0)
                {
                    cout << "Processo de destino: ";
                    cin >> processoDestino;

                    if (processoDestino >= 0 && processoDestino < quantProcessos)
                    {
                        cout << "Tempo de destino: ";
                        cin >> tempoDestino;

                        if (tempoDestino >= 0 && tempoDestino <= (tempoDestino * 9) && tempoDestino % (pN[1][processoDestino] - pN[0][processoDestino]) == 0)
                        {
                            int novoTempoDestino = 0;

                            if (tempoOrigem < tempoDestino)
                            {
                                novoTempoDestino = 0;
                            }
                            else
                            {
                                novoTempoDestino = ajustaContadorProcesso(pN, tempoOrigem, processoDestino, tempoDestino);
                            }

                            vector<int> evento = {processoOrigem, tempoOrigem, processoDestino, tempoDestino, novoTempoDestino};
                            eventos.push_back(evento);
                            mostrarUltimoEvento(eventos);
                            mostrarMatrizProcessos(pN, quantProcessos);
                        }
                        else
                        {
                            cout << "Tempo de destino " << tempoDestino << " é inválido para o processo " << processoDestino << "!" << endl;
                        }
                    }
                    else
                    {
                        cout << "O ID " << processoDestino << " é inválido!" << endl;
                    }
                }
                else
                {
                    cout << "Tempo de origem " << tempoOrigem << " é inválido para o processo " << processoOrigem << "!" << endl;
                }
            }
            else
            {
                cout << "O ID " << processoOrigem << " é inválido!" << endl;
            }

            cout << "Deseja sair? (S/N): ";
            cin >> acao;

            if (acao == "S" || acao == "s")
            {
                break;
            }
        }
    }
    else
    {
        cout << "Erro na entrada da quantidade de processos! Programa encerrado." << endl;
    }
    return 0;
}
