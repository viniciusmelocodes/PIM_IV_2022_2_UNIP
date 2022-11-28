#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_40 40
#define MAX_100 100
#define MAX_512 512
#define MAX_9999 9999

struct Usuario {
    int codigo;
    char usuario[MAX_40];
    char senha[MAX_40];
};

struct Paciente {
    int codigo;
    char nome[70];
    char cpf[11];
    char ddd[2];
    char telefone[9];
    char logradouro[20];
    char numero[5];
    char bairro[30];
    char cidade[50];
    char estado[50];
    char cep[8];
    char data_nascimento[8];
    char email[100];
    char data_diagnostico[8];
    char comorbidades_existentes[300];
};

struct PacienteGrupoRisco {
    int codigo;
    char cep[8];
    int idade;
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

void strip(char *s) {
    char *p2 = s;
    while(*s != '\0') {
        if(*s != '\t' && *s != '\n') {
            *p2++ = *s++;
        } else {
            ++s;
        }
    }
    *p2 = '\0';
}

int main()
{
    struct tm*                tempoAtual;

    struct Usuario            listaUsuarios[MAX_9999];
    struct Paciente           listaPacientes[MAX_9999];
    struct PacienteGrupoRisco listaPacientesGrupoRisco[MAX_9999];
    FILE* arquivoUsuarios;
    FILE* arquivoPacientes;
    FILE* arquivoPacientesGrupoRisco;

    int i = 1;
    int opcaoSelecionada;
    int usuarioValidado = 1;
    int senhaValidada = 1;
    int loginAutorizado = 0;
    int codigoUsuario = 0;
    int codigoPaciente = 0;
    int idade = 0;
    int anoNascimento = 0;
    int anoAtual = 0;
    int possuiComorbidades = 1;

    // Para limpar buffer de cadastro de pacientes
	char temp;

	char auxCadastro[1];
    char anoNascimentoAux[4];
    char linhaArquivo[MAX_512];

    char codigoAux[MAX_40];
    char idadeAux[4];
    char usuario[MAX_40];
    char senha[MAX_40];

    // Paciente
    char nome[70];
    char cpf[12];
    char ddd[3];
    char telefone[10];
    char logradouro[20];
    char numero[5];
    char bairro[30];
    char cidade[50];
    char estado[50];
    char cep[9];
    char data_nascimento[9];
    char email[100];
    char data_diagnostico[9];
    char comorbidades_existentes[300];

    time_t dataHorarioAgora = time(NULL);

    // Carga do arquivo de usuários
    arquivoUsuarios = fopen("usuarios.txt", "r");

    if (arquivoUsuarios == NULL) {
        printf("Erro ao abrir arquivo de usuários.");
        return 0;
    }

    while (fgets(linhaArquivo, MAX_100, arquivoUsuarios) != NULL) {
        strncpy(codigoAux, &linhaArquivo[8], strlen(linhaArquivo));
        codigoUsuario = atoi(codigoAux);
        listaUsuarios[i].codigo = codigoUsuario;

        fgets(linhaArquivo, MAX_40, arquivoUsuarios);
        strncpy(usuario, &linhaArquivo[9], strlen(linhaArquivo));
        strcpy(listaUsuarios[i].usuario, usuario);
        strip(listaUsuarios[i].usuario);

        fgets(linhaArquivo, MAX_40, arquivoUsuarios);
        strncpy(senha, &linhaArquivo[7], strlen(linhaArquivo));
        strcpy(listaUsuarios[i].senha, senha);
        strip(listaUsuarios[i].senha);

        i++;
    }

    fclose(arquivoUsuarios);

    // Carga do arquivo de pacientes
    arquivoPacientes = fopen("pacientes.txt", "r");

    if (arquivoPacientes == NULL) {
        printf("Erro ao abrir arquivo de pacientes.");
        return 0;
    }

    i = 1;

    while (fgets(linhaArquivo, MAX_512, arquivoPacientes) != NULL) {
        strncpy(codigoAux, &linhaArquivo[8], strlen(linhaArquivo));
        codigoPaciente = atoi(codigoAux);
        listaPacientes[i].codigo = codigoPaciente;

        fgets(linhaArquivo, 70, arquivoPacientes);
        strncpy(nome, &linhaArquivo[6], strlen(linhaArquivo));
        strcpy(listaPacientes[i].nome, nome);
        strip(listaPacientes[i].nome);

        fgets(linhaArquivo, MAX_40, arquivoPacientes);
        strncpy(cpf, &linhaArquivo[5], strlen(linhaArquivo));
        strcpy(listaPacientes[i].cpf, cpf);
        strip(listaPacientes[i].cpf);

        fgets(linhaArquivo, MAX_40, arquivoPacientes);
        strncpy(ddd, &linhaArquivo[5], strlen(linhaArquivo));
        strcpy(listaPacientes[i].ddd, ddd);
        strip(listaPacientes[i].ddd);

        fgets(linhaArquivo, MAX_40, arquivoPacientes);
        strncpy(telefone, &linhaArquivo[10], strlen(linhaArquivo));
        strcpy(listaPacientes[i].telefone, telefone);
        strip(listaPacientes[i].telefone);

        fgets(linhaArquivo, 20, arquivoPacientes);
        strncpy(logradouro, &linhaArquivo[12], strlen(linhaArquivo));
        strcpy(listaPacientes[i].logradouro, logradouro);
        strip(listaPacientes[i].logradouro);

        fgets(linhaArquivo, 5, arquivoPacientes);
        strncpy(numero, &linhaArquivo[8], strlen(linhaArquivo));
        strcpy(listaPacientes[i].numero, numero);
        strip(listaPacientes[i].numero);

        fgets(linhaArquivo, 30, arquivoPacientes);
        strncpy(bairro, &linhaArquivo[8], strlen(linhaArquivo));
        strcpy(listaPacientes[i].bairro, bairro);
        strip(listaPacientes[i].bairro);

        fgets(linhaArquivo, 50, arquivoPacientes);
        strncpy(cidade, &linhaArquivo[8], strlen(linhaArquivo));
        strcpy(listaPacientes[i].cidade, cidade);
        strip(listaPacientes[i].cidade);

        fgets(linhaArquivo, 50, arquivoPacientes);
        strncpy(estado, &linhaArquivo[8], strlen(linhaArquivo));
        strcpy(listaPacientes[i].estado, estado);
        strip(listaPacientes[i].estado);

        fgets(linhaArquivo, 8, arquivoPacientes);
        strncpy(cep, &linhaArquivo[5], strlen(linhaArquivo));
        strcpy(listaPacientes[i].cep, cep);
        strip(listaPacientes[i].cep);

        fgets(linhaArquivo, MAX_40, arquivoPacientes);
        strncpy(data_nascimento, &linhaArquivo[17], strlen(linhaArquivo));
        strcpy(listaPacientes[i].data_nascimento, data_nascimento);
        strip(listaPacientes[i].data_nascimento);

        fgets(linhaArquivo, 100, arquivoPacientes);
        strncpy(email, &linhaArquivo[8], strlen(linhaArquivo));
        strcpy(listaPacientes[i].email, email);
        strip(listaPacientes[i].email);

        fgets(linhaArquivo, MAX_40, arquivoPacientes);
        strncpy(data_diagnostico, &linhaArquivo[18], strlen(linhaArquivo));
        strcpy(listaPacientes[i].data_diagnostico, data_diagnostico);
        strip(listaPacientes[i].data_diagnostico);

        fgets(linhaArquivo, 300, arquivoPacientes);
        strncpy(comorbidades_existentes, &linhaArquivo[25], strlen(linhaArquivo));
        strcpy(listaPacientes[i].comorbidades_existentes, comorbidades_existentes);
        strip(listaPacientes[i].comorbidades_existentes);

        i++;
    }

    fclose(arquivoPacientes);

    // Carga do arquivo de pacientes de grupo de risco
    arquivoPacientesGrupoRisco = fopen("pacientes_grupo_risco.txt", "r");

    if (arquivoPacientesGrupoRisco == NULL) {
        printf("Erro ao abrir arquivo de pacientes de grupo de risco.");
        return 0;
    }

    i = 1;

    while (fgets(linhaArquivo, MAX_100, arquivoPacientesGrupoRisco) != NULL) {
        strncpy(codigoAux, &linhaArquivo[17], strlen(linhaArquivo));
        listaPacientesGrupoRisco[i].codigo = atoi(codigoAux);

        fgets(linhaArquivo, MAX_40, arquivoPacientesGrupoRisco);
        strncpy(cep, &linhaArquivo[5], strlen(linhaArquivo));
        strcpy(listaPacientesGrupoRisco[i].cep, cep);
        strip(listaPacientesGrupoRisco[i].cep);

        fgets(linhaArquivo, MAX_40, arquivoPacientesGrupoRisco);
        strncpy(idadeAux, &linhaArquivo[7], strlen(linhaArquivo));
        listaPacientesGrupoRisco[i].idade = atoi(idadeAux);

        i++;
    }

    fclose(arquivoPacientesGrupoRisco);

    // Menu Principal
    while (1) {
        printf(" << Sistema >> \n");
        printf("::: 1 - Fazer login :::\n");
        printf("::: 0 - Sair do sistema :::\n");
        printf("____________________\n\n");
        printf("Escolha uma das opções acima: \n");
        scanf("%d", &opcaoSelecionada);
        pausarMenuPrincipal();
        limparTela();

        switch(opcaoSelecionada)
        {
        case 1:
            printf("::: Login :::\n");
            printf("Usuário: ");
            scanf("%39s", usuario);
            printf("Senha: ");
            scanf("%39s", senha);

            // Rotina de validacao de login
            for(i = 1; i < MAX_9999; i++)
            {
                usuarioValidado = strcmp(usuario, listaUsuarios[i].usuario);
                senhaValidada = strcmp(senha, listaUsuarios[i].senha);

                if (usuarioValidado == 0 && senhaValidada == 0) {
                    loginAutorizado = 1;
                    break;
                }

                if (listaUsuarios[i].codigo == 0) {
                    break;
                }
            }

            if (loginAutorizado == 0) {
                printf("\n >> Login inválido. Tente novamente! <<");
            } else {
                limparTela();

                while (loginAutorizado == 1) {
                    printf(" << Menu >> \n");
                    printf("::: 1 - Cadastrar paciente :::\n");
                    printf("::: 2 - Deslogar :::\n");
                    printf("____________________\n\n");
                    printf("Escolha uma das opcoes acima: \n");
                    scanf("%d", &opcaoSelecionada);
                    pausarMenuPrincipal();
                    limparTela();

                    switch(opcaoSelecionada)
                    {
                    case 1:
                        arquivoPacientes = fopen("pacientes.txt", "a+");

                        if (arquivoPacientes == NULL) {
                            printf("Erro ao abrir arquivo de pacientes.");
                            return 0;
                        }

                        printf(" << Cadastro de Paciente >> \n");

                        codigoPaciente++;

                        printf("Nome: ");
                        scanf("%[^\n]", nome);

                        fprintf(arquivoPacientes, "codigo: %d", codigoPaciente);
                        fprintf(arquivoPacientes, "\nnome: %s", nome);

                        printf("CPF (somente números): ");
                        scanf("%11s", cpf);
                        fprintf(arquivoPacientes, "\ncpf: %s", cpf);

                        printf("DDD Telefone: ");
                        scanf("%2s", ddd);
                        fprintf(arquivoPacientes, "\nddd: %s", ddd);

                        printf("Telefone: ");
                        scanf("%9s", telefone);
                        fprintf(arquivoPacientes, "\ntelefone: %s", telefone);

                        printf("Logradouro: ");
                        scanf("%c", &temp);
                        scanf("%[^\n]", logradouro);
                        fprintf(arquivoPacientes, "\nlogradouro: %s", logradouro);

                        printf("Numero: ");
                        scanf("%4s", numero);
                        fprintf(arquivoPacientes, "\nnumero: %s", numero);

                        printf("Bairro: ");
                        scanf("%c", &temp);
                        scanf("%[^\n]", bairro);
                        fprintf(arquivoPacientes, "\nbairro: %s", bairro);

                        printf("Cidade: ");
                        scanf("%c", &temp);
                        scanf("%[^\n]", cidade);
                        fprintf(arquivoPacientes, "\ncidade: %s", cidade);

                        printf("Estado: ");
                        scanf("%c", &temp);
                        scanf("%[^\n]", estado);
                        fprintf(arquivoPacientes, "\nestado: %s", estado);

                        printf("CEP (somente números): ");
                        scanf("%8s", cep);
                        fprintf(arquivoPacientes, "\ncep: %s", cep);

                        printf("Data Nascimento (somente números): ");
                        scanf("%8s", data_nascimento);
                        fprintf(arquivoPacientes, "\ndata nascimento: %s", data_nascimento);

                        printf("E-mail: ");
                        scanf("%100s", email);
                        fprintf(arquivoPacientes, "\ne-mail: %s", email);

                        printf("Data Diagnóstico (somente números): ");
                        scanf("%8s", data_diagnostico);
                        fprintf(arquivoPacientes, "\ndata diagnostico: %s", data_diagnostico);

                        printf("Comorbidades Existentes: ");
                        scanf("%300s", comorbidades_existentes);
                        fprintf(arquivoPacientes, "\ncomorbidades existentes: %s", comorbidades_existentes);

                        fclose(arquivoPacientes);

                        // Analise se paciente é de grupo de risco
                        strncpy(anoNascimentoAux, &data_nascimento[4], 4);
                        strip(comorbidades_existentes);
                        strip(cep);
                        tempoAtual = localtime(&dataHorarioAgora);
                        anoAtual = (tempoAtual->tm_year + 1900);
                        sscanf(anoNascimentoAux, "%04d", &anoNascimento);

                        if (anoAtual - anoNascimento >= 65) {
                            possuiComorbidades = strstr(comorbidades_existentes, "nenhuma");

                            if (possuiComorbidades == 0) {
                                possuiComorbidades = strstr(comorbidades_existentes, "-");
                            }

                            if (possuiComorbidades == 0) {
                                arquivoPacientesGrupoRisco = fopen("pacientes_grupo_risco.txt", "a+");

                                if (arquivoPacientesGrupoRisco == NULL) {
                                    printf("Erro ao abrir arquivo de pacientes de grupo de risco.");
                                    return 0;
                                }

                                fprintf(arquivoPacientesGrupoRisco, "\ncodigo_paciente: %d", codigoPaciente);
                                fprintf(arquivoPacientesGrupoRisco, "\ncep: %s", cep);
                                fprintf(arquivoPacientesGrupoRisco, "\nidade: %d", anoAtual - anoNascimento);

                                fclose(arquivoPacientesGrupoRisco);
                            }
                        }

                        printf("\n >>> Novo paciente cadastrado com sucesso! <<<\n\nConfirme com S para sair.\n");
                        scanf("%s", auxCadastro);

                        break;

                    case 2:
                        loginAutorizado = 0;
                        printf("\n Tecle 'Enter' para voltar ao menu inicial do sistema.");
                        break;

                    case 0:
                        return 0;

                    default:
                        printf("Opção Inválida.\n Tecle 'Enter' para voltar ao menu do sistema.");
                    }

                    limparTela();
                }
            }

            pausarMenuPrincipal();
            break;

        case 0:
            return 0;

        default:
            printf("Opção Inválida.\n Tecle 'Enter' para voltar ao menu do sistema.");
        }

        pausarMenuPrincipal();
        limparTela();
    }
}
