#include <stdio.h>    
#include <stdlib.h>   
#include <string.h> 
#include <conio.h>    
#include <windows.h>  
#include <time.h>     

// --- ESTRUTURAS DE DADOS ---
typedef struct { 
    char cliente[50], empresa[20], email[100]; 
} cadastro;

typedef struct {
    int id;
    char nome[50];
    int qtd;
    float preco;
} produtos; 

typedef struct {
    char item[50]; 
    double valor;  
} Venda;

void Formatar_Moeda(double valor, char *destino) {
    char temp[50];
    sprintf(temp, "%.2f", valor);
    
    int tam = strlen(temp);
    int p_dest = 0;
    int p_orig = 0;
    
    int ponto_idx = tam - 3; 
    
    for (p_orig = 0; p_orig < ponto_idx; p_orig++) {
        destino[p_dest++] = temp[p_orig];
        
        int digitos_restantes = ponto_idx - 1 - p_orig;
        if (digitos_restantes > 0 && digitos_restantes % 3 == 0) {
            destino[p_dest++] = '.'; 
        }
    }
    
    destino[p_dest++] = ',';
    destino[p_dest++] = temp[ponto_idx + 1];
    destino[p_dest++] = temp[ponto_idx + 2];
    destino[p_dest] = '\0';
}

void mudarCor(int cor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, cor);
}

int i;

double total_vendas = 0; 
int eh_manager = 0; 

void cls() { system("cls"); }

// --- 0. ANIMAÇÕES COMPLETAS DE SISTEMA ---

void animacao_boot() {   
    cls();
    mudarCor(10);
    printf("ECO MEKHA SYSTEMS [Version 22.052026]\n");
    printf(" © 2026 Eco Mekha CO . BIOS v3.0\n\n");
    Sleep(800);
    printf("Verificando hardware... OK\n"); Sleep(500);
    printf("Testando memoria RAM... OK [1024MB]\n"); Sleep(500);
    printf("Carregando Kernel ECO_OS... OK\n"); Sleep(600);
    printf("Sincronizando bancos de dados (.txt)... OK\n"); Sleep(700);
    printf("\nSISTEMA PRONTO PARA OPERACAO.\n");
    mudarCor(7);
    Sleep(1000);
}

// Animação Loading 
void loading_doom() {
    cls();
    char anima[] = "|/-\\"; 
    int i, j;
    printf("\n\n   AUTENTICANDO CREDENCIAIS NO BANCO DE DADOS...\n");
    for (i = 0; i <= 20; i++) {
        printf("\r   ["); 
        for (j = 0; j < i; j++) printf("="); 
        for (j = i; j < 20; j++) printf(" ");
        printf("] %c %d%%", anima[i % 4], i * 5); 
        Sleep(40); 
    }
    printf("\n\n   ACESSO LIBERADO! BEM-VINDO.");
    Sleep(600);
}

void transicao() {
    cls();
    char anima[] = "|/-\\";
    int i;
    printf("\n\n   PROCESSANDO REQUISICAO... ");
    for (i = 0; i < 10; i++) {
        printf("%c\b", anima[i % 4]);
        Sleep(70);
    }
}

// --- 0.1 SEGURANÇA E LOGIN ---
void tela_login() {
    char usuario[20], senha[20], ch;
    int i, tentativas = 0;
    while(tentativas < 3) {
        cls();
        mudarCor(10);
        printf("ECO MEKHA CO - LOGIN GATEWAY\n");
        mudarCor(7);
        printf("USUARIO: "); fflush(stdin); scanf("%s", usuario);
        if(strcmp(usuario, "Manager") == 0) {
            printf("SENHA: ");
            i = 0;
            while (1) {
                ch = getch();
                if (ch == 13) { senha[i] = '\0'; break; } 
                else if (ch == 8) { if (i > 0) { i--; printf("\b \b"); } } 
                else if (i < 19) { senha[i] = ch; i++; printf("*"); }
            }
            if(strcmp(senha, "1234") == 0) { eh_manager = 1; loading_doom(); return; }
        } 
        else if(strcmp(usuario, "AE") == 0) {
            eh_manager = 0;
            loading_doom();
            return;
        }        
        mudarCor(12);
        printf("\n\nACESSO NEGADO! TENTE NOVAMENTE.\n");
        mudarCor(7);
        tentativas++; system("pause");
    }
    exit(0);
}
// --- 1. cadastro de clientes 
void Cadastro_Cli() {
    transicao();
    cls();
    cadastro a; 
    FILE *arq = fopen("Cadastro.txt", "a");
    printf("\n ====== CADASTRO DE CLIENTE ====== \n\n");
    printf("Nome: ");
    fflush(stdin);
    scanf(" %49[^\n]", a.cliente); // Limita a 49 caracteres (+1 do \0)
    printf("Empresa: ");
    fflush(stdin);
    scanf(" %19[^\n]", a.empresa); // Limita a 19 caracteres (+1 do \0)
    printf("Email: ");
    fflush(stdin);
    scanf(" %75[^\n]", a.email);   // Corta o e-mail na digitação caso passe de 75 caracteres
    
    if (arq != NULL) {
        fprintf(arq, "[Cliente: %s] | [Empresa: %s] | [Email: %s]\n",
        a.cliente, a.empresa, a.email);
        fclose(arq);
        printf("\n ====== CLIENTE CADASTRADO! ====== \n\n");
    }
    system("pause");
}

