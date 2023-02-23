#define MAX_PALAVRA 50
#define MAX_TAMANHO_FILA 100
#define MAX_TAMANHO_PALAVRA 10

typedef struct no No;

typedef struct {
    No* inicio;
    No* fim;
} Fila;

typedef struct {
    char palavra[MAX_PALAVRA];
    int tamanho;
} Palavra;

void inicializar_fila(Fila* fila);

int fila_vazia(Fila* fila);

void inserir_na_fila(Fila* fila, char letra);

int tamanho_da_fila(Fila* fila);

void imprimir_fila(Fila* fila);

void desalocar_fila(Fila* fila);

void inicializar_palavra(Palavra* palavra);

void inserir_letra_na_palavra(Palavra* palavra, char letra);

int tamanho_da_palavra(Palavra* palavra);

void imprimir_palavra(Palavra* palavra);

void ler_palavra_do_arquivo(FILE* arquivo, Palavra* palavra);

int escolher_nivel();

void enfileirar(Fila* fila, char letra);

int verificar_letra_na_palavra(Palavra* palavra, char letra);

int verificar_palavra_descoberta(Palavra* palavra, Fila* letras_digitadas);

void jogar();