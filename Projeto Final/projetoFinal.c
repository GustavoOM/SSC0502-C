#include <stdio.h>
#include <string.h>

int opcoes();
int fsize(FILE *fp);
void listaProdutos(struct produtos listaDeProdutos[], int quantidadeDeRegistros);
void cadastrarProduto(struct produtos listaDeProdutos[], int quantidadesDeRegistros);
int procuraPosicaoValidaProduto(struct produtos listaDeProdutos[],int quantidadesDeRegistros);
void excluirProduto(struct produtos listaDeProdutos[], int quantidadesDeRegistros);
void editarProduto(struct produtos listaDeProdutos[], int quantidadesDeRegistros);
void procurarProduto(struct produtos listaDeProdutos[], int quantidadesDeRegistros);
void listaVendas(struct vendas listaDeVendas[], int quantidadesDeRegistros);
void dataFormatada (int data);
int procuraPosicaoValidaVenda(struct vendas listaDeVendas[],int quantidadesDeRegistros);
void cadastrarVenda(struct vendas listaDeVendas[], struct produtos listaDeProdutos[], int quantidadesDeRegistros);

struct produtos{
    char nome[50];
    int codigo;
    float preco;
    int estoque;
};

struct vendas{
    int codigo;
    int codigoProduto;
    int quantidade;
    int data;
};

