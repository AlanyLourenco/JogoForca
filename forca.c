#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "forca.h"

typedef struct no {
    char letra;
    struct no* prox;
} No;

void inicializar_fila(Fila* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

int fila_vazia(Fila* fila) {
    return fila->inicio == NULL;
}

void inserir_na_fila(Fila* fila, char letra) {
    No* novo_no = (No*) malloc(sizeof(No));
    novo_no->letra = letra;
    novo_no->prox = NULL;
    if (fila_vazia(fila)) {
        fila->inicio = novo_no;
    } else {
        fila->fim->prox = novo_no;
    }
    fila->fim = novo_no;
}

int tamanho_da_fila(Fila* fila) {
    No* no_atual = fila->inicio;
    int tamanho = 0;
    while (no_atual != NULL) {
        tamanho++;
        no_atual = no_atual->prox;
    }
    return tamanho;
}

void imprimir_fila(Fila* fila) {
    No* no_atual = fila->inicio;
    while (no_atual != NULL) {
        printf("%c ", no_atual->letra);
        no_atual = no_atual->prox;
    }
    printf("\n");
}

void desalocar_fila(Fila* fila) {
    No* no_atual = fila->inicio;
    while (no_atual != NULL) {
        No* no_aux = no_atual->prox;
        free(no_atual);
        no_atual = no_aux;
    }
    inicializar_fila(fila);
}

void inicializar_palavra(Palavra* palavra) {
    palavra->palavra[0] = '\0';
    palavra->tamanho = 0;
}

void inserir_letra_na_palavra(Palavra* palavra, char letra) {
    palavra->palavra[palavra->tamanho] = letra;
    palavra->tamanho++;
    palavra->palavra[palavra->tamanho] = '\0';
}

int tamanho_da_palavra(Palavra* palavra) {
    return palavra->tamanho;
}

void imprimir_palavra(Palavra* palavra) {
    printf("%s\n", palavra->palavra);
}

void ler_palavra_do_arquivo(FILE* arquivo, Palavra* palavra) {
    char linha[MAX_PALAVRA];
    int tamanho_minimo, tamanho_maximo;
    fscanf(arquivo, "%d %d\n", &tamanho_minimo, &tamanho_maximo);
    do {
        fgets(linha, MAX_PALAVRA, arquivo);
        linha[strcspn(linha, "\n")] = '\0';
    } while (strlen(linha) < tamanho_minimo || strlen(linha) > tamanho_maximo);
    strcpy(palavra->palavra, linha);
    palavra->tamanho = strlen(linha);
}

int escolher_nivel() {
    int opcao;
    printf("\n");
    printf("Escolha o nivel de dificuldade:\n");
    printf("1 - Facil\n");
    printf("2 - Medio\n");
    printf("3 - Dificil\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

void enfileirar(Fila* fila, char letra) {
    if (tamanho_da_fila(fila) < MAX_TAMANHO_FILA) {
        inserir_na_fila(fila, letra);
    } else {
        printf("Fila cheia.\n");
    }
}

int verificar_letra_na_palavra(Palavra* palavra, char letra) {
    for (int i = 0; i < tamanho_da_palavra(palavra); i++) {
        if (palavra->palavra[i] == letra) {
            return 1;
        }
    }
    return 0;
}

int verificar_palavra_descoberta(Palavra* palavra, Fila* letras_digitadas) {
    for (int i = 0; i < tamanho_da_palavra(palavra); i++) {
        int letra_encontrada = 0;
        No* no_atual = letras_digitadas->inicio;
        while (no_atual != NULL) {
            if (palavra->palavra[i] == no_atual->letra) {
                letra_encontrada = 1;
                break;
            }
            no_atual = no_atual->prox;
        }
        if (!letra_encontrada) {
            return 0;
        }
    }
    return 1;
}

void jogar() {
    int nivel = escolher_nivel();
    FILE* arquivo;
    if (nivel == 1) {
        arquivo = fopen("arquivTxt/facil.txt", "r");
    } else if (nivel == 2) {
        arquivo = fopen("arquivTxt/medio.txt", "r");
    } else if (nivel == 3) {
        arquivo = fopen("arquivTxt/dificil.txt", "r");
    } else {
        printf("Opcao invalida.\n");
        return;
    }
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }
    srand(time(NULL));
    Palavra palavra_secreta;
    inicializar_palavra(&palavra_secreta);
    ler_palavra_do_arquivo(arquivo, &palavra_secreta);
    fclose(arquivo);
    Fila letras_digitadas;
    inicializar_fila(&letras_digitadas);
    char letra;
    int erros = 0;
    printf("\nA palavra tem %d letras.\n\n", tamanho_da_palavra(&palavra_secreta));
    while (erros < 7) {
        printf("Letras digitadas: ");
        imprimir_fila(&letras_digitadas);
        printf("\n");
        for (int i = 0; i < tamanho_da_palavra(&palavra_secreta); i++) {
            if (i == 0 || i == tamanho_da_palavra(&palavra_secreta) - 1) {
                printf("%c ", palavra_secreta.palavra[i]);
            } else {
                int achou = 0;
                No* no_atual = letras_digitadas.inicio;
                while (no_atual != NULL) {
                    if (no_atual->letra == palavra_secreta.palavra[i]) {
                        printf("%c ", no_atual->letra);
                        achou = 1;
                        break;
                    }
                    no_atual = no_atual->prox;
                }
                if (!achou) {
                    printf("_ ");
                }
            }
        }
        printf("\n\n");
        if (tamanho_da_fila(&letras_digitadas) >= 1) {
            printf("Deseja arriscar a palavra? (s/n) ");
            char resposta;
            scanf(" %c", &resposta);
            if (resposta == 's') {
                char palpite[MAX_PALAVRA];
                printf("Qual o seu palpite? ");
                scanf("%s", palpite);
                if (strcmp(palpite, palavra_secreta.palavra) == 0) {
                    printf("Parabens, voce acertou!\n");
                    return;
                } else {
                    printf("Que pena, voce errou.\n");
                    erros++;
                }
            }
        }
        printf("Digite uma letra: ");
        scanf(" %c", &letra);
        if (letra < 'a' || letra > 'z') {
            printf("Letra invalida.\n");
            continue;
        }
        No* no_atual = letras_digitadas.inicio;
        int letra_repetida = 0;
        while (no_atual != NULL) {
            if (no_atual->letra == letra) {
                printf("Voce ja digitou essa letra.\n");
                letra_repetida = 1;
                break;
            }
            no_atual = no_atual->prox;
        }
        if (letra_repetida) {
            continue;
        }
        enfileirar(&letras_digitadas, letra);
        if (!verificar_letra_na_palavra(&palavra_secreta, letra)) {
            printf("A palavra nao tem a letra %c.\n", letra);
            erros++;
        } else {
            printf("A palavra tem a letra %c.\n", letra);
        }
        if (verificar_palavra_descoberta(&palavra_secreta, &letras_digitadas)) {
            printf("Parabens, voce acertou!\n");
            return;
        }
    }
    printf("Que pena, voce perdeu. A palavra era: %s\n", palavra_secreta.palavra);
}
