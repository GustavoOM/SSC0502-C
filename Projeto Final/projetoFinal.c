#include <stdio.h>
#include <string.h>

int opcoes();
void listaProdutos(struct produtos listaDeProdutos[], int quantidadeDeRegistros);
void cadastrarProduto(struct produtos listaDeProdutos[], int quantidadeDeRegistros, struct configuracoes *configuracao);
int procuraPosicaoValidaProduto(struct produtos listaDeProdutos[],int quantidadeDeRegistros);
int procuraPosicaoPeloCodigoDeProduto(int codigoProduto, struct produtos listaDeProdutos[],int quantidadeDeRegistros);
void excluirProduto(struct produtos listaDeProdutos[], int quantidadeDeRegistros);
void editarProduto(struct produtos listaDeProdutos[], int quantidadeDeRegistros);
void procurarProduto(struct produtos listaDeProdutos[], int quantidadeDeRegistros);
void listaVendas(struct vendas listaDeVendas[], int quantidadeDeRegistros);
int procuraPosicaoValidaVenda(struct vendas listaDeVendas[],int quantidadeDeRegistros);
int procuraPosicaoPeloCodigoDeVenda(int codigoVenda, struct vendas listaDeVendas[], int quantidadeDeRegistros);
void cadastrarVenda(struct vendas listaDeVendas[], struct produtos listaDeProdutos[], int quantidadeDeRegistros, struct configuracoes *configuracao);
void excluirVenda(struct vendas listaDeVendas[], struct produtos listaDeProdutos[], int quantidadeDeRegistros);
void procurarVenda(struct vendas listaDeVendas[], int quantidadeDeRegistros);
void vendasDeUmMes(struct vendas listaDeVendas[], int quantidadeDeRegistros);
void listaVendasDeUmProduto(struct vendas listaDeVendas[], int quantidadeDeRegistros);

int fsize(FILE *fp);
void dataFormatada (int data);
int ehBissexto(int ano);
void precioneEnter();

struct produtos{
    char nome[50];
    int codigo;
    float preco;
    int estoque;
};

struct vendas{
    int codigo;
    int quantidade;
    int data;
    int codigoProduto;
    char nomeProduto[50];
    float precoProduto;
};

struct configuracoes{
    int contadorProdutos;
    int contadorVendas;
};

