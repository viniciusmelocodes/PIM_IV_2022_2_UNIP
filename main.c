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
    system("cls");
    // Linux
    // system("clear");
}

void pausarMenu() {
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
    struct Usuario usuarios[MAX_100];
    struct Paciente pacientes[MAX_100];
    struct PacienteGrupoRisco pacientesGrupoRisco[MAX_100];
    struct tm* tempoAtual;
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
    int pacienteGrupoRisco = 0;

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
        usuarios[i].codigo = codigoUsuario;

        fgets(linhaArquivo, MAX_40, arquivoUsuarios);
        strncpy(usuario, &linhaArquivo[9], strlen(linhaArquivo));
        strcpy(usuarios[i].usuario, usuario);
        strip(usuarios[i].usuario);

        fgets(linhaArquivo, MAX_40, arquivoUsuarios);
        strncpy(senha, &linhaArquivo[7], strlen(linhaArquivo));
        strcpy(usuarios[i].senha, senha);
        strip(usuarios[i].senha);

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
        pacientes[i].codigo = codigoPaciente;

        fgets(linhaArquivo, 70, arquivoPacientes);
        strncpy(nome, &linhaArquivo[6], strlen(linhaArquivo));
        strcpy(pacientes[i].nome, nome);
        strip(pacientes[i].nome);

        fgets(linhaArquivo, MAX_40, arquivoPacientes);
        strncpy(cpf, &linhaArquivo[5], strlen(linhaArquivo));
        strcpy(pacientes[i].cpf, cpf);
        strip(pacientes[i].cpf);

        fgets(linhaArquivo, MAX_40, arquivoPacientes);
        strncpy(ddd, &linhaArquivo[5], strlen(linhaArquivo));
        strcpy(pacientes[i].ddd, ddd);
        strip(pacientes[i].ddd);

        fgets(linhaArquivo, MAX_40, arquivoPacientes);
        strncpy(telefone, &linhaArquivo[10], strlen(linhaArquivo));
        strcpy(pacientes[i].telefone, telefone);
        strip(pacientes[i].telefone);

        fgets(linhaArquivo, 20, arquivoPacientes);
        strncpy(logradouro, &linhaArquivo[12], strlen(linhaArquivo));
        strcpy(pacientes[i].logradouro, logradouro);
        strip(pacientes[i].logradouro);

        fgets(linhaArquivo, 5, arquivoPacientes);
        strncpy(numero, &linhaArquivo[8], strlen(linhaArquivo));
        strcpy(pacientes[i].numero, numero);
        strip(pacientes[i].numero);

        fgets(linhaArquivo, 30, arquivoPacientes);
        strncpy(bairro, &linhaArquivo[8], strlen(linhaArquivo));
        strcpy(pacientes[i].bairro, bairro);
        strip(pacientes[i].bairro);

        fgets(linhaArquivo, 50, arquivoPacientes);
        strncpy(cidade, &linhaArquivo[8], strlen(linhaArquivo));
        strcpy(pacientes[i].cidade, cidade);
        strip(pacientes[i].cidade);

        fgets(linhaArquivo, 50, arquivoPacientes);
        strncpy(estado, &linhaArquivo[8], strlen(linhaArquivo));
        strcpy(pacientes[i].estado, estado);
        strip(pacientes[i].estado);

        fgets(linhaArquivo, 8, arquivoPacientes);
        strncpy(cep, &linhaArquivo[5], strlen(linhaArquivo));
        strcpy(pacientes[i].cep, cep);
        strip(pacientes[i].cep);

        fgets(linhaArquivo, MAX_40, arquivoPacientes);
        strncpy(data_nascimento, &linhaArquivo[17], strlen(linhaArquivo));
        strcpy(pacientes[i].data_nascimento, data_nascimento);
        strip(pacientes[i].data_nascimento);

        fgets(linhaArquivo, 100, arquivoPacientes);
        strncpy(email, &linhaArquivo[8], strlen(linhaArquivo));
        strcpy(pacientes[i].email, email);
        strip(pacientes[i].email);

        fgets(linhaArquivo, MAX_40, arquivoPacientes);
        strncpy(data_diagnostico, &linhaArquivo[18], strlen(linhaArquivo));
        strcpy(pacientes[i].data_diagnostico, data_diagnostico);
        strip(pacientes[i].data_diagnostico);

        fgets(linhaArquivo, 300, arquivoPacientes);
        strncpy(comorbidades_existentes, &linhaArquivo[25], strlen(linhaArquivo));
        strcpy(pacientes[i].comorbidades_existentes, comorbidades_existentes);
        strip(pacientes[i].comorbidades_existentes);

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
        pacientesGrupoRisco[i].codigo = atoi(codigoAux);

        fgets(linhaArquivo, MAX_40, arquivoPacientesGrupoRisco);
        strncpy(cep, &linhaArquivo[5], strlen(linhaArquivo));
        strcpy(pacientesGrupoRisco[i].cep, cep);
        strip(pacientesGrupoRisco[i].cep);

        fgets(linhaArquivo, MAX_40, arquivoPacientesGrupoRisco);
        strncpy(idadeAux, &linhaArquivo[7], strlen(linhaArquivo));
        pacientesGrupoRisco[i].idade = atoi(idadeAux);

        i++;
    }

    fclose(arquivoPacientesGrupoRisco);

    // Menu Principal
    while (1) {
        printf(" << Sistema >> \n");
        printf("::: 1 - Fazer login :::\n");
        printf("::: 0 - Sair do sistema :::\n");
        printf("____________________\n\n");
        printf("Escolha uma das opcoes acima: \n");
        scanf("%d", &opcaoSelecionada);
        pausarMenu();
        limparTela();

        switch(opcaoSelecionada)
        {
        case 1:
            printf("::: Login :::\n");
            printf("Usuario: ");
            scanf("%39s", usuario);
            printf("Senha: ");
            scanf("%39s", senha);

            // Rotina de validacao de login
            for(i = 1; i < MAX_9999; i++)
            {
                usuarioValidado = strcmp(usuario, usuarios[i].usuario);
                senhaValidada = strcmp(senha, usuarios[i].senha);

                if (usuarioValidado == 0 && senhaValidada == 0) {
                    loginAutorizado = 1;
                    break;
                }

                if (usuarios[i].codigo == 0) {
                    break;
                }
            }

            if (loginAutorizado == 0) {
                printf("\n >> Login invalido. Tente novamente! <<");
            } else {
                limparTela();

                while (loginAutorizado == 1) {
                    printf(" << Menu >> \n");
                    printf("::: 1 - Cadastrar paciente :::\n");
                    printf("::: 2 - Deslogar :::\n");
                    printf("____________________\n\n");
                    printf("Escolha uma das opcoes acima: \n");
                    scanf("%d", &opcaoSelecionada);
                    pausarMenu();
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

                        printf("CPF (somente numeros): ");
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

                        printf("CEP (somente numeros): ");
                        scanf("%8s", cep);
                        fprintf(arquivoPacientes, "\ncep: %s", cep);

                        printf("Data Nascimento (somente numeros): ");
                        scanf("%8s", data_nascimento);
                        fprintf(arquivoPacientes, "\ndata nascimento: %s", data_nascimento);

                        printf("E-mail: ");
                        scanf("%100s", email);
                        fprintf(arquivoPacientes, "\ne-mail: %s", email);

                        printf("Data Diagnostico (somente numeros): ");
                        scanf("%8s", data_diagnostico);
                        fprintf(arquivoPacientes, "\ndata diagnostico: %s", data_diagnostico);

                        printf("Comorbidades Existentes: ");
                        scanf("%300s", comorbidades_existentes);
                        fprintf(arquivoPacientes, "\ncomorbidades existentes: %s", comorbidades_existentes);

                        fclose(arquivoPacientes);

                        // Analise se paciente é de grupo de risco
                        pacienteGrupoRisco = 0;

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

                                pacienteGrupoRisco = 1;
                            }
                        }

                        if (pacienteGrupoRisco == 1) {
                            printf("\n >>> Novo paciente cadastrado com sucesso! <<<\nPaciente eh do grupo de risco e foi cadastrado no arquivo paciente_grupo_risco.txt\n\nConfirme com S para sair.\n");
                        } else {
                            printf("\n >>> Novo paciente cadastrado com sucesso! <<<\n\nConfirme com S para sair.\n");
                        }

                        scanf("%s", auxCadastro);

                        break;

                    case 2:
                        loginAutorizado = 0;
                        printf("\n Tecle 'Enter' para voltar ao menu inicial do sistema.");
                        pausarMenu();
                        break;

                    case 0:
                        return 0;

                    default:
                        printf("Opcao Invalida.\n Tecle 'Enter' para voltar ao menu do sistema.");
                    }

                    limparTela();
                }
            }

            pausarMenu();
            break;

        case 0:
            return 0;

        default:
            printf("Opcao Invalida.\n Tecle 'Enter' para voltar ao menu do sistema.");
        }

        pausarMenu();
        limparTela();
    }
}