void Exibir_Tabela_Clientes(cadastro lista[], int total) {
    printf("\n ====== LISTAGEM DE CLIENTES ECO MEKHA ====== \n");
    printf("======================================================================================================\n");
    printf("| %-4s | %-35s | %-20s | %-30s |\n", "ID", "CLIENTE", "EMPRESA", "EMAIL");
    printf("======================================================================================================\n");

    if (total == 0) {
        mudarCor(12);
        printf("| %-101s |\n", "Nenhum Cliente registrado.");
        mudarCor(7);
    } else {
        int idx;
        for (idx = 0; idx < total; idx++) {
            char *p = lista[idx].cliente + strlen(lista[idx].cliente) - 1;
            while(p >= lista[idx].cliente && *p == ' ') { 
                *p = '\0'; 
                p--; 
            }

            printf("| %-4d | %-35.35s | %-20.20s | %-30.30s |\n",
                   idx + 1, lista[idx].cliente, lista[idx].empresa, lista[idx].email);
        }
    }
    printf("======================================================================================================\n");
}

// --- 2. listar clientes
void Listar_Cli() {
    transicao();
    cls();
    char linha[250];      
    cadastro lista[100];  
    int total = 0;
    
    FILE *arq = fopen("Cadastro.txt", "r");
    if (arq != NULL) {
        while (fgets(linha, sizeof(linha), arq) != NULL && total < 100) {
            sscanf(linha, "[Cliente: %49[^]]] | [Empresa: %19[^]]] | [Email: %75[^]]]",
                   lista[total].cliente, lista[total].empresa, lista[total].email);
            total++;
        }
        fclose(arq);
    }
    
    Exibir_Tabela_Clientes(lista, total);
    system("pause");
}