int main(){

    //Declaração das variáveis
    int quantidadeDeRegistros = 100;
    FILE *arquivoDeProdutos;
    FILE *arquivoDeVendas;
    FILE *arquivoDeConfiguracoes;
    struct produtos listaDeProdutos[quantidadeDeRegistros];
    struct vendas listaDeVendas[quantidadeDeRegistros];
    struct configuracoes configuracao;

    //Abre arquivo de produtos e adiciona no array
    if((arquivoDeProdutos = fopen("produtos.txt", "rb+")) == NULL || fsize(arquivoDeProdutos)==0){
        if((arquivoDeProdutos = fopen("produtos.txt", "wb+")) == NULL){
            printf("\nErro ao abrir o arquivo de produtos.\n");
            return 0;
        }
        for(int i = 0; i < quantidadeDeRegistros; i++){
            listaDeProdutos[i].codigo = 0;
            listaDeProdutos[i].estoque = 0;
            listaDeProdutos[i].preco = 0;
            strcpy(listaDeProdutos[i].nome,"");
        }
        fwrite(listaDeProdutos,sizeof(struct produtos), quantidadeDeRegistros, arquivoDeProdutos);
        fclose(arquivoDeProdutos);
    }
    else{
        fseek(arquivoDeProdutos,0,SEEK_SET);
        fread(listaDeProdutos, sizeof(struct produtos), quantidadeDeRegistros, arquivoDeProdutos);
        fclose(arquivoDeProdutos);
    }

    //Abre arquivo de vendas e adiciona no array
    if((arquivoDeVendas = fopen("vendas.txt", "rb+")) == NULL || fsize(arquivoDeVendas)==0){
        if((arquivoDeVendas = fopen("vendas.txt", "wb+")) == NULL){
            printf("\nErro ao abrir o arquivo de vendas.\n");
            return 0;
        }
        for(int i = 0; i < quantidadeDeRegistros; i++){
            listaDeVendas[i].codigo = 0;
            listaDeVendas[i].data = 0;
            listaDeVendas[i].quantidade = 0;
            listaDeVendas[i].codigoProduto = 0;
            listaDeVendas[i].precoProduto = 0;
            strcpy(listaDeVendas[i].nomeProduto,"");
        }
        fwrite(listaDeVendas,sizeof(struct vendas), quantidadeDeRegistros, arquivoDeVendas);
        fclose(arquivoDeVendas);
    }
    else{
        fseek(arquivoDeVendas,0,SEEK_SET);
        fread(listaDeVendas, sizeof(struct vendas), quantidadeDeRegistros, arquivoDeVendas);
        fclose(arquivoDeVendas);
    }

    //Abre arquivo de configurações
    if((arquivoDeConfiguracoes = fopen("configuracao.txt", "rb+")) == NULL || fsize(arquivoDeConfiguracoes)==0){
        if((arquivoDeConfiguracoes = fopen("configuracao.txt", "wb+")) == NULL){
            printf("\nErro ao abrir o arquivo de configuração.\n");
            return 0;
        }
        configuracao.contadorProdutos = 1;
        configuracao.contadorVendas = 1;
        fwrite(&configuracao,sizeof(struct configuracoes), 1, arquivoDeConfiguracoes);
        fclose(arquivoDeConfiguracoes);
    }
    else{
        fseek(arquivoDeConfiguracoes,0,SEEK_SET);
        fread(&configuracao, sizeof(struct configuracoes), 1, arquivoDeConfiguracoes);
        fclose(arquivoDeConfiguracoes);
    }
    
    while (1){
        switch (opcoes()){
        
            case 0:
                return 0;

            case 1:
                cadastrarProduto(listaDeProdutos,quantidadeDeRegistros,&configuracao);
                break;

            case 2:
                listaProdutos(listaDeProdutos,quantidadeDeRegistros);
                break;

            case 3:
                procurarProduto(listaDeProdutos, quantidadeDeRegistros);
                break;

            case 4:
                editarProduto(listaDeProdutos,quantidadeDeRegistros);
                break;

            case 5:
                excluirProduto(listaDeProdutos,quantidadeDeRegistros);
                break;

            case 6:
                cadastrarVenda(listaDeVendas, listaDeProdutos, quantidadeDeRegistros, &configuracao);
                break;

            case 7:
                listaVendas(listaDeVendas, quantidadeDeRegistros);
                break;

            case 8:
                procurarVenda(listaDeVendas,quantidadeDeRegistros);
                break;

            case 9:
                excluirVenda(listaDeVendas,listaDeProdutos,quantidadeDeRegistros);
                break;

            case 10:
                vendasDeUmMes(listaDeVendas, quantidadeDeRegistros);
                break;

            case 11:
                listaVendasDeUmProduto(listaDeVendas,quantidadeDeRegistros);
                break;

            case 12:
                break;

            default:
                break;
        }
        if((arquivoDeProdutos = fopen("produtos.txt", "wb+")) == NULL){
            printf("\nErro ao abrir o arquivo de produtos.\n");
            return 0;
        }
        fwrite(listaDeProdutos,sizeof(struct produtos), quantidadeDeRegistros, arquivoDeProdutos);
        fclose(arquivoDeProdutos);
        if((arquivoDeVendas = fopen("vendas.txt", "wb+")) == NULL){
            printf("\nErro ao abrir o arquivo de vendas.\n");
            return 0;
        }
        fwrite(listaDeVendas,sizeof(struct vendas), quantidadeDeRegistros, arquivoDeVendas);
        fclose(arquivoDeVendas);
        if((arquivoDeConfiguracoes = fopen("configuracao.txt", "wb+")) == NULL){
            printf("\nErro ao abrir o arquivo de configuração.\n");
            return 0;
        }
        fwrite(&configuracao,sizeof(struct configuracoes), 1, arquivoDeConfiguracoes);
        fclose(arquivoDeConfiguracoes);
    }
    
}

