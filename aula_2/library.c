#include <stdio.h>
#include <string.h>

#define MAX 100 //tamanho maximo da string 
#define TAM 1000 //tamanho do acervo

int totlivros = 0; //n total de livros cadastrados no acervo (em teste)

struct Livro { //estrutura para livros
    char nome[MAX];
    char autor[MAX];
    char editora[MAX];
    int ano;
    int emprestado;
};  

struct Livro acervo[TAM]; //acervo, cada posicao tem um livro

void inserir() {
    if (totlivros == TAM) { //validacao
        printf("Capacidade maxima atingida.\n");
        return;
    }

    struct Livro novoLivro; 
    printf("Nome: ");
    scanf("%s", novoLivro.nome);
    printf("Autor: ");
    scanf("%s", novoLivro.autor);
    printf("Editora: ");
    scanf("%s", novoLivro.editora);
    printf("Ano: ");
    scanf("%d", &novoLivro.ano);
    novoLivro.emprestado = 0; //validacao
    acervo[totlivros] = novoLivro; //insercao
    puts("Livro inserido com sucesso!");
    totlivros++; //contador
}

/*void remover() {
    
}

void emprestar() {

}

void devolver() {

}

void alterar() {

} */

int main() {
    int opcao;
    do {
        puts("Digite 0 para parar o programa.");
        puts("Digite 1 para inserir um livro.");
        puts("Digite 2 para remover um livro.");
        puts("Digite 3 para fazer emprestimo de um livro.");
        puts("Digite 4 para devolver um livro.");
        puts("Digite 5 para alterar um livro.");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserir(); break;
           /* case 2: remover(); break;
            case 3: emprestar(); break;
            case 4: devolver(); break;
            case 5: alterar(); break; */
            case 0: printf("Volte smepre!\n"); break;
            default: printf("Número invalido!\n");
        }
    } while (opcao != 0);

    return 0;
}