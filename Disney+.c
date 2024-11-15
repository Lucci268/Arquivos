#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME_FILME 100
#define MAX_GENERO_FILME 100
#define MAX_USUARIO 100
#define MAX_FAVORITOS 100

typedef struct {
    int id;
    char filme[MAX_NOME_FILME];
    char genero[MAX_GENERO_FILME];
} Filme;

typedef struct {
    int id;
    char nome[MAX_USUARIO];
    int filmes_favoritos[MAX_FAVORITOS];
    int num_favoritos;
} Usuario;

void adicionar_filme(FILE *filme_file);
void adicionar_usuario(FILE *user_file);
void listar_filmes(FILE *filme_file);
void listar_usuarios(FILE *user_file, FILE *video_file);

int main() {
    FILE *filme_file, *user_file;

    filme_file = fopen("filmes.bin", "rb+");
    if (!filme_file) filme_file = fopen("filmes.bin", "wb+");

    user_file = fopen("usuarios.bin", "rb+");
    if (!filme_file) user_file = fopen("usuarios.bin", "wb+");

    if (!filme_file || !user_file) {
        printf("Erro ao abrir os arquivos binários.\n");
        return 1;
    }

    int opcao;
    do {
        printf("\n=== MENU ===\n");
        printf("1. Adicionar Filme\n");
        printf("2. Adicionar Usuário\n");
        printf("3. Listar Filmes\n");
        printf("4. Listar Usuários\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionar_filme(filme_file);
                break;
            case 2:
                adicionar_usuario(user_file);
                break;
            case 3:
                listar_filmess(filme_file);
                break;
            case 4:
                listar_usuarios(user_file, filme_file);
                break;
            case 5:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);

    fclose(filme_file);
    fclose(user_file);

    return 0;
}

void adicionar_video(FILE *filme_file) {
    Filme filme;
    printf("\n=== Adicionar Vídeo ===\n");
    printf("ID: ");
    scanf("%d", &filme.id);
    printf("Título: ");
    getchar(); // Limpar o buffer
    fgets(filme.filme, MAX_NOME_FILME, stdin);
    strtok(filme.filme, "\n"); // Remover o '\n' do final
    printf("Gênero: ");
    fgets(filme.genero, MAX_GENERO_FILME, stdin);
    strtok(filme.genero, "\n");

    fseek(filme_file, 0, SEEK_END);
    fwrite(&filme, sizeof(Filme), 1, filme_file);