int opcoes(){
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-= MENU =-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    int opicao = -1;
    while(opicao < 0 || opicao > 13){
        printf("Digite uma opção!\n");
        printf("(1) Cadastrar um produto\n");
        printf("(2) Listar todos produtos\n");
        printf("(3) Procurar um produto\n");
        printf("(4) Editar produto\n");
        printf("(5) Excluir produto \n");
        printf("(6) Realizar uma venda\n");
        printf("(7) Listar todas vendas\n");
        printf("(8) Procurar uma venda\n");
        printf("(9) Excluir venda\n");
        printf("(10) Vendas realizadas em um mês\n");
        printf("(11) Vendas de um produto\n");
        printf("(12) Listar produtos por ordem de mais vendidos\n");
        printf("(0) Fechar sistema\n");
        printf("Escolha: ");
        scanf("%d",&opicao);
        if(opicao < 0 || opicao > 13)
            printf("\n\n\n\n\nOpção invalida, por favor tente novamente\n\n");
    }
    return opicao;
}

void listaProdutos(struct produtos listaDeProdutos[], int quantidadeDeRegistros){
    printf("\n=-=-=-=-=-=-=-=-=-=-=-= LISTA DE PRODUTO =-=-=-=-=-=-=-=-=-=-=\n");
    for(int i = 0; i<quantidadeDeRegistros; i++){
        if(listaDeProdutos[i].codigo != 0){
            if(listaDeProdutos[i].codigo < 10)
                printf("\n=-=-=-=-=- PRODUTO  0%d -=-=-=-=-=",listaDeProdutos[i].codigo);
            else
                printf("\n=-=-=-=-=- PRODUTO  %d -=-=-=-=-=",listaDeProdutos[i].codigo);
            printf("\nCódigo: %d",listaDeProdutos[i].codigo);
            printf("\nNome: %s",listaDeProdutos[i].nome);
            printf("\nPreço: R$%.2f",listaDeProdutos[i].preco);
            printf("\n%d em estoque",listaDeProdutos[i].estoque);
            printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n",listaDeProdutos[i].codigo);   
        }
    }
    precioneEnter();
}

void cadastrarProduto(struct produtos listaDeProdutos[], int quantidadeDeRegistros, struct configuracoes *configuracao){
    printf("\n=-=-=-=-=-=-=-=-=-=-= CADASTRO DE PRODUTO =-=-=-=-=-=-=-=-=-=-\n");
    int lugarParaSalvar = procuraPosicaoValidaProduto(listaDeProdutos,quantidadeDeRegistros);
    if(lugarParaSalvar != -1){
        listaDeProdutos[lugarParaSalvar].codigo = configuracao->contadorProdutos;
        configuracao->contadorProdutos++;
        printf("O registro terá como código %d!\n", listaDeProdutos[lugarParaSalvar].codigo);
        printf("Digite o nome do produto: ");
        setbuf(stdin, 0);
        fgets(listaDeProdutos[lugarParaSalvar].nome,49,stdin);
        listaDeProdutos[lugarParaSalvar].nome[strcspn(listaDeProdutos[lugarParaSalvar].nome, "\n")] = 0;
        printf("Digite o preço do produto: ");
        scanf("%f",&listaDeProdutos[lugarParaSalvar].preco);
        printf("Digite a quantidade em estoque: ");
        scanf("%d",&listaDeProdutos[lugarParaSalvar].estoque);
        printf("\nProduto salvo com sucesso!\n");
    }
    else{
        printf("\n\nNão há espaço para novos produtos no estoque!\n");
    }
    precioneEnter();
}

int procuraPosicaoValidaProduto(struct produtos listaDeProdutos[],int quantidadeDeRegistros){
    for(int i = 0; i < quantidadeDeRegistros; i++)
        if(listaDeProdutos[i].codigo == 0)
            return i;
    return -1;
}

int procuraPosicaoPeloCodigoDeProduto(int codigoProduto, struct produtos listaDeProdutos[],int quantidadeDeRegistros){
    for(int i = 0; i < quantidadeDeRegistros; i++)
        if(codigoProduto == listaDeProdutos[i].codigo)
            return i;
    return -1;
}