// --- 3. Editar / Excluir Cliente
void Editar_Cli() {
    transicao();
    cls();
    cadastro lista[100];  
    int total = 0;
    int i;
    char linha[250];      
    
    FILE *arq = fopen("Cadastro.txt", "r");
    if (arq == NULL) {
        mudarCor(12);
        printf("\nNenhum cliente registado.\n");
        mudarCor(7);
        system("pause");
        return;
    }

    while (fgets(linha, sizeof(linha), arq) != NULL && total < 100) {
        sscanf(linha,
               "[Cliente: %49[^]]] | [Empresa: %19[^]]] | [Email: %75[^]]]",
               lista[total].cliente,
               lista[total].empresa,
               lista[total].email);
        total++;
    }
    fclose(arq);
    
    int op, idProcurado;
    printf("\n ====== EDITAR CLIENTE ====== \n");
    printf("0 - Voltar\n");
    printf("1 - Editar\n");
    printf("2 - Excluir\n");
    printf("Escolha: ");
    scanf("%d", &op);

    if (op == 0) {
        transicao();
        return;
    }
    
    if (op != 1 && op != 2) {
        mudarCor(12);
        printf("\nOpcao Invalida!\n");
        mudarCor(7);
        system("pause");
        return;
    }

    cls();
    Exibir_Tabela_Clientes(lista, total);

    printf("ID do cliente: ");
    scanf("%d", &idProcurado);
    
    int indice = idProcurado - 1;
    if (indice >= 0 && indice < total) {

        if (op == 1) {
            printf("\n--- Editando Cliente [ID: %d] ---\n", idProcurado);
            printf("Novo Nome: ");
            scanf(" %49[^\n]", lista[indice].cliente);
            printf("Nova Empresa: ");
            scanf(" %19[^\n]", lista[indice].empresa);
            printf("Novo Email: ");
            scanf(" %75[^\n]", lista[indice].email); 
        }
        else if (op == 2) {
            int conf;
            mudarCor(12);
            printf("Confirmar Exclusao do Cliente [ID: %d]? (1 - Sim / 0 - Nao): ", idProcurado);
            mudarCor(7);
            scanf("%d", &conf);
            if (conf == 1) {
                int j;
                for (j = indice; j < total - 1; j++) {
                    lista[j] = lista[j + 1];
                }
                total--;
            }
        }

    } else {
        mudarCor(12);
        printf("\nCliente Nao Encontrado!\n");
        mudarCor(7);
        system("pause");
        return;
    }

    arq = fopen("Cadastro.txt", "w");
    if (arq != NULL) {
        for (i = 0; i < total; i++) {
            fprintf(arq,
                    "[Cliente: %s] | [Empresa: %s] | [Email: %s]\n",
                    lista[i].cliente,
                    lista[i].empresa,
                    lista[i].email);
        }
        fclose(arq);
    }
    printf("\nOperacao concluida com sucesso!\n");
    system("pause");
}
// --- 4. cadastro de produtos
void Cadastro_Prod() {
    transicao();
    cls();
    int idAtual = 1;
    char linha[200];
    
    // CORREÇÃO: Descobre o maior ID existente para gerar o próximo corretamente
    FILE *arqContador = fopen("Produtos.txt", "r");
    if (arqContador != NULL) {
        int idLido;
        while (fgets(linha, sizeof(linha), arqContador) != NULL) {
            if (sscanf(linha, "[ID: %d]", &idLido) == 1) {
                if (idLido >= idAtual) {
                    idAtual = idLido + 1;
                }
            }
        }
        fclose(arqContador);
    }

    FILE *arq = fopen("Produtos.txt", "a");
    if (arq == NULL) {
        mudarCor(12); 
        printf("Erro ao abrir o ficheiro de produtos!\n");
        mudarCor(7);
        system("pause");
        return;
    }

    produtos novo;
    novo.id = idAtual;
    
    printf("\n ====== CADASTRO DE PRODUTO ====== \n\n");
    printf("ID gerado automaticamente: %d\n", novo.id);
    
    printf("Nome: ");
    fflush(stdin); 
    scanf(" %49[^\n]", novo.nome); // Limita a 49 caracteres de forma segura
    
    printf("Preco: ");
    scanf("%f", &novo.preco);
    
    printf("Quantidade: ");
    scanf("%d", &novo.qtd);

    fprintf(arq, "[ID: %d] | [Nome: %s] | [Qtd: %d] | [Preco: %.2f]\n",
            novo.id, novo.nome, novo.qtd, novo.preco);
    fclose(arq);
    
    printf("\nProduto cadastrado e salvo com sucesso!\n");
    system("pause");
}

void Exibir_Tabela(produtos lista[], int total) {
    char str_preco[30]; 
    
    printf("\n==========================================================================\n");
    printf("| %-4s | %-30s | %-12s | %-16s|\n", "ID", "NOME DO PRODUTO", "QUANTIDADE", "PRECO");
    printf("==========================================================================\n");
    
    if (total == 0) {
        mudarCor(12);
        printf("| %-73s |\n", "Nenhum produto registrado no estoque.");
        mudarCor(7);
    } else {
        int idx;
        for (idx = 0; idx < total; idx++) {
            Formatar_Moeda((double)lista[idx].preco, str_preco);
            
            printf("| %-4d | %-30.30s | %-12d | R$ %-12s |\n", 
                   lista[idx].id, lista[idx].nome, lista[idx].qtd, str_preco);
        }
    }
    printf("==========================================================================\n");
}


// --- 5- Listar_Prod 
void Listar_Prod() {
    transicao();
    cls();
    char linha[250];
    produtos lista[100];
    int total = 0;
    
    FILE *arq = fopen("Produtos.txt", "r");
    if (arq != NULL) {
        while (fgets(linha, sizeof(linha), arq) != NULL && total < 100) {
            sscanf(linha, "[ID: %d] | [Nome: %49[^]]] | [Qtd: %d] | [Preco: %f]", 
                   &lista[total].id, lista[total].nome, &lista[total].qtd, &lista[total].preco);
            total++;
        }
        fclose(arq);
    }
    
    Exibir_Tabela(lista, total);
    system("pause");
}

