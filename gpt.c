#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100 // Definindo o tamanho máximo da sentença
#define MAX_SENTENCES 20 // Definindo o número máximo de sentenças
#define MAX_PROOF_STEPS 100 // Definindo o número máximo de passos da prova

// Protótipos de função
void processSentences(char sentences[][MAX_LENGTH], int count, char *goal);
int canProveGoal(char sentences[][MAX_LENGTH], int count, char *goal, char *proofSteps[], int *proofStepCount);
int isSentenceTrue(char *sentence, char *proofSteps[], int proofStepCount);

int main() {
    char sentences[MAX_SENTENCES][MAX_LENGTH]; // Array para armazenar as sentenças
    char goal[MAX_LENGTH]; // Sentença objetivo
    int count = 0; // Contador de sentenças

    printf("Digite as sentencas de Logica Proposicional (maximo de %d):\n", MAX_SENTENCES);
    
    // Loop para receber várias sentenças até atingir o limite ou uma sentença vazia
    while (count < MAX_SENTENCES) {
        printf("Sentenca %d: ", count + 1);
        fgets(sentences[count], sizeof(sentences[count]), stdin);

        // Removendo o caractere de nova linha, se estiver presente
        if (sentences[count][strlen(sentences[count]) - 1] == '\n')
            sentences[count][strlen(sentences[count]) - 1] = '\0';

        // Verificando se o usuário deseja parar de inserir sentenças
        if (strlen(sentences[count]) == 0)
            break;

        count++;
    }

    // Recebendo a sentença objetivo
    printf("Digite a sentenca objetivo: ");
    fgets(goal, sizeof(goal), stdin);
    if (goal[strlen(goal) - 1] == '\n')
        goal[strlen(goal) - 1] = '\0';

    // Processando as sentenças e verificando se é possível provar o objetivo
    processSentences(sentences, count, goal);

    return 0;
}

// Função para processar as sentenças e verificar se é possível provar o objetivo
void processSentences(char sentences[][MAX_LENGTH], int count, char *goal) {
    printf("\nProva para o objetivo '%s':\n", goal);

    // Exibindo as sentenças recebidas
    printf("\nSentencas fornecidas:\n");
    for (int i = 0; i < count; i++) {
        printf("S%d: %s\n", i + 1, sentences[i]);
    }
    printf("\n");

    // Verificando se é possível provar o objetivo
    char *proofSteps[MAX_PROOF_STEPS];
    int proofStepCount = 0;
    if (canProveGoal(sentences, count, goal, proofSteps, &proofStepCount)) {
        printf("E possivel provar o objetivo '%s'.\n", goal);
        printf("\nProva:\n");
        for (int i = 0; i < proofStepCount; i++) {
            printf("%d: %s\n", i + 1, proofSteps[i]);
        }
    } else {
        printf("Nao e possivel provar o objetivo '%s' com as sentencas fornecidas.\n", goal);
    }
}

// Função para verificar se uma sentença está presente nos passos da prova
int isSentenceTrue(char *sentence, char *proofSteps[], int proofStepCount) {
    for (int i = 0; i < proofStepCount; i++) {
        if (strstr(proofSteps[i], sentence) != NULL)
            return 1; // Sentença encontrada nos passos da prova
    }
    return 0; // Sentença não encontrada
}

// Função para verificar se é possível provar o objetivo com base nas sentenças fornecidas
int canProveGoal(char sentences[][MAX_LENGTH], int count, char *goal, char *proofSteps[], int *proofStepCount) {
    // Array para marcar se uma sentença já foi usada como prova
    int used[MAX_SENTENCES];
    memset(used, 0, sizeof(used));

    // Adicionando as sentenças dadas como passos iniciais da prova
    for (int i = 0; i < count; i++) {
        if (strstr(sentences[i], goal) != NULL) {
            proofSteps[(*proofStepCount)++] = sentences[i];
            used[i] = 1;
        }
    }

    int isProven = 0; // Indicador se o objetivo foi provado
    while (!isProven) {
        isProven = 1;
        for (int i = 0; i < count; i++) {
            if (!used[i]) {
                // Verificando se a sentença i pode ser usada como prova
                // Se a sentença contiver apenas uma letra, ela é uma proposição verdadeira
                if (strlen(sentences[i]) == 1) {
                    proofSteps[(*proofStepCount)++] = sentences[i];
                    used[i] = 1;
                    isProven = 0;
                    printf("Proposicao verdadeira: %s\n", sentences[i]);
                }
                // Verificando se a sentença i pode ser usada para provar o objetivo
                if (strstr(sentences[i], goal) != NULL) {
                    proofSteps[(*proofStepCount)++] = sentences[i];
                    used[i] = 1;
                    isProven = 0;
                    printf("Usando Modus Ponens: %s\n", sentences[i]);
                }
            }
        }
    }

    return isSentenceTrue(goal, proofSteps, *proofStepCount);
}