void excluirProduto(struct produtos listaDeProdutos[], int quantidadeDeRegistros){
    printf("\n=-=-=-=-=-=-=-=-=-=-=-= EXCLUIR PRODUTO =-=-=-=-=-=-=-=-=-=-=-\n");
    int posicaoExcluida;
    while (1){
        printf("Digite o código que deseja remover (0 para cancelar operação): ");
        scanf("%d",&posicaoExcluida);
        if(posicaoExcluida == 0)
            break;
        posicaoExcluida = procuraPosicaoPeloCodigoDeProduto(posicaoExcluida,listaDeProdutos,quantidadeDeRegistros);
        if(posicaoExcluida != -1){
            int certeza;
            printf("\nVocê tem certeza que deseja excluir o item %s?\n1 para confirmar ou 0 para cancelar: ",listaDeProdutos[posicaoExcluida].nome);
            scanf("%d",&certeza);
            if(certeza==1){
                listaDeProdutos[posicaoExcluida].codigo = 0;
                strcpy(listaDeProdutos[posicaoExcluida].nome, "");
                listaDeProdutos[posicaoExcluida].preco = 0;
                listaDeProdutos[posicaoExcluida].estoque = 0;
                printf("\nProduto excluido com sucesso!\n");
                precioneEnter();
                break;
            }
            printf("\nOperação cancelada!\n");
            precioneEnter();
            break;
        }
        printf("\nCódigo de produto inválido ou não encontrado\n\n"); 
    }
}

void editarProduto(struct produtos listaDeProdutos[], int quantidadeDeRegistros){
    printf("\n=-=-=-=-=-=-=-=-=-=-=-=- EDITAR PRODUTO -=-=-=-=-=-=-=-=-=-=-=\n");
    int posicaoEditada;
    while (1){
        printf("Digite o código que deseja alterar (0 para cancelar operação): ");
        scanf("%d",&posicaoEditada);
        if(posicaoEditada == 0)
            break;
        posicaoEditada = procuraPosicaoPeloCodigoDeProduto(posicaoEditada,listaDeProdutos,quantidadeDeRegistros);
        if(posicaoEditada != -1){
            printf("Nome -> de %s para: ",listaDeProdutos[posicaoEditada].nome);
            setbuf(stdin, 0);
            fgets(listaDeProdutos[posicaoEditada].nome,49,stdin);
            listaDeProdutos[posicaoEditada].nome[strcspn(listaDeProdutos[posicaoEditada].nome, "\n")] = 0;
            printf("Preço -> de R$%.2f para: R$",listaDeProdutos[posicaoEditada].preco);
            scanf("%f",&listaDeProdutos[posicaoEditada].preco);
            printf("Quantidade em estoque -> de %d para: ",listaDeProdutos[posicaoEditada].estoque);
            scanf("%d",&listaDeProdutos[posicaoEditada].estoque);
            printf("\nProduto editado com sucesso!\n");
            precioneEnter();
            break;
        }
        printf("\nCódigo de produto inválido ou não encontrado\n\n"); 
    }
}

void procurarProduto(struct produtos listaDeProdutos[], int quantidadeDeRegistros){
    printf("\n=-=-=-=-=-=-=-=-=-=-=-= PROCURAR PRODUTO =-=-=-=-=-=-=-=-=-=-=\n");
    int posicaoDeBusca;
    while (1){
        printf("Digite o código que deseja procurar (0 para cancelar operação): ");
        scanf("%d",&posicaoDeBusca);
        if(posicaoDeBusca == 0)
            break;
        posicaoDeBusca = procuraPosicaoPeloCodigoDeProduto(posicaoDeBusca,listaDeProdutos,quantidadeDeRegistros);
        if(posicaoDeBusca != -1){
            if(listaDeProdutos[posicaoDeBusca].codigo < 10)
                printf("\n=-=-=-=-=- PRODUTO  0%d -=-=-=-=-=",listaDeProdutos[posicaoDeBusca].codigo);
            else
                printf("\n=-=-=-=-=- PRODUTO  %d -=-=-=-=-=",listaDeProdutos[posicaoDeBusca].codigo);
            printf("\nCódigo: %d",listaDeProdutos[posicaoDeBusca].codigo);
            printf("\nNome: %s",listaDeProdutos[posicaoDeBusca].nome);
            printf("\nPreço: R$%.2f",listaDeProdutos[posicaoDeBusca].preco);
            printf("\n%d em estoque",listaDeProdutos[posicaoDeBusca].estoque);
            printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n",listaDeProdutos[posicaoDeBusca].codigo);  
            precioneEnter();
            break;
        }
        printf("\nCódigo de produto inválido ou não encontrado\n\n"); 
    }
}

