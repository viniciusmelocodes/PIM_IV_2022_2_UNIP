#include <stdio.h>
#include <string.h>

#define MAX_20 20
#define MAX_40 40
#define MAX_100 100
#define MAX_512 512
#define MAX_9999 9999

struct Usuario {
    int codigo;
    char login[MAX_20];
    char senha[MAX_20];
};

void limparTela() {
    // Windows
    //system("cls");
    // Linux
    system("clear");
}

void pausarMenuPrincipal() {
    getchar();
}

int main()
{
    struct Usuario listaUsuarios[MAX_9999];
    FILE* arquivoUsuarios;

    int i;
    int opcaoSelecionada;
    int acessarMenu = 0;
    int codigoUsuario = 0;
    int opcao = 0;
    int ultimoCodigoUsuario = 0;

    char linhaArquivo[MAX_100];
    char *resultLinhaArquivo;
    char login[MAX_20];
    char senha[MAX_20];

    arquivoUsuarios = fopen("usuarios.txt", "a+");

    if (arquivoUsuarios == NULL) {
        printf("Erro ao abrir arquivo de usuarios.");
        return 0;
    }

    while (fgets(linhaArquivo, MAX_100, arquivoUsuarios) != NULL || fgets(linhaArquivo, MAX_100, arquivoUsuarios) == '--------') {
        codigoUsuario = atoi(linhaArquivo);
        ultimoCodigoUsuario = codigoUsuario;
        listaUsuarios[codigoUsuario].codigo = codigoUsuario;
        fgets(listaUsuarios[codigoUsuario].login, MAX_20, arquivoUsuarios);
        fgets(listaUsuarios[codigoUsuario].senha, MAX_20, arquivoUsuarios);
    }

    fclose(arquivoUsuarios);

    // Menu Principal
    while (1) {
        printf(" << Sistema >> \n");
        printf("::: 1 - Fazer login :::\n");
        printf("::: 0 - Sair do sistema :::\n");
        printf("____________________\n\n");
        printf("Escolha uma das opcoes acima: \n");
        scanf("%d", &opcaoSelecionada);
        pausarMenuPrincipal();
        limparTela();

        switch(opcaoSelecionada)
        {
        case 1:
            printf("::: Login :::\n");
            printf("Usuario: ");
            scanf("%s", &login);
            printf("Senha: ");
            scanf("%s", &senha);

            for(i = 1; i < MAX_9999; i++)
            {
                printf("%d\n", listaUsuarios[i].codigo);
                printf("%d\n", login);

                if (login == listaUsuarios[i].login) {
                    if (senha == listaUsuarios[i].senha) {
                        acessarMenu = 1;
                    }
                }

                if (listaUsuarios[i].codigo == 0) {
                    break;
                }
            }

            if (acessarMenu == 1) {
                while (1) {
                    printf(" << Menu >> \n");
                    printf("::: 1 - Opcao :::\n");
                    printf("::: 2 - Opcao :::\n");
                    printf("____________________\n\n");
                    printf("Escolha uma das opcoes acima: \n");
                    scanf("%d", &opcaoSelecionada);
                    pausarMenuPrincipal();
                    limparTela();

                    switch(opcaoSelecionada)
                    {
                    case 1:
                        printf("\n Tecle 'Enter' para voltar ao menu do sistema.");
                        pausarMenuPrincipal();
                        break;

                    case 2:
                        printf("\n Tecle 'Enter' para voltar ao menu do sistema.");
                        pausarMenuPrincipal();
                        break;

                    case 0:

                        return 0;

                    default:
                        printf("Opcao Invalida");
                        printf("\n Tecle 'Enter' para voltar ao menu do sistema.");
                    }

                    pausarMenuPrincipal();
                    limparTela();
                }
            } else {
                printf("\n Login inválido. Tente novamente.");
            }

            pausarMenuPrincipal();
            break;

        case 0:

            return 0;

        default:
            printf("Opcao Invalida");
            printf("\n Tecle 'Enter' para voltar ao menu do sistema.");
        }

        pausarMenuPrincipal();
        limparTela();
    }
}
