#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct Usuario {
    int id;
    char nome[100];
    char email[100];
    char sexo[15];
    char endereco[200];
    double altura;
    int vacina;
};


int gerarId() {
    return rand() % 10000 + 1; 
}


int validaEmail(char *email) {
    char *posArroba = strchr(email, '@');
    return (posArroba != NULL);
}


int validaSexo(char *sexo) {
    return (strcmp(sexo, "Feminino") == 0 || strcmp(sexo, "Masculino") == 0 || strcmp(sexo, "Indiferente") == 0);
}


int validaAltura(double altura) {
    return (altura >= 1.0 && altura <= 2.0);
}


int validaVacina(int vacina) {
    return (vacina == 0 || vacina == 1);
}


void incluirUsuario(struct Usuario usuarios[], int *numUsuarios) {
    if (*numUsuarios < 1000) {
        struct Usuario novoUsuario;
        novoUsuario.id = gerarId();

        printf("Nome completo: ");
        scanf(" %[^\n]s", novoUsuario.nome);

        do {
            printf("Email: ");
            scanf("%s", novoUsuario.email);
        } while (!validaEmail(novoUsuario.email));

        do {
            printf("Sexo (Feminino/Masculino/Indiferente): ");
            scanf("%s", novoUsuario.sexo);
        } while (!validaSexo(novoUsuario.sexo));

        printf("Endereco: ");
        scanf(" %[^\n]s", novoUsuario.endereco);

        do {
            printf("Altura (entre 1 e 2 metros): ");
            scanf("%lf", &novoUsuario.altura);
        } while (!validaAltura(novoUsuario.altura));

        do {
            printf("Recebeu vacina? (1 para sim, 0 para nao): ");
            scanf("%d", &novoUsuario.vacina);
        } while (!validaVacina(novoUsuario.vacina));

        usuarios[*numUsuarios] = novoUsuario;
        (*numUsuarios)++;
        printf("Usuário cadastrado com sucesso!\n");
    } else {
        printf("Limite de usuários atingido.\n");
    }
}


void editarUsuario(struct Usuario usuarios[], int numUsuarios) {
    int id;
    printf("Digite o ID do usuário que deseja editar: ");
    scanf("%d", &id);

    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i].id == id) {
            printf("Novo nome completo: ");
            scanf(" %[^\n]s", usuarios[i].nome);

            do {
                printf("Novo email: ");
                scanf("%s", usuarios[i].email);
            } while (!validaEmail(usuarios[i].email));

            do {
                printf("Novo sexo (Feminino/Masculino/Indiferente): ");
                scanf("%s", usuarios[i].sexo);
            } while (!validaSexo(usuarios[i].sexo));

            printf("Novo endereco: ");
            scanf(" %[^\n]s", usuarios[i].endereco);

            do {
                printf("Nova altura (entre 1 e 2 metros): ");
                scanf("%lf", &usuarios[i].altura);
            } while (!validaAltura(usuarios[i].altura));

            do {
                printf("Recebeu nova vacina? (1 para sim, 0 para nao): ");
                scanf("%d", &usuarios[i].vacina);
            } while (!validaVacina(usuarios[i].vacina));

            printf("Usuário editado com sucesso!\n");
            return;
        }
    }

    printf("Usuário não encontrado.\n");
}


void excluirUsuario(struct Usuario usuarios[], int *numUsuarios) {
    int id;
    printf("Digite o ID do usuário que deseja excluir: ");
    scanf("%d", &id);

    for (int i = 0; i < *numUsuarios; i++) {
        if (usuarios[i].id == id) {
            
            for (int j = i; j < *numUsuarios - 1; j++) {
                usuarios[j] = usuarios[j + 1];
            }
            (*numUsuarios)--;
            printf("Usuário excluído com sucesso!\n");
            return;
        }
    }

    printf("Usuário não encontrado.\n");
}


void buscarUsuarioPorEmail(struct Usuario usuarios[], int numUsuarios) {
    char email[100];
    printf("Digite o email do usuário que deseja buscar: ");
    scanf("%s", email);

    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].email, email) == 0) {
            printf("Usuário encontrado:\n");
            printf("ID: %d\n", usuarios[i].id);
            printf("Nome: %s\n", usuarios[i].nome);
            printf("Email: %s\n", usuarios[i].email);
            printf("Sexo: %s\n", usuarios[i].sexo);
            printf("Endereco: %s\n", usuarios[i].endereco);
            printf("Altura: %.2f\n", usuarios[i].altura);
            printf("Vacina: %d\n", usuarios[i].vacina);
            return;
        }
    }

    printf("Usuário não encontrado.\n");
}


void imprimirUsuarios(struct Usuario usuarios[], int numUsuarios) {
    printf("Lista de Usuários:\n");
    for (int i = 0; i < numUsuarios; i++) {
        printf("ID: %d\n", usuarios[i].id);
        printf("Nome: %s\n", usuarios[i].nome);
        printf("Email: %s\n", usuarios[i].email);
        printf("Sexo: %s\n", usuarios[i].sexo);
        printf("Endereco: %s\n", usuarios[i].endereco);
        printf("Altura: %.2f\n", usuarios[i].altura);
        printf("Vacina: %d\n", usuarios[i].vacina);
        printf("--------------------\n");
    }
}

int main() {
    struct Usuario usuarios[1000];
    int numUsuarios = 0;
    char opcao;

 
    srand(time(NULL));

    do {
        printf("\nEscolha uma opção:\n");
        printf("1. Incluir usuário\n");
        printf("2. Editar usuário\n");
        printf("3. Excluir usuário\n");
        printf("4. Buscar usuário por e-mail\n");
        printf("5. Imprimir todos os usuários cadastrados\n");
        printf("0. Sair\n");

        scanf(" %c", &opcao);

        switch (opcao) {
            case '1':
                incluirUsuario(usuarios, &numUsuarios);
                break;
            case '2':
                editarUsuario(usuarios, numUsuarios);
                break;
            case '3':
                excluirUsuario(usuarios, &numUsuarios);
                break;
            case '4':
                buscarUsuarioPorEmail(usuarios, numUsuarios);
                break;
            case '5':
                imprimirUsuarios(usuarios, numUsuarios);
                break;
            case '0':
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != '0');

    return 0;
}