void listaVendas(struct vendas listaDeVendas[], int quantidadeDeRegistros){
    printf("\n=-=-=-=-=-=-=-=-=-=-= LISTA DE VENDAS =-=-=-=-=-=-=-=-=-=-=-\n");
    for(int i = 0; i<quantidadeDeRegistros; i++){
        if(listaDeVendas[i].codigo != 0){
            if(listaDeVendas[i].codigo < 10)
                printf("\n=-=-=-=-=-= VENDA  0%d =-=-=-=-=-=\n", listaDeVendas[i].codigo);
            else
                printf("\n=-=-=-=-=-= VENDA  %d =-=-=-=-=-=\n", listaDeVendas[i].codigo);
            printf("Compra realizada em ");
            dataFormatada(listaDeVendas[i].data);
            printf("\nCódigo do produto vendido: %d",listaDeVendas[i].codigoProduto);
            printf("\n%d x %s",listaDeVendas[i].quantidade,listaDeVendas[i].nomeProduto);
            printf("\nTotal: R$%.2f",listaDeVendas[i].precoProduto*listaDeVendas[i].quantidade);
            printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        }
    }
    precioneEnter();
}

int procuraPosicaoValidaVenda(struct vendas listaDeVendas[],int quantidadeDeRegistros){
    for(int i = 0; i < quantidadeDeRegistros; i++)
        if(listaDeVendas[i].codigo == 0)
            return i;
    return -1;
}

int procuraPosicaoPeloCodigoDeVenda(int codigoVenda, struct vendas listaDeVendas[], int quantidadeDeRegistros){
    for(int i = 0; i < quantidadeDeRegistros; i++)
        if(listaDeVendas[i].codigo == codigoVenda)
            return i;
    return -1;
}