// --- 6. Editar / Excluir Produto 
void Editar_Prod() {
    transicao();
    cls();
    produtos lista[100];
    int total = 0;
    char linha[250];
    
    FILE *arq = fopen("Produtos.txt", "r");
    if (arq == NULL) {
        mudarCor(12);
        printf("\nNenhum produto registrado.\n");
        mudarCor(7);
        system("pause");
        return;
    }

    while (fgets(linha, sizeof(linha), arq) != NULL && total < 100) {
        sscanf(linha,
        "[ID: %d] | [Nome: %49[^]]] | [Qtd: %d] | [Preco: %f]",
        &lista[total].id,
        lista[total].nome,
        &lista[total].qtd,
        &lista[total].preco);
        total++;
    }
    fclose(arq);
    
    int op, idProcurado;
    printf("\n ====== EDITAR PRODUTO ====== \n");
    printf("0 - Voltar\n");
    printf("1 - Editar\n");
    printf("2 - Excluir\n");
    printf("Escolha: ");
    scanf("%d", &op);

    if (op == 0) {
        transicao();
        return;
    }
    
    if (op != 1 && op != 2) {
        mudarCor(12);
        printf("\nOpcao invalida!\n");
        mudarCor(7);
        system("pause");
        return;
    }

    cls();
    Exibir_Tabela(lista, total);

    printf("\nDigite o ID do produto que deseja prosseguir: ");
    scanf("%d", &idProcurado);
    
    int encontrou = 0;
    int i; 
    
    for (i = 0; i < total; i++) {
        if (lista[i].id == idProcurado) {
            encontrou = 1;
            
            if (op == 1) {
                printf("\n--- Editando Produto [ID %d] ---\n", idProcurado);
                printf("Novo Nome: ");
                fflush(stdin);
                scanf(" %49[^\n]", lista[i].nome);
                printf("Novo Preco: ");
                scanf("%f", &lista[i].preco);
                printf("Nova Quantidade: ");
                scanf("%d", &lista[i].qtd);
            }
            else if (op == 2) {
                int conf;
                mudarCor(12);
                printf("Confirmar exclusao do produto [ID %d]? (1 - Sim / 0 - Nao): ", idProcurado);
                mudarCor(7);
                scanf("%d", &conf);
                if (conf == 1) {
                    int j;
                    for (j = i; j < total - 1; j++) {
                        lista[j] = lista[j + 1];
                    }
                    total--;
                }
            }
            break;
        }
    }

    if (!encontrou) {
        mudarCor(12);
        printf("\nProduto Nao Encontrado!\n");
        mudarCor(7);
        system("pause");
        return;
    }

    arq = fopen("Produtos.txt", "w");
    if (arq != NULL) {
        for (i = 0; i < total; i++) {
            lista[i].id = i + 1; 
            fprintf(arq,
            "[ID: %d] | [Nome: %s] | [Qtd: %d] | [Preco: %.2f]\n",
            lista[i].id,
            lista[i].nome,
            lista[i].qtd,
            lista[i].preco);
        }
        fclose(arq);
    }
    printf("\nOperacao concluida com sucesso!\n");
    system("pause");
}

