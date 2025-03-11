/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-Atividade 2                       */
/*             Objetivo: Obter, Calcular e Mostrar as 5 melhores notas              */
/*                                                                                  */
/*                                  Autor: Guilherme Gallo Migliorini               */
/*                                                                   Data:11/03/2025*/
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

void Notas(float *notas, int candidatoID, int qtdNotas, int maxCandidatos) {
	// SimplificaC'C#o do Ponteiro da Array
	float *notaCandidato = notas + candidatoID;

	// Pede, verifica e Armazena a nota
	for (int s = 0; s < qtdNotas; s++) {
		float temp = 0.0;

		printf("\nNota %d: ", s + 1);
		scanf("%f", &temp);

		// Filtro Contra possiveis erros de digitaC'C#o
		while(temp < 0 || temp  > 10) {
			printf("\nNota %d está! com um valor invalido, que tal tentar novamente? \n", s + 1);
			scanf("%f",  &temp);
		}

		*(notaCandidato + s * maxCandidatos) = temp;
	}

	// Fazendo o Sort das notas (ordem decrescente)
	for (int n = 0; n < qtdNotas - 1; n++) {
		for (int c = n + 1; c < qtdNotas; c++) {
			float notaN = notaCandidato[n * maxCandidatos];
			float notaC = notaCandidato[c * maxCandidatos];

			if (notaN < notaC) {
				float temp = notaN;
				notaCandidato[n * maxCandidatos] = notaC;
				notaCandidato[c * maxCandidatos] = temp;
			}
		}
	}
}

int main() {
	// Minhas Variaveis!
	int maxCandidatos = 0;

	// NC:mero de candidatos
	printf("Por favor, informe quantos Alunos participaram, até no Maximo 50! \n");
	scanf("%i", &maxCandidatos);

	// Filtro para erros
	while (maxCandidatos > 50 || maxCandidatos < 1) {
		printf("Por favor informe um nC:mero de Aluno entre 1 e 50 \n");
		scanf("%i", &maxCandidatos);
	}

	// EnumeraC'C#o para identificar as provas
	enum Provas {
		PE,          // 0
		AC,          // 1
		PP,          // 2
		EB,          // 3
		PROVAS       // 4
	};

	// Meus Vetores! ;)
	char nomes[maxCandidatos][100];
	float PE_N[4][maxCandidatos];         // 4 notas de PE
	float AC_N[5][maxCandidatos];         // 5 notas de AC
	float PP_N[10][maxCandidatos];        // 10 notas de PP
	float EB_N[3][maxCandidatos];         // 3 notas de EB
	float mediasF[PROVAS][maxCandidatos]; // 4 medias das Provas
	float notaMaxima[maxCandidatos];      // Notas mC!ximas

	// Ponteiro para o vetor de nomes
	char *ptrNomes = (char *)nomes;

	// Meu Vetor com ponteiros para as Notas :)!
	float *notas[6] = {
		(float *)PE_N,               // notas[0] aponta para PE
		(float *)AC_N,               // notas[1] aponta para AC
		(float *)PP_N,               // notas[2] aponta para PP
		(float *)EB_N,               // notas[3] aponta para EB
		(float *)mediasF,            // notas[4] aponta para mediasF
		(float *)notaMaxima          // notas[5] aponta para notaMaxima
	};

	// Nomes das provas
	const char *nomesProvas[] = {
		"PE",           // 0
		"AC",           // 1
		"PP",           // 2
		"EB",           // 3
		"notaMaxima"    // 4
	};

	// Tamanho de cada vetor de notas
	const int qtdNotasPorProva[PROVAS] = {
		sizeof(PE_N) / sizeof(PE_N[0]),    // PE tem 4 notas
		sizeof(AC_N) / sizeof(AC_N[0]),    // AC tem 5 notas
		sizeof(PP_N) / sizeof(PP_N[0]),    // PP tem 10 notas
		sizeof(EB_N) / sizeof(EB_N[0])     // EB tem 3 notas
	};

	// Preenchendo as informaC'C5es dos Candidatos
	for (int i = 0; i < maxCandidatos; i++) {
		printf("\nCandidato %i\n", i + 1);

		// Preenche o nome do candidato
		printf("Nome: ");
		scanf("%s", ptrNomes + i * 100);

		// Preenche as notas de cada prova
		for (int n = 0; n < PROVAS; n++) {
			printf("\nInsira as Notas da prova %s:\n", nomesProvas[n]);
			Notas(notas[n], i, qtdNotasPorProva[n], maxCandidatos);

			// Calcula a mC)dia excluindo a maior e a menor nota
			float somaNotas = 0.0;
			for (int a = 1; a < qtdNotasPorProva[n] - 1; a++) {
				somaNotas += notas[n][a * maxCandidatos + i];
			}
            
            //Calcula o peso de cada Prova!
			switch (n) {
			case 0:
				somaNotas = somaNotas * 0.3;
				break;
			case 1:
				somaNotas = somaNotas * 0.1;
				break;
			case 2:
				somaNotas = somaNotas * 0.4;
				break;
			case 3:
				somaNotas = somaNotas* 0.2;
				break;
			}
            
            //Armazena a media dessa prova
			mediasF[n][i] = somaNotas;

			//Somar a Nota a todas as notas para a media Final
			notaMaxima[i] += somaNotas;

			//printf("Final %f", notaMaxima[i]);

			//printf("Média da prova %s para o candidato %d: %f\n", nomesProvas[n], i + 1, mediasF[n][i]);
		}

	}
	// Definir o número de candidatos no pódio
    int podio = maxCandidatos;
    
    //Caso haja mais de 5 aluno mostrar apenas os 5 melhores
    if(maxCandidatos > 5) {
        podio = 5;
    }

    // Ordenar os candidatos pela nota máxima
    for(int n = 0; n < maxCandidatos - 1; n++) {
        for(int c = n + 1; c < maxCandidatos; c++) {
            if(notaMaxima[n] < notaMaxima[c]) {
                float tempNota = notaMaxima[n];
                notaMaxima[n] = notaMaxima[c];
                notaMaxima[c] = tempNota;

                //Copia as strings e as coloca no seu novo destino
                char tempNome[100];
                strcpy(tempNome, nomes[n]);
                strcpy(nomes[n], nomes[c]);
                strcpy(nomes[c], tempNome);
            }
        }
    }

    // Exibir os melhores candidatos
    for (int i = 0; i < podio; i++) {
        printf("\n\nPosição %d: \nAluno: %s \nNota: %.2f", i + 1, nomes[i], notaMaxima[i]);
    }

    return 0;
}