void cadastrarVenda(struct vendas listaDeVendas[], struct produtos listaDeProdutos[], int quantidadeDeRegistros, struct configuracoes *configuracao){
    printf("\n-=-=-=-=-=-=-=-=-=-=-= CADASTRO DE VENDA =-=-=-=-=-=-=-=-=-=-=\n");
    int lugarParaSalvar = procuraPosicaoValidaVenda(listaDeVendas,quantidadeDeRegistros);
    if(lugarParaSalvar != -1){
        int localDoProduto = -1;
        while (localDoProduto == -1){
            printf("Código do produto que deseja adicionar a venda (0 para cancelar operação): ");
            scanf("%d",&localDoProduto);
            if (localDoProduto == 0)
                return;
            localDoProduto = procuraPosicaoPeloCodigoDeProduto(localDoProduto,listaDeProdutos,quantidadeDeRegistros);
            if(localDoProduto == -1)
                printf("\nCódigo de produto inválido ou não encontrado\n\n");
        }

        int quantidadeEstoque = -1;
        while (quantidadeEstoque == -1){
            printf("\nO produto %s de id %d possui %d unidades em estoque!\n", listaDeProdutos[localDoProduto].nome, listaDeProdutos[localDoProduto].codigo, listaDeProdutos[localDoProduto].estoque);
            printf("\nQuantas unidades deseja adicionar a venda (0 para cancelar operação): ");
            scanf("%d",&quantidadeEstoque);
            if(quantidadeEstoque == 0)
                return;
            else if (quantidadeEstoque < 0 || quantidadeEstoque > listaDeProdutos[localDoProduto].estoque){
                printf("\nImpossível retirar do estoque esse valor, por favor digite um número entre 1 e %d\n", listaDeProdutos[localDoProduto].estoque);
                quantidadeEstoque = -1;
            }
        }

        int ano = -1;
        while (ano < 0){
            printf("\nDigite o ano da venda (0 para cancelar operação): ");
            scanf("%d", &ano);
            if(ano == 0)
                return;
            else if(ano < 0)
                printf("\nNosso sistema não trata anos antes de Cristo, por favor insira um ano superior a 0\n");
        }

        int mes = -1;
        while (mes == -1){
            printf("\nDigite o mês da venda (0 para cancelar operação): ");
            scanf("%d", &mes);
            if(mes == 0)
                return;
            else if(mes < 1 || mes > 12){
                printf("\nMês inválido, por favor digite um valor entre 1 e 12\n");
                mes = -1;
            }
        }
        
        int quantidadeDeDiasPorMes[12] = {31,28,31,31,30,31,31,30,31,30,31};
        if(mes == 2)
            if(ehBissexto(ano))
                quantidadeDeDiasPorMes[1]++;

        int dia = -1;
        while (dia == -1){
            printf("\nDigite o dia da venda (0 para cancelar operação): ");
            scanf("%d",&dia);
            if(dia == 0)
                return;
            else if(dia < 0 || dia > quantidadeDeDiasPorMes[mes-1]){
                printf("\nDia inválido, por favor digite um valor entre 1 e %d\n",quantidadeDeDiasPorMes[mes-1]);
                dia = -1;
            }
        }

        int data = ano*10000 + mes*100 + dia;
        
        listaDeVendas[lugarParaSalvar].codigo = configuracao->contadorVendas;
        configuracao->contadorVendas++;
        listaDeVendas[lugarParaSalvar].data = data;
        listaDeVendas[lugarParaSalvar].quantidade = quantidadeEstoque;
        listaDeVendas[lugarParaSalvar].codigoProduto = listaDeProdutos[localDoProduto].codigo;
        listaDeVendas[lugarParaSalvar].precoProduto = listaDeProdutos[localDoProduto].preco;
        strcpy(listaDeVendas[lugarParaSalvar].nomeProduto,listaDeProdutos[localDoProduto].nome);

        listaDeProdutos[localDoProduto].estoque -= quantidadeEstoque;

        if(listaDeVendas[lugarParaSalvar].codigo < 10)
            printf("\n=-=-=-=-=-= VENDA  0%d =-=-=-=-=-=\n", listaDeVendas[lugarParaSalvar].codigo);
        else
            printf("\n=-=-=-=-=-= VENDA  %d =-=-=-=-=-=\n", listaDeVendas[lugarParaSalvar].codigo);
        printf("Compra realizada em ");
        dataFormatada(listaDeVendas[lugarParaSalvar].data);
        printf("\nCódigo do produto vendido: %d",listaDeVendas[lugarParaSalvar].codigoProduto);
        printf("\n%d x %s",listaDeVendas[lugarParaSalvar].quantidade,listaDeVendas[lugarParaSalvar].nomeProduto);
        printf("\nTotal: R$%.2f",listaDeVendas[lugarParaSalvar].precoProduto*listaDeVendas[lugarParaSalvar].quantidade);
        printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n", listaDeVendas[lugarParaSalvar].codigo);
    }
    else{
        printf("\n\nNão há espaço para novas vendas!\n\n");
    }
    precioneEnter();
}

void procurarVenda(struct vendas listaDeVendas[], int quantidadeDeRegistros){
    printf("\n=-=-=-=-=-=-=-=-=-=-=-=- PROCURAR VENDA -=-=-=-=-=-=-=-=-=-=-=\n");
    int posicaoDeBusca;
    while (1){
        printf("Digite o código que deseja procurar (0 para cancelar operação): ");
        scanf("%d",&posicaoDeBusca);
        if(posicaoDeBusca == 0)
            break;
        posicaoDeBusca = procuraPosicaoPeloCodigoDeVenda(posicaoDeBusca,listaDeVendas,quantidadeDeRegistros);
        if(posicaoDeBusca != -1){
            if(listaDeVendas[posicaoDeBusca].codigo < 10)
                printf("\n=-=-=-=-=-= VENDA  0%d =-=-=-=-=-=",listaDeVendas[posicaoDeBusca].codigo);
            else
                printf("\n=-=-=-=-=-= VENDA  %d =-=-=-=-=-=",listaDeVendas[posicaoDeBusca].codigo);
            printf("Venda realizada em ");
            dataFormatada(listaDeVendas[posicaoDeBusca].data);
            printf("\nCódigo do produto vendido: %d",listaDeVendas[posicaoDeBusca].codigoProduto);
            printf("\n%d x %s",listaDeVendas[posicaoDeBusca].quantidade,listaDeVendas[posicaoDeBusca].nomeProduto);
            printf("\nTotal: R$%.2f",listaDeVendas[posicaoDeBusca].precoProduto*listaDeVendas[posicaoDeBusca].quantidade);
            printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n", listaDeVendas[posicaoDeBusca].codigo);
            precioneEnter();
            break;
        }
        printf("\nCódigo de venda inválido ou não encontrado\n\n"); 
    }
}