// --- 7. Cadastrar Venda
void Cadastro_Venda() {
    transicao();
    cls();
    produtos lista[100];
    cadastro clientes[100];
    int totalProd = 0;
    int totalCli = 0;
    int i;
    char linha[300];
    FILE *arqProd = fopen("Produtos.txt", "r");
    if (arqProd == NULL) {
    	mudarCor(12);
        printf("\nNenhum Produto Cadastrado!\n");
        mudarCor(7);
        system("pause");
        return;
    }

    while (fgets(linha, sizeof(linha), arqProd) != NULL) {
        sscanf(linha,
        "[ID: %d] | [Nome: %[^]]] | [Qtd: %d] | [Preco: %f]",
        &lista[totalProd].id,
        lista[totalProd].nome,
        &lista[totalProd].qtd,
        &lista[totalProd].preco);
        totalProd++;
    }

    fclose(arqProd);
    FILE *arqCli = fopen("Cadastro.txt", "r");
    if (arqCli == NULL) {
        printf("\nNenhum Cliente Cadastrado!\n");
        system("pause");
        return;
    }

    while (fgets(linha, sizeof(linha), arqCli) != NULL) {
        sscanf(linha,
        "[Cliente: %[^]]] | [Empresa: %[^]]] | [Email: %[^]]]",
        clientes[totalCli].cliente,
        clientes[totalCli].empresa,
        clientes[totalCli].email);
        totalCli++;
    }
    fclose(arqCli);
    
    int idCliente;
    int idProduto;
    int quantidade;

    printf("\n================ REGISTRO DE VENDA ================\n\n");
    Listar_Cli();
    printf("\nID do Cliente: ");
    scanf("%d", &idCliente);
    Listar_Prod();
    printf("\nID do Produto: ");
    scanf("%d", &idProduto);
    printf("Quantidade: ");
    scanf("%d", &quantidade);
    if (idCliente <= 0 || idCliente > totalCli) {
    	mudarCor(12);
        printf("\nCliente Invalido!\n");
        mudarCor(7);
        system("pause");
        return;
    }
    int encontrou = 0;
    for (i = 0; i < totalProd; i++) {
        if (lista[i].id == idProduto) {
            encontrou = 1;
            if (quantidade > lista[i].qtd) {
            	mudarCor(12);
                printf("\nEstoque Insuficiente!\n");
                mudarCor(7);
                system("pause");
                return;
            }
            lista[i].qtd -= quantidade;
            double totalVenda = quantidade * lista[i].preco;
            int idVenda = 1;
            FILE *contador = fopen("vendas.txt", "r");
            if (contador != NULL) {
                while (fgets(linha, sizeof(linha), contador) != NULL) {
                    idVenda++;
                }
                fclose(contador);
            }
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            FILE *venda = fopen("vendas.txt", "a");
            fprintf(venda,
            "[ID:%d] | [%02d/%02d/%d %02d:%02d] | [Cliente:%s] | [Produto:%s] | [Qtd:%d] | [Total:%.2f]\n",
            idVenda,
            tm.tm_mday,
            tm.tm_mon + 1,
            tm.tm_year + 1900,
            tm.tm_hour,
            tm.tm_min,
            clientes[idCliente - 1].cliente,
            lista[i].nome,
            quantidade,
            totalVenda);
            fclose(venda);
            arqProd = fopen("Produtos.txt", "w");
            int j;
            for (j = 0; j < totalProd; j++) {
                fprintf(arqProd,
                "[ID: %d] | [Nome: %s] | [Qtd: %d] | [Preco: %.2f]\n",
                lista[j].id,
                lista[j].nome,
                lista[j].qtd,
                lista[j].preco);
            }
            fclose(arqProd);
            printf("\nVenda Realizada Com Sucesso!\n");
            
            printf("Valor total: R$ %.2f\n", totalVenda);
            system("pause");
            return;
        }
    }
    if (!encontrou) {
    	mudarCor(12);
        printf("\nProduto Nao Encontrado!\n");
        mudarCor(7);
        system("pause");
    }
}

// --- 8. Listar vendas
void Listar_Vendas() {
    transicao();
    cls();
    FILE *arq = fopen("vendas.txt", "r");
    char linha[300];
    double totalCaixa = 0;
    
    char str_total_item[30];
    char str_total_caixa[30];

    printf("\n===================================== VENDAS REALIZADAS ========================================\n");
    printf("| %-4s | %-16s | %-20s | %-20s | %-5s | %-11s  |\n",
           "ID",
           "DATA/HORA",
           "CLIENTE",
           "PRODUTO",
           "QTD",
           "TOTAL");
    printf("================================================================================================\n");

    if (arq == NULL) {
        printf("\nNenhuma venda realizada.\n");
    }
    else {
        int idVenda;
        char data[30];
        char cliente[50];
        char produto[50];
        int qtd;
        double total;
        
        while (fgets(linha, sizeof(linha), arq)) {
            sscanf(linha,
            "[ID:%d] | [%[^]]] | [Cliente:%[^]]] | [Produto:%[^]]] | [Qtd:%d] | [Total:%lf]",
            &idVenda,
            data,
            cliente,
            produto,
            &qtd,
            &total);
            
            Formatar_Moeda(total, str_total_item);

            printf("| %-4d | %-16s | %-20.20s | %-20.20s | %-5d | R$ %-8s |\n",
                   idVenda,
                   data,
                   cliente,
                   produto,
                   qtd,
                   str_total_item);
                   
            totalCaixa += total;
        }
        fclose(arq);
    }
    printf("================================================================================================\n");
    
    // Formata o total acumulado do caixa
    Formatar_Moeda(totalCaixa, str_total_caixa);
    printf("\nTOTAL EM CAIXA: R$ %s\n\n", str_total_caixa);
    system("pause");
}