int main(){

    //Declaração das variáveis
    int quantidadeDeRegistros = 100;
    FILE *arquivoDeProdutos;
    FILE *arquivoDeVendas;
    struct produtos listaDeProdutos[quantidadeDeRegistros];
    struct vendas listaDeVendas[quantidadeDeRegistros];

    //Abre arquivo de produtos e adiciona no array
    if((arquivoDeProdutos = fopen("produtos.txt", "rb+")) == NULL){
        printf("\nErro ao abrir o arquivo de produtos.\n");
        return 0;
    }
    if(fsize(arquivoDeProdutos)==0){
        fclose(arquivoDeProdutos);
        if((arquivoDeProdutos = fopen("produtos.txt", "wb+")) == NULL){
            printf("\nErro ao abrir o arquivo de produtos.\n");
            return 0;
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
    if((arquivoDeVendas = fopen("vendas.txt", "rb+")) == NULL){
        printf("\nErro ao abrir o arquivo de vendas.\n");
        return 0;
    }
    if(fsize(arquivoDeVendas)==0){
        fclose(arquivoDeVendas);
        if((arquivoDeVendas = fopen("vendas.txt", "rb+")) == NULL){
            printf("\nErro ao abrir o arquivo de vendas.\n");
            return 0;
        }
        fwrite(listaDeVendas,sizeof(struct produtos), quantidadeDeRegistros, arquivoDeVendas);
        fclose(arquivoDeVendas);
    }
    else{
        fseek(arquivoDeVendas,0,SEEK_SET);
        fread(listaDeVendas, sizeof(struct vendas), quantidadeDeRegistros, arquivoDeVendas);
        fclose(arquivoDeVendas);
    }
    
    while (1){
        switch (opcoes()){
        
            case 0:
                return 0;

            case 1:
                cadastrarProduto(listaDeProdutos,quantidadeDeRegistros);
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
                cadastrarVenda(listaDeVendas, listaDeProdutos, quantidadeDeRegistros);
                break;

            case 7:
                listaVendas(listaDeVendas,quantidadeDeRegistros);
                break;

            case 8:
                break;

            case 9:
                break;

            case 10:
                break;

            case 11:
                break;

            case 12:
                break;

            case 13:
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
        printf("(8) Procurar uma venda por data ou número\n");
        printf("(9) Editar venda\n");
        printf("(10) Excluir venda\n");
        printf("(11) Vendas realizadas em um mês\n");
        printf("(12) Vendas de um produto\n");
        printf("(13) Listar produtos por ordem de mais vendidos\n");
        printf("(0) Fechar sistema\n");
        printf("Escolha: ");
        scanf("%d",&opicao);
        if(opicao < 0 || opicao > 13)
            printf("\n\n\n\n\nOpção invalida, por favor tente novamente\n\n");
    }
    return opicao;
}

int fsize(FILE *fp){
    int prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz=ftell(fp);
    fseek(fp,prev,SEEK_SET);
    return sz;
}

void listaProdutos(struct produtos listaDeProdutos[], int quantidadeDeRegistros){
    printf("\n=-=-=-=-=-=-=-=-=-=-=-= LISTA DE PRODUTO =-=-=-=-=-=-=-=-=-=-=\n");
    for(int i = 0; i<quantidadeDeRegistros; i++){
        if(listaDeProdutos[i].codigo != 0){
            printf("\n-=-=-=-=-==-=-=");
            printf("\nCódigo: %d",listaDeProdutos[i].codigo);
            printf("\nNome: %s",listaDeProdutos[i].nome);
            printf("\nPreço: R$%.2f",listaDeProdutos[i].preco);
            printf("\n%d em estoque\n",listaDeProdutos[i].estoque);
        }
    }
    char aux[10];
    printf("\nPrecione ENTER para continuar!");
    setbuf(stdin, 0);
    fgets(aux,9,stdin);
    printf("\n");
}

void cadastrarProduto(struct produtos listaDeProdutos[], int quantidadesDeRegistros){
    printf("\n=-=-=-=-=-=-=-=-=-=-= CADASTRO DE PRODUTO =-=-=-=-=-=-=-=-=-=-\n");
    int lugarParaSalvar = procuraPosicaoValidaProduto(listaDeProdutos,quantidadesDeRegistros);
    if(lugarParaSalvar != -1){
        listaDeProdutos[lugarParaSalvar].codigo = lugarParaSalvar + 1;
        printf("O registro terá como código %d!\n", listaDeProdutos[lugarParaSalvar].codigo);
        printf("Digite o nome do produto: ");
        setbuf(stdin, 0);
        fgets(listaDeProdutos[lugarParaSalvar].nome,49,stdin);
        listaDeProdutos[lugarParaSalvar].nome[strcspn(listaDeProdutos[lugarParaSalvar].nome, "\n")] = 0;
        printf("Digite o preço do produto: ");
        scanf("%f",&listaDeProdutos[lugarParaSalvar].preco);
        printf("Digite a quantidade em estoque: ");
        scanf("%d",&listaDeProdutos[lugarParaSalvar].estoque);
    }
    else{
        printf("\n\nNão há espaço para novos produtos no estoque!\n\n");
    }
}

int procuraPosicaoValidaProduto(struct produtos listaDeProdutos[],int quantidadesDeRegistros){
    for(int i = 0; i < quantidadesDeRegistros; i++){
        if(listaDeProdutos[i].codigo == 0)
            return i;
    }
    return -1;
}

void excluirProduto(struct produtos listaDeProdutos[], int quantidadesDeRegistros){
    printf("\n=-=-=-=-=-=-=-=-=-=-=-= EXCLUIR PRODUTO =-=-=-=-=-=-=-=-=-=-=-\n");
    int posicaoExcluida;
    while (1){
        printf("Digite o código que deseja remover (0 para cancelar operação): ");
        scanf("%d",&posicaoExcluida);
        posicaoExcluida--;
        if(posicaoExcluida == -1)
            break;
        if(posicaoExcluida >= 0 && posicaoExcluida < quantidadesDeRegistros){
            listaDeProdutos[posicaoExcluida].codigo = 0;
            strcpy(listaDeProdutos[posicaoExcluida].nome, "");
            listaDeProdutos[posicaoExcluida].preco = 0;
            listaDeProdutos[posicaoExcluida].estoque = 0;
            char aux[10];
            printf("\nProduto excluido com sucesso!\n\nPrecione ENTER para continuar!");
            setbuf(stdin, 0);
            fgets(aux,9,stdin);
            printf("\n");
            break;
        }
        printf("\nCódigo de produto inválido por favor digite um número entre 1 e %d\n\n", quantidadesDeRegistros); 
    }
}

void editarProduto(struct produtos listaDeProdutos[], int quantidadesDeRegistros){
    printf("\n=-=-=-=-=-=-=-=-=-=-=-=- EDITAR PRODUTO -=-=-=-=-=-=-=-=-=-=-=\n");
    int posicaoExcluida;
    while (1){
        printf("Digite o código que deseja alterar (0 para cancelar operação): ");
        scanf("%d",&posicaoExcluida);
        posicaoExcluida--;
        if(posicaoExcluida == -1)
            break;
        if(posicaoExcluida >= 0 && posicaoExcluida < quantidadesDeRegistros){
            if(listaDeProdutos[posicaoExcluida].codigo == 0){
                printf("\nCódigo de produto não cadastrado\n");
            }
            else{
                printf("Nome -> de %s para: ",listaDeProdutos[posicaoExcluida].nome);
                setbuf(stdin, 0);
                fgets(listaDeProdutos[posicaoExcluida].nome,49,stdin);
                listaDeProdutos[posicaoExcluida].nome[strcspn(listaDeProdutos[posicaoExcluida].nome, "\n")] = 0;
                printf("Preço -> de R$%.2f para: R$",listaDeProdutos[posicaoExcluida].preco);
                scanf("%f",&listaDeProdutos[posicaoExcluida].preco);
                printf("Quantidade em estoque -> de %d para: ",listaDeProdutos[posicaoExcluida].estoque);
                scanf("%d",&listaDeProdutos[posicaoExcluida].estoque);
                printf("\nProduto editado com sucesso!\n");
            }
            char aux[10];
            printf("\nPrecione ENTER para continuar!");
            setbuf(stdin, 0);
            fgets(aux,9,stdin);
            printf("\n");
            break;
        }
        printf("\nCódigo de produto inválido por favor digite um número entre 1 e %d\n\n", quantidadesDeRegistros); 
    }
}

void procurarProduto(struct produtos listaDeProdutos[], int quantidadesDeRegistros){
    printf("\n=-=-=-=-=-=-=-=-=-=-=-= PROCURAR PRODUTO =-=-=-=-=-=-=-=-=-=-=\n");
    int posicaoDeBusca;
    while (1){
        printf("Digite o código que deseja procurar (0 para cancelar operação): ");
        scanf("%d",&posicaoDeBusca);
        posicaoDeBusca--;
        if(posicaoDeBusca == -1)
            break;
        if(posicaoDeBusca >= 0 && posicaoDeBusca < quantidadesDeRegistros){
            if(listaDeProdutos[posicaoDeBusca].codigo == 0){
                printf("\nCódigo de produto não cadastrado\n");
            }
            else{
                printf("Código: %d\n",listaDeProdutos[posicaoDeBusca].codigo);
                printf("Nome: %s\n",listaDeProdutos[posicaoDeBusca].nome);
                printf("Preço: R$%.2f\n",listaDeProdutos[posicaoDeBusca].preco);
                printf("Quantidade em estoque: %d\n",listaDeProdutos[posicaoDeBusca].estoque);
            }
            char aux[10];
            printf("\nPrecione ENTER para continuar!");
            setbuf(stdin, 0);
            fgets(aux,9,stdin);
            printf("\n");
            break;
        }
        printf("\nCódigo de produto inválido por favor digite um número entre 1 e %d\n\n", quantidadesDeRegistros); 
    }
}

void listaVendas(struct vendas listaDeVendas[], int quantidadeDeRegistros){
    printf("\n=-=-=-=-=-=-=-=-=-=-= LISTA DE VENDAS =-=-=-=-=-=-=-=-=-=-=-\n");
    for(int i = 0; i<quantidadeDeRegistros; i++){
        if(listaDeVendas[i].codigo != 0){
            printf("\n-=-=-=-=-==-=-=");
            printf("\nCódigo: %d",listaDeVendas[i].codigo);
            printf("\nCódigo produto: %d",listaDeVendas[i].codigoProduto);
            printf("\nQuantidade: R$%.2f",listaDeVendas[i].quantidade);
            printf("\nData: ");
            dataFormatada(listaDeVendas[i].data);
            printf("\n");
        }
    }
    char aux[10];
    printf("\nPrecione ENTER para continuar!");
    setbuf(stdin, 0);
    fgets(aux,9,stdin);
    printf("\n");
}

int procuraPosicaoValidaVenda(struct vendas listaDeVendas[],int quantidadesDeRegistros){
    for(int i = 0; i < quantidadesDeRegistros; i++){
        if(listaDeVendas[i].codigo == 0)
            return i;
    }
    return -1;
}

void cadastrarVenda(struct vendas listaDeVendas[], struct produtos listaDeProdutos[], int quantidadesDeRegistros){
    printf("\n-=-=-=-=-=-=-=-=-=-=-= CADASTRO DE VENDA =-=-=-=-=-=-=-=-=-=-=\n");
    int codigoProduto = -1;
    int quantidadeEstoque = -1;
    int lugarParaSalvar = procuraPosicaoValidaVenda(listaDeVendas,quantidadesDeRegistros);
    if(lugarParaSalvar != -1){
        while (codigoProduto < 0 || codigoProduto > quantidadesDeRegistros){
            printf("Código do produto que deseja adicionar a venda (0 para cancelar operação): ");
            scanf("%d",&codigoProduto);
            if (codigoProduto == 0)
                return;
            else if(codigoProduto < 0 || codigoProduto > quantidadesDeRegistros)
                printf("\nCódigo do produto fora dos limites de 1 e %d\n\n",quantidadesDeRegistros);
            else if(listaDeProdutos[codigoProduto-1].codigo == 0){
                printf("\nCódigo do produto não cadastrado\n\n");
                codigoProduto = -1;
            }
        }

        //while (listaDeProdutos)
        //{
        //    /* code */
        //}
        
        
        //listaDeVendas[lugarParaSalvar].codigo = lugarParaSalvar + 1;
        //printf("O registro terá como código %d!\n", listaDeVendas[lugarParaSalvar].codigo);
        //printf("Digite o nome do Venda: ");
        //setbuf(stdin, 0);
        //fgets(listaDeVendas[lugarParaSalvar].nome,49,stdin);
        //listaDeVendas[lugarParaSalvar].nome[strcspn(listaDeVendas[lugarParaSalvar].nome, "\n")] = 0;
        //printf("Digite o preço do Venda: ");
        //scanf("%f",&listaDeVendas[lugarParaSalvar].preco);
        //printf("Digite a quantidade em estoque: ");
        //scanf("%d",&listaDeVendas[lugarParaSalvar].estoque);
    }
    else{
        printf("\n\nNão há espaço para novas vendas!\n\n");
    }
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