void excluirVenda(struct vendas listaDeVendas[], struct produtos listaDeProdutos[], int quantidadeDeRegistros){
    printf("\n=-=-=-=-=-=-=-=-=-=-=-= EXCLUIR  VENDA =-=-=-=-=-=-=-=-=-=-=\n");
    int posicaoDeBusca;
    while (1){
        printf("Digite o código que deseja excluir (0 para cancelar operação): ");
        scanf("%d",&posicaoDeBusca);
        if(posicaoDeBusca == 0)
            break;
        posicaoDeBusca = procuraPosicaoPeloCodigoDeVenda(posicaoDeBusca,listaDeVendas,quantidadeDeRegistros);
        if(posicaoDeBusca != -1){
            int certeza;
            printf("\nVocê tem certeza que deseja excluir a venda %d que possue %d %s com o valor de R$%.2f?\n1 para confirmar ou 0 para cancelar: ",listaDeVendas[posicaoDeBusca].codigo,listaDeVendas[posicaoDeBusca].quantidade,listaDeVendas[posicaoDeBusca].nomeProduto, listaDeVendas[posicaoDeBusca].quantidade*listaDeVendas[posicaoDeBusca].precoProduto);
            scanf("%d",&certeza);
            if(certeza==1){
                int produtosDevolvidos;
                printf("\nOs produtos foram devolvidos?\n1 para sim ou 0 para não: ");
                scanf("%d",&produtosDevolvidos);
                if(produtosDevolvidos == 1){
                    int localDoProduto = procuraPosicaoPeloCodigoDeProduto(listaDeVendas[posicaoDeBusca].codigoProduto,listaDeProdutos,quantidadeDeRegistros);
                    if(localDoProduto != -1)
                        listaDeProdutos[localDoProduto].estoque += listaDeVendas[posicaoDeBusca].quantidade;
                }
                listaDeVendas[posicaoDeBusca].codigo = 0;
                listaDeVendas[posicaoDeBusca].codigoProduto = 0;
                listaDeVendas[posicaoDeBusca].data = 0;
                listaDeVendas[posicaoDeBusca].precoProduto = 0;
                listaDeVendas[posicaoDeBusca].quantidade = 0;
                strcpy(listaDeVendas[posicaoDeBusca].nomeProduto,"");



                printf("\nVenda excluida com sucesso!\n");
                precioneEnter();
                break;
            }
            printf("\nOperação cancelada!\n");
            precioneEnter();
            break;
        }
        printf("\nCódigo de venda inválido ou não encontrado\n\n"); 
    }
}

void listaVendasDeUmProduto(struct vendas listaDeVendas[], int quantidadeDeRegistros){
    printf("\n=-=-=-=-=-=-=-=-=-=- VENDAS DE UM ITEM -=-=-=-=-=-=-=-=-=-=-\n");
    printf("Digite o código do item que deseja procurar (0 para cancelar operação): ");
    int codigoProduto;
    scanf("%d",&codigoProduto);
    if(codigoProduto == 0)
        return;
    int totalDeItens = 0;
    float valorTotal = 0;
    char nomeProduto[50]; 
    for(int i = 0; i<quantidadeDeRegistros; i++){
        if(listaDeVendas[i].codigoProduto == codigoProduto){
            if(listaDeVendas[i].codigo < 10)
                printf("\n=-=-=-=-=-= VENDA  0%d =-=-=-=-=-=\n", listaDeVendas[i].codigo);
            else
                printf("\n=-=-=-=-=-= VENDA  %d =-=-=-=-=-=\n", listaDeVendas[i].codigo);
            printf("Compra realizada em ");
            dataFormatada(listaDeVendas[i].data);
            printf("\nCódigo do produto vendido: %d",listaDeVendas[i].codigoProduto);
            printf("\n%d x %s",listaDeVendas[i].quantidade,listaDeVendas[i].nomeProduto);
            totalDeItens += listaDeVendas[i].quantidade;
            strcpy(nomeProduto,listaDeVendas[i].nomeProduto);
            printf("\nTotal: R$%.2f",listaDeVendas[i].precoProduto*listaDeVendas[i].quantidade);
            valorTotal += listaDeVendas[i].precoProduto*listaDeVendas[i].quantidade;
            printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        }
    }
    if(totalDeItens == 0)
        printf("\nNão há vendas cadastradas com esse item!");
    else
        printf("\n=-=-=-=- SOMA DAS VENDAS =-=-=-=-=\n");
        printf("\n%d x %s",totalDeItens,nomeProduto);
        printf("\nTotal: R$%.2f",valorTotal);
        printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");

    precioneEnter();
}