// --- 9. estorno de vendas

void carregar_vendas_salvas() {
    FILE *arq = fopen("vendas.txt", "r");
    char linha[300];
    double valor_lido;
    total_vendas = 0;
    if (arq != NULL) {
        while (fgets(linha, sizeof(linha), arq) != NULL) {
            char *ptr = strstr(linha, "[Total:");
            if (ptr != NULL) {
                sscanf(ptr, "[Total:%lf]", &valor_lido);
                total_vendas += valor_lido;
            }
        }
        fclose(arq);
    }
}

void Estorno() {
    transicao();
    cls();
    FILE *arq = fopen("vendas.txt", "r");
    if (arq == NULL) {
        mudarCor(12);
        printf("\nNenhuma Venda Encontrada.\n");
        mudarCor(7);
        system("pause");
        return;
    }

    char linhas[100][300];
    int total = 0;
    char str_total_item[20]; 

    printf("\n===================================== VENDAS REALIZADAS =======================================\n");
    printf("| %-4s | %-16s | %-20s | %-20s | %-5s | %-11s |\n",
           "ID",
           "DATA/HORA",
           "CLIENTE",
           "PRODUTO",
           "QTD",
           "TOTAL");
    printf("===============================================================================================\n");

    while (fgets(linhas[total], sizeof(linhas[total]), arq) != NULL && total < 100) {
        int idVenda;
        char data[30];
        char cliente[50];
        char produto[50];
        int qtd;
        double total_val;

        sscanf(linhas[total],
               "[ID:%d] | [%[^]]] | [Cliente:%[^]]] | [Produto:%[^]]] | [Qtd:%d] | [Total:%lf]",
               &idVenda, data, cliente, produto, &qtd, &total_val);

        Formatar_Moeda(total_val, str_total_item);


        printf("| %-4d | %-16s | %-20.20s | %-20.20s | %-5d | R$ %-8s |\n",
               idVenda, data, cliente, produto, qtd, str_total_item);

        total++;
    }
    fclose(arq);
    printf("===============================================================================================\n");
    
    int escolha;
    printf("\nDigite o ID da Venda que deseja estornar: ");
    scanf("%d", &escolha);
    
    int indice_encontrado = -1;
    int i;

    for (i = 0; i < total; i++) {
        int idLinha;
        sscanf(linhas[i], "[ID:%d]", &idLinha);
        if (idLinha == escolha) {
            indice_encontrado = i;
            break;
        }
    }

    if (indice_encontrado == -1) {
        mudarCor(12);
        printf("\nID de Venda Invalido ou Nao Encontrado!\n");
        mudarCor(7);
        system("pause");
        return;
    }

    int qtd_devolver = 0;
    char produto_venda[50];
    sscanf(linhas[indice_encontrado],
           "[ID:%*d] | [%*[^]]] | [Cliente:%*[^]]] | [Produto:%[^]]] | [Qtd:%d]",
           produto_venda,
           &qtd_devolver);

    char *p = produto_venda + strlen(produto_venda) - 1;
    while(p >= produto_venda && (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n')) { 
        *p = '\0'; 
        p--; 
    }

    FILE *prod = fopen("Produtos.txt", "r");
    if (prod == NULL) {
        mudarCor(12);
        printf("\nErro critico: Arquivo de produtos nao encontrado!\n");
        mudarCor(7);
        system("pause");
        return;
    }
    
    FILE *tempProd = fopen("tempProd.txt", "w");
    char linha[300];
    int id;
    int quantidade;
    float preco;
    char nomeProd[50];
    
    while (fgets(linha, sizeof(linha), prod)) {
        sscanf(linha,
               "[ID: %d] | [Nome: %[^]]] | [Qtd: %d] | [Preco: %f]",
               &id, nomeProd, &quantidade, &preco);
        
        char *p2 = nomeProd + strlen(nomeProd) - 1;
        while(p2 >= nomeProd && (*p2 == ' ' || *p2 == '\t')) { 
            *p2 = '\0'; 
            p2--; 
        }
    
        if (strcmp(nomeProd, produto_venda) == 0) {
            quantidade += qtd_devolver; 
        }
        
        fprintf(tempProd,
                "[ID: %d] | [Nome: %s] | [Qtd: %d] | [Preco: %.2f]\n",
                id, nomeProd, quantidade, preco);
    }

    fclose(prod);
    fclose(tempProd);
    remove("Produtos.txt");
    rename("tempProd.txt", "Produtos.txt");

    FILE *temp = fopen("temp.txt", "w");
    for (i = 0; i < total; i++) {
        if (i != indice_encontrado) {
            fprintf(temp, "%s", linhas[i]);
        }
    }
    fclose(temp);
    remove("vendas.txt");
    rename("temp.txt", "vendas.txt");
    
    carregar_vendas_salvas();
    
    printf("\nVenda Estornada com Sucesso! Itens devolvidos ao estoque.\n");
    system("pause");
}

// --- 10. tela de saida
void tela_saida() {
transicao();
cls();
printf("\n==================================================\n");
mudarCor(10);
printf(" ENCERRANDO ECO MEKHA SYSTEMS... \n");
mudarCor(7);
printf("==================================================\n");
mudarCor(10);
printf("\n Obrigado por utilizar nossos servicos.\n");
printf(" (c) 2026 Eco Mekha CO. All rights reserved.\n");
printf("\n STATUS: Desconectando do servidor DOS...\n");
printf(" GOODBYE!\n");
mudarCor(7);
printf("==================================================\n");
system("pause");
Sleep(2000);
}

// --- 11. Creditos
void Creditos() {
transicao();
cls();
printf ("||================================================================================================================================================||\n");
printf ("||                                                                    Eco Mekha CO                                                                ||\n");
printf ("||================================================================================================================================================||\n");
printf ("||                                                          Responsaveis Pela Aplicacao Em C                                                      ||\n");
printf ("||================================================================================================================================================||\n");
printf ("||                                          Arthur Holanda Cavalcante de Melo            RA: 3025103750                                           ||\n");
printf ("||                                              Guilherme Luiz Morales                   RA: 3025102358                                           ||\n");
printf ("||                                            Joao Pedro da Silva Vicente                RA: 3025102790                                           ||\n");
printf ("||================================================================================================================================================||\n");
printf ("||                                                               Outros Desenvolvedores                                                           ||\n");
printf ("||================================================================================================================================================||\n");
printf ("||                                               Marcelo Vieira Da Silva                  RA: 3025102363                                          ||\n");
printf ("||                                          Marcus Vinicius Ferreira Siqueira             RA: 3025104806                                          ||\n");
printf ("||                                          Maria Eduarda Do Nascimento Gomes             RA: 3026102565                                          ||\n");
printf ("||                                               Murilo Akio Ribeiro Kota                 RA: 3025103571                                          ||\n");
printf ("||                                          Pablo Henrique Dos Santos Coutinho            RA: 3126100211                                          ||\n");
printf ("||                                          Paulo Henrique Da Conceicao Pereira           RA: 3025103487                                          ||\n");
printf ("||                                              Thiago Enrique Pereira Gomes              RA: 3025100300                                          ||\n");
printf ("||================================================================================================================================================||\n");
system("pause");
}

// --- 12. Instruções
void Instrucoes() {
transicao();
cls();
printf ("||================================================================================================================================================||\n");
printf ("||                                                                     Eco Mekha CO                                                               ||\n");
printf ("||================================================================================================================================================||\n");
printf ("||                                                                 Seja Bem Vindo(a)!                                                             ||\n");
printf ("||                                                                                                                                                ||\n");
printf ("||                        1.Cadastrar Cliente - (Esta Funcao Salva Informacoes Referentes Aos Seus Clientes)                                      ||\n");
printf ("||                                                                                                                                                ||\n");
printf ("||                        2.Listar Clientes - (Esta Funcao Exibe Na Tela Os Clientes Cadastrados)                                                 ||\n");
printf ("||                                                                                                                                                ||\n");
printf ("||                        3.Editar Cliente - (Esta Funcao Serve Para Atualizar As Informacoes Dos Clientes Ou Excluilos)                          ||\n");
printf ("||                                                                                                                                                ||\n");
printf ("||                        4.Cadastrar Produto - (Esta Funcao Registra Os Seus Produtos )                                                          ||\n");
printf ("||                                                                                                                                                ||\n");
printf ("||                        5.Listar Produtos - (Esta Funcao Exibe Os Produtos Cadastrados)                                                         ||\n");
printf ("||                                                                                                                                                ||\n");
printf ("||                        6.Editar Produtos - (Esta Funcao Serve Para Atualizar Os Seus Produtos)                                                 ||\n");
printf ("||                                                                                                                                                ||\n");
printf ("||                        7.Cadastra Venda - (Esta Funcao Serve Para Registrar A Venda De Um Dos Seus Produtos)                                   ||\n");
printf ("||                                                                                                                                                ||\n");
printf ("||                        8.Listar Vendas - (Esta Funcao Serve Para Exibir As suas Vendas E Um Grafico De Vendas)                                 ||\n");
printf ("||                                                                                                                                                ||\n");
printf ("||                        9.Estornar Venda - (Esta Funcao Serve Para Devolucoes E Cancelamento De Vendas)                                         ||\n");
printf ("||                                                                                                                                                ||\n");
printf ("||                        10.Sair - (Esta Funcao Serve Para Encerar Esta Maravilhosa Aplicacao)                                                   ||\n");
printf ("||                                                                                                                                                ||\n");
printf ("||                        11.Creditos - (Esta Funcao Serve Para Exibir Os Brilhantes Desenvolvedores Desta Aplicacao E Seus Associados)           ||\n");
printf ("||                                                                                                                                                ||\n");
printf ("||================================================================================================================================================||\n");

system("pause");
}

// --- MENU PRINCIPAL ---
int main() {
    int opcao;
    animacao_boot(); 
    tela_login();
    carregar_vendas_salvas();

    while(1) {
        cls();
        mudarCor(10);
        printf("EcoMekhasystems V22.052026| User login: %s\n", eh_manager ? "MANAGER" : "Account_Executive");
        printf("C:\\ECO_MEKHA\\SYSTEM>\n\n");
        mudarCor(7);
        if (eh_manager) {
        	printf("||==============================================================================================================================================||\n");
        	mudarCor(7);
	        printf("||                                                            ");mudarCor(10); printf("Bem Vindo(a)"); mudarCor(7); printf("                                                                      ||\n"); // \n no final para pular linha
        	printf("||==============================================================================================================================================||\n");
            printf("||                1. Cadastrar Cliente        4. Cadastrar Produto        7. Cadastrar Venda      10. Sair                                      ||\n");
            printf("||                2. Listar Clientes          5. Listar Produtos          8. Listar Vendas        11. Creditos                                  ||\n");
            printf("||                3. Editar Cliente           6. Editar Produto           9. Estornar Venda       12. Instrucoes                                ||\n");
            printf("||==============================================================================================================================================||\n");
        } else {
            mudarCor(7);
	        printf("||==============================================================================================================================================||\n"); // \n no final para pular linha
            mudarCor(7);
	        printf("||                                                            ");mudarCor(10); printf("Bem Vindo(a)"); mudarCor(7); printf("                                                                      ||\n"); // \n no final para pular linha
        	printf("||==============================================================================================================================================||\n");
            printf("||                                                       1. Cadastrar Cliente                                                                   ||\n");
            printf("||                                                       2. Realizar Compra                                                                     ||\n");
            printf("||                                                       3. Sair                                                                                ||\n");
        	printf("||==============================================================================================================================================||\n");
        }
        printf("Comando: ");
        if (scanf("%d", &opcao) != 1) { fflush(stdin); continue; }

        if (eh_manager) {
            switch(opcao) {
				case 1: Cadastro_Cli(); break; 
            	case 2: Listar_Cli(); break; 
            	case 3: Editar_Cli(); break; 
           	    case 4: Cadastro_Prod(); break; 
            	case 5: Listar_Prod(); break; 
            	case 6: Editar_Prod(); break; 
            	case 7: Cadastro_Venda(); break; 
            	case 8: Listar_Vendas(); break; 
            	case 9: Estorno(); break;
            	case 10: tela_saida(); exit(0); break;
            	case 11: Creditos(); break;
            	case 12: Instrucoes(); break;
                default: system("pause");
            }
        } else {
            switch(opcao) {
                case 1: Cadastro_Cli(); break;
				case 2: Cadastro_Venda(); break;	
                case 3: tela_saida(); exit(0);
                default: system("pause");
            }
        }
    }
    return 0;
}

