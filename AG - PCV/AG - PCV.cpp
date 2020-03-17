// AG - PCV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <signal.h>

using namespace std;

int tam_genes=15;
int tam_pop = 100;
int tam_torneio = 50;
int geracoes = 5000;
double prob_mut = 0.15;
double prob_cruz = 0.7;
int dados[15][15];

vector<vector<int>> populacao;


void inicializaPopulacao()
{
	for (int i = 0; i < tam_pop; i++)
	{
		vector<int> individuo;

		for (int j = 0; j < tam_genes; j++)
		{
			individuo.push_back(j); // insere no vetor do individuo
		}

		random_shuffle(individuo.begin(), individuo.end());

		populacao.push_back(individuo); // insere no vetor da populacao
	}
}

int obterPontuacao(vector<int> individuo)
{
	// o score é a soma dos valores dos genes
	int soma = 0;

	for (int i = 0; i < tam_genes-1; i++)
		soma += dados[individuo[i]][individuo[i+1]];
	soma += dados[individuo[14]][individuo[0]];
	return soma;
}

void mutacao(vector<int>& individuo)
{
	// escolhe dois genes aleatoriamente no intervalo [0, tam_genes - 1]
	int gene1 = rand() % tam_genes;
	int gene2;
	do
	{
		gene2 = rand() % tam_genes;
	} while (gene1 == gene2);

	// altera o valor dos genes escolhidos entre si
	int aux = individuo[gene1];
	individuo[gene1] = individuo[gene2];
	individuo[gene2] = aux;
}

void cruzamento(int indice_pai1, int indice_pai2, vector<int>& filho)
{
	// escolhe um ponto aleatoriamente no intervalo [0, tam_genes - 1]
	int ponto = rand() % tam_genes;

	// coloca do indice 0 até o ponto do pai1 no filho
	for (int i = 0; i <= ponto; i++)
		filho.push_back(populacao[indice_pai1][i]);

	// verifica e coloca o que é possivel do pai2
	for (int i = ponto + 1; i < tam_genes; i++)
	{
		bool aux = 0;
		for (int j = 0; j <= ponto; j++)
		{
			if (filho[j] == populacao[indice_pai2][i])
				aux = 1;
		}
		if(!aux)
			filho.push_back(populacao[indice_pai2][i]);
	}

	// coloca os valores faltantes
	if (filho.size() != 15)
	{
		vector<int> falta;
		for (int i = 0; i < 15; i++)
		{
			bool jaexiste = 0;
			for (int j = 0; j < filho.size(); j++)
				if (filho[j] == i)
					jaexiste = 1;
			if (!jaexiste)
				falta.push_back(i);
		}
		// randomiza os valores que faltam
		random_shuffle(falta.begin(), falta.end());
		for (int j = 0; j < falta.size(); j++)
			filho.push_back(falta[j]);
	}

}

int obterMelhor()
{
	int indice_melhor = 0;
	int score_melhor = obterPontuacao(populacao[0]);

	for (int i = 1; i < tam_pop; i++)
	{
		int score = obterPontuacao(populacao[i]);
		if (score < score_melhor)
		{
			indice_melhor = i;
			score_melhor = score;
		}
	}

	return indice_melhor;
}

int main()
{

	clock_t start, end;
	FILE* fp;
	fp = fopen("dados.txt", "r");
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
		{
			fscanf(fp, "%d ", &dados[i][j]);
		}
	start = clock();
	inicializaPopulacao();
	srand(time(NULL));
	for (int i = 0; i < geracoes; i++)
	{
		for (int j = 0; j < tam_torneio; j++)
		{

			// calcula a probabilidade de cruzamento
			double prob = ((double)rand() / ((double)RAND_MAX + 1));

			if (prob < prob_cruz)
			{
				// escolhe dois pais
				int indice_pai1 = rand() % tam_pop;
				int indice_pai2;

				// garante que os índices dos pais não são iguais
				do
				{
					indice_pai2 = rand() % tam_pop;
				} while (indice_pai1 == indice_pai2);

				vector<int> filho;

				// aplica o cruzamento de 1 ponto
				cruzamento(indice_pai1, indice_pai2, filho);

				// calcula a probabilidade de mutação
				prob = ((double)rand() / ((double)RAND_MAX + 1));

				if (prob < prob_mut)
					mutacao(filho);

				int score_pai = obterPontuacao(populacao[indice_pai1]);
				int score_filho = obterPontuacao(filho);

				/*
					se a pontuação (score) do filho for melhor do
					que o pai1, então substitui o pai 1 pelo filho
				*/
				if (score_filho < score_pai)
				{
					// faz a cópia dos genes do filho para o pai
					for (int k = 0; k < tam_genes; k++)
						populacao[indice_pai1][k] = filho[k];
				}
			}
		}

		cout << "Geracao " << i + 1 << endl;
		cout << "Melhor: ";

		int indice_melhor = obterMelhor();
		int score_melhor = obterPontuacao(populacao[indice_melhor]);

		for (int j = 0; j < tam_genes; j++)
			cout << populacao[indice_melhor][j] << " ";

		cout << "\nPontuacao: " << score_melhor << "\n\n";
		if (score_melhor == 291)
			break;
		
	}
	end = clock();
	printf("%f segundos \n", ((float)end - (float)start) / (float)1000);
	system("pause");
}