void vendasDeUmMes(struct vendas listaDeVendas[], int quantidadeDeRegistros){
    int ano = -1;
        while (ano < 0){
            printf("\nDigite o ano da venda (0 para cancelar operação): ");
            scanf("%d", &ano);
            if(ano == 0)
                return;
            else if(ano < 0)
                printf("\nNosso sistema não trata anos antes de Cristo, por favor insira um ano superior a 0\n");
        }

        int mes = -1;
        while (mes == -1){
            printf("\nDigite o mês da venda (0 para cancelar operação): ");
            scanf("%d", &mes);
            if(mes == 0)
                return;
            else if(mes < 1 || mes > 12){
                printf("\nMês inválido, por favor digite um valor entre 1 e 12\n");
                mes = -1;
            }
        }

        int dataInicial = ano*10000 + mes*100;
        int dataFinal = ano*10000 + (mes+1)*100;

        float valorTotal = 0;
        for(int i = 0; i<quantidadeDeRegistros; i++){
            if(listaDeVendas[i].data > dataInicial && listaDeVendas[i].data < dataFinal){
                if(listaDeVendas[i].codigo < 10)
                    printf("\n=-=-=-=-=-= VENDA  0%d =-=-=-=-=-=\n", listaDeVendas[i].codigo);
                else
                    printf("\n=-=-=-=-=-= VENDA  %d =-=-=-=-=-=\n", listaDeVendas[i].codigo);
                printf("Compra realizada em ");
                dataFormatada(listaDeVendas[i].data);
                printf("\nCódigo do produto vendido: %d",listaDeVendas[i].codigoProduto);
                printf("\n%d x %s",listaDeVendas[i].quantidade,listaDeVendas[i].nomeProduto);
                printf("\nTotal: R$%.2f",listaDeVendas[i].precoProduto*listaDeVendas[i].quantidade);
                valorTotal += listaDeVendas[i].precoProduto*listaDeVendas[i].quantidade;
                printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
            }
        }
        printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("\nVALOR DAS VENDAS NO MÊS %d DO ANO DE %d: R$%.2f\n",mes,ano,valorTotal);
        printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

        precioneEnter();
}

int fsize(FILE *fp){
    int prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz=ftell(fp);
    fseek(fp,prev,SEEK_SET);
    return sz;
}

void dataFormatada (int data){

    int dia = data%100;
    data -= dia;

    data *= 0.01;
    int mes = data%100;
    data -= mes;

    data *= 0.01;
    int ano = data;

    if(dia < 10 && mes < 10)
        printf("0%d/0%d/%d",dia,mes,ano);
    else if(dia < 10)
        printf("0%d/%d/%d",dia,mes,ano);
    else if(mes < 10)
        printf("%d/0%d/%d",dia,mes,ano);
    else
        printf("%d/%d/%d",dia,mes,ano);
}

int ehBissexto(int ano){
    if((ano % 400 == 0) || ((ano % 4 == 0) && (ano % 100 != 0)))
        return 1;
    return 0;
}

void precioneEnter(){
    char aux[10];
    printf("\nPrecione ENTER para continuar!");
    setbuf(stdin, 0);
    fgets(aux,9,stdin);
    printf("\n");
}