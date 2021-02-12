#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>

#define MAX_linhas 23040

typedef struct				//estrutura que contem o nome de um proprietario, o seu cc e quantas casas possui(em relacao ao ficheiro lido)
{
	char nome[60+1];
	int ncc;
	int n_casas;
}props;

typedef struct				//estrutura que cntem os dados lidos do ficheiro
{
	int nac;
	int reg;
	int dis;
	int mun;
	int ncc;
	char nome[60+1];
	char morada[60+1];
	int n_porta;
	char cod_pos[8+1];
}dados;

void saida()									//funcao de saida(ultima opcao do menu)
{
	printf("\nAdeus!!!\n\n");
	exit(1);
}

void dados_prop(dados *dds, int i)						//esta funcao imprime os valores guardados na posição i
{
        printf("%d.%d.%d.%d ", dds[i].nac, dds[i].reg, dds[i].dis, dds[i].mun);
        printf("%d ", dds[i].ncc);
        printf("%s ", dds[i].nome);
        printf("%s ", dds[i].morada);
        printf("%d  ", dds[i].n_porta);
        printf("%s\n", dds[i].cod_pos);
}

int total_prop(props *prps)							//esta funcao retorna o numero de proprietarios diferentes que exitem
{
	int i=0;
	for(i=0;prps[i].ncc;i++){
	}
	return i;
}

void verif_nac(dados *dds, int nac)
{
	if(nac>10||nac<1)
	{
		printf("Erro na introdução de dados!!(Nac)\n");          	// verifica se o valor de nacionalidade está correto
		exit (1);
	}
}
void verif_reg(dados *dds, int reg)
{
	if(reg>16||reg<0)
	{
		printf("Erro na introdução de dados!!(Reg)\n");			// verifica se o valor de regional está correto
		exit (1);
	}
}

void verif_dis(dados *dds, int dis)
{
	if(dis>9||dis<0)
	{
		printf("Erro na introdução de dados!!(Dis)\n");			// verifica se o valor de distrital está correto
		exit (1);
	}
}

void verif_mun(dados *dds, int mun)
{
	if(mun>16||mun<0)
	{
		printf("Erro na introdução de dados!!(Mun)\n");			// verifica se o valor de municipal está correto
		exit (1);
	}
}

void guardar_props(int i, dados *dds, props *prps)				//consoante sao guardados os dados do ficheiro lido, esta funcao verifica e guarda na segunda estrutura o nome, cc e n_casas de um proprietario(props)
{
	int j, val=0;

	for(j=0;prps[j].ncc;j++)
	{
		if(prps[j].ncc==dds[i].ncc)
		{
			prps[j].n_casas++;
			val=1;							//se for encotrado algum valor ja guardado, val é alterado evitando criar 2 proprietarios iguais
			break;
		}
	}
	if(val==0)								//se ainda nao existir o proprietario dentro da estrutura, é guardado as suas informaçoes
	{
		prps[j].ncc=dds[i].ncc;
		prps[j].n_casas=1;
		strcpy(prps[j].nome, dds[i].nome);
	}
}

void ler_registo(FILE *fp, dados *dds, int i, props *prps)			//esta funcao le uma linha i do ficheiro e guarda os respetivos dados nas estruturas
{
	int nac, reg, dis, mun, ncc;
	int n_porta=0;

	fscanf(fp,"%d.%d.%d.%d %d %60c %60c %d %8c", &nac, &reg, &dis, &mun, &ncc, dds[i].nome, dds[i].morada, &n_porta, dds[i].cod_pos);

	dds[i].nac = nac;							//atribuição dos valores guardados nas variaveis à posição na estrutura
	dds[i].reg = reg;
	dds[i].dis = dis;
	dds[i].mun = mun;
	dds[i].ncc = ncc;
	dds[i].n_porta = n_porta;

	dds[i].nome[60]='\0';							//colocaçao do caracter terminaçao no fim dos vetores
	dds[i].morada[60]='\0';
	dds[i].cod_pos[8]='\0';
	guardar_props(i, dds, prps);
}

void ler_file(dados *dds, props *prps)
{
	FILE *fp;
	int i=0;
	char ch;
	char nome_fich[50];
	getchar();

	printf("Escreva o nome do ficheiro a abrir(ENTER para base.txt):   ");
	fgets(nome_fich, 50, stdin);

	if(nome_fich[0]=='\n')							//se for introduzido um ENTER( para ler o base.txt) o nome do ficheiro é alterado para base.txt
	{
		strcpy(nome_fich, "base.txt");

	}
	else
	{
		nome_fich[strlen(nome_fich) - 1] = '\0';			//colocaçao do caracter terminaçao no fim do vetor
	}
	fp=fopen(nome_fich, "r");
	if(fp!=NULL)								//se o ficheiro que introduziu nao existir
	{
		do
       		{
	    		ler_registo(fp, dds, i, prps);				//guardar os dados na estrutura
	    		i++;

		}
		while((ch=fgetc(fp)) != EOF);
		printf("O ficheiro %s foi lido com sucesso!\n", nome_fich);
		fclose(fp);
    	}
	else
	{
		printf("Erro ao tentar abrir o ficheiro \"%s\"\nEste ficheiro pode não existir\n", nome_fich);
	}
}

int ler_fich(dados *dds, char nomefich[], props *prps)				//esta funcao le automaticamente o ficheiro caso seja introudzido na linha de comandos
{
	FILE *fp;
	int i=0;
	char ch;

	fp=fopen(nomefich, "r");
	 if(fp!=NULL)
	{
		do
       		{
            		ler_registo(fp, dds, i, prps);
            		i++;

        	}
        	while((ch=fgetc(fp)) != EOF);
		printf("\nA leitura do ficheiro %s foi efetuada com sucesso!!!\n", nomefich);
		fclose(fp);
		return 1;
    	}
	else
	{
		printf("\nA leitura do ficheiro %s não foi efetuada!!!\nEste ficheiro pode não existir!\n", nomefich);
		return 0;
	}
}

void most_prop(dados *dds, props *prps)						//esta funcao imprime o numero de proprietarios diferentes que existem no ficheiro lido
{
	int i;
	char opcao;
	int total;
	total=total_prop(prps);							//atribuição do numero total de casas

	printf("Há %d proprietarios, deseja ver os proprietarios (S/s ou N/n)? ", total);
	scanf(" %c", &opcao);

	if(opcao == 's' || opcao == 'S'||opcao=='n'||opcao=='N')		//caso queira ver ou nao
	{
		if(opcao=='S'||opcao=='s')					//se escolher ver
		{
			for(i=0;prps[i].ncc;i++)
			{
				printf("%d %s\n", prps[i].ncc, prps[i].nome);
			}
		}
	}
	else
	{
		printf("A opcao que introduziu não está correta!\n");		//se introduzir uma opcao errada, volta para o menu
	}
}

void altr_prop(dados *dds, int i, props *prps)
{
	int val=0, sair=1, ncc=0, indice;
	for(int j=0;prps[j].ncc;j++)						//decrementação do numero de casas do proprietario a que foi comprada a casa
	{
		if(prps[j].ncc==dds[i].ncc)
		{
			prps[j].n_casas--;
		}
	}
	printf("Diga nos o seu Número de CC: ");
	while(sair)
	{
		scanf(" %d", &ncc);
		if(ncc>=99999999||ncc<0)					//confirmacao que foi introduzido um valor correto para o cc
		{
			printf("Erro na introdução do Numero de CC, Tente Novamente!  ");
		}
		else
		{
			sair=0;
		}
	}
	dds[i].ncc=ncc;
	printf("Diga nos o seu nome: ");
	scanf(" %60[^\n]c", dds[i].nome);

	size_t length = strlen(dds[i].nome);					//colocação do espaços ate o vetor conter 60 caracteres
	while(length < 60)
	{
		dds[i].nome[length] = ' ';
		length++;
	}
	dds->nome[60]='\0';							//colacação do caracter terminação no fim do vetor
	for(int j=0;prps[j].ncc;j++)
	{
		if(prps[j].ncc==dds[i].ncc)					//caso o proprietario que for comprar a casa ja tenha alguma casa anteriormente, incrementa o numero das suas casas
		{
			prps[j].n_casas++;
			val=1;
		}
	}
	if(val==0)
	{
		indice=total_prop(prps);
		prps[indice].n_casas++;						//caso o proprietario que for comprar a casa seja "novo", guarda os seus dados(que foram introduzidos anteriormente)
		prps[indice].ncc=dds[i].ncc;
		strcpy(prps[indice].nome, dds[i].nome);
	}
}

void compra_venda(dados *dds, props *prps)
{
	int i, nac, reg, dis, mun;

	printf("Que propriedade pretende comprar? \n");

	printf("Existem 23040 propriedades.\nA nivel Nacional(1 a 10): ");
	scanf(" %d", &nac);
	verif_nac(dds, nac);

	printf("Restam-lhe 2304 resultados. A nivel Regional(1 a 16): ");
	scanf(" %d", &reg);
	verif_reg(dds, reg);

	printf("Restam-lhe 144 resultados. A nivel Distrital(1 a 9): ");
	scanf(" %d", &dis);
	verif_dis(dds, dis);

	printf("Restam-lhe 16 resultados. A nivel Munipal(1 a 16): ");
	scanf(" %d", &mun);
	verif_mun(dds, mun);

	for(i=0;i<MAX_linhas;i++)
	{
		if(nac==dds[i].nac)
		{
			if(reg==dds[i].reg)
			{
				if(dis==dds[i].dis)
				{
					if(mun==dds[i].mun)
					{
						dados_prop(dds, i);		//impressao dos dados da propriedade na posiçao i
						altr_prop(dds, i, prps);	//alteraçao dos dados da propriedade na posiçao i
						printf("A propriedade foi comprada com sucesso!\n");
						printf("Os dados atuais para a casa %d.%d.%d.%d sao:  \n", nac, reg, dis, mun);
						dados_prop(dds, i);		//impressao dos dados da propriedade na posiçao i
						break;
					}
				}
			}
		}
	}
}
void guardar_dados(dados *dds)
{
	FILE *fp;
	int i;
	char nome_fich[50];
	__fpurge(stdin);

	printf("Pretende guardar em que ficheiro?  ");				//escolha do ficheirio onde se pretende escrever os dados
	fgets(nome_fich, 50, stdin);
	strtok(nome_fich, "\n");						//esta funcao retira o caracter escolhido

	fp=fopen(nome_fich, "w");
	if(fp==NULL)
	{
		printf("Erro na abertura do ficheiro!\n");
		exit(1);
	}
	for(i=0;i<MAX_linhas;i++)						//escrita no ficheiro
	{
		fprintf(fp,"%d.%d.%d.%d %d %s %s %d %s\n", dds[i].nac, dds[i].reg, dds[i].dis, dds[i].mun, dds[i].ncc, dds[i].nome, dds[i].morada, dds[i].n_porta, dds[i].cod_pos);
	}
	fclose(fp);
	printf("A escrita no ficheiro \"%s\"foi efetuada com sucesso!!\n", nome_fich);
}

void most_reg(dados *dds, int nac)
{
	int inicio;
	int fim;

	fim = (nac*2304)-1;       						 //a nivel regional, quando é escrito "0" é mostrado 2304 propriedades
	if(nac==1)
	{
		inicio = 0;
	}
	else
	{
		inicio = (((nac-1)*2304));
	}
	for(;inicio<=fim; inicio++)
	{
		printf(" %d.%d.%d.%d  ", dds[inicio].nac, dds[inicio].reg, dds[inicio].dis, dds[inicio].mun);
		printf(" %s\n", dds[inicio].nome);
	}
}

void most_dis(dados *dds, int nac, int reg)
{
	int inicio;
	int sub;
	int fim;

	sub = ((nac-1)*2304);
	fim = ((reg*144)-1)+(sub);                				//a nivel distrital, quando é escrito "0" é mostrado 144 propriedades

	if(reg==1)
	{
		inicio = sub;
	}
	else
	{

		inicio = ((reg-1)*144)+(sub);
	}
	for(;inicio<=fim;inicio++)
	{
		printf(" %d.%d.%d.%d  ", dds[inicio].nac, dds[inicio].reg, dds[inicio].dis, dds[inicio].mun);
		printf(" %s\n", dds[inicio].nome);
	}
}

void most_mun(dados *dds, int nac, int reg, int dis)
{
	int inicio;
	int fim;
	int sub;

	sub = ((reg-1)*144) + ((nac-1)*2304);
	fim = ((dis*16)-1) + (sub);						//a nivel municipal, quando é escrito "0" é mostrado 16 propriedades

	if(dis==1)
	{
		inicio =sub;
	}
	else
	{
		inicio = ((dis-1)*16) + (sub);
	}
	for(;inicio<=fim;inicio++)
	{
		printf(" %d.%d.%d.%d  ", dds[inicio].nac, dds[inicio].reg, dds[inicio].dis, dds[inicio].mun);
		printf(" %s\n", dds[inicio].nome);
	}
}

void propriedade(dados *dds, int nac, int reg, int dis, int mun)
{
	int inicio;
	int sub;

	sub = ((dis-1)*16) + ((reg-1)*144) + ((nac-1)*2304);
	if(mun==1)
	{
		inicio = sub;							//apenas uma propriedade é mostrada porque todos os campos de regioes foram preenchidos
	}
	else
	{
		inicio = (mun-1) + sub;
	}
	printf(" %d.%d.%d.%d  ", dds[inicio].nac, dds[inicio].reg, dds[inicio].dis, dds[inicio].mun);
	printf(" %s\n", dds[inicio].nome);
}

void proprietario_reg(dados *dds)
{
	int nac, reg, dis, mun;

	printf("\n\tEscreva a localização geografica:\nNivel Nacional(1 a 10)[23040 resultados]: ");
	scanf(" %d", &nac);
	verif_nac(dds, nac);

	printf("Nivel Regional(0 a 16)[2304 resultados]: ");
	scanf(" %d", &reg);
	verif_reg(dds, reg);
	if(reg==0)								//caso opte por ver um "bloco" nacional
	{
		most_reg(dds, nac);
		return;
	}

	printf("Nivel Distrital(0 a 9)[144 resultados]: ");
	scanf(" %d", &dis);
	verif_dis(dds, dis);
	if(dis==0)								//caso opte por ver um "bloco" regional
	{
		most_dis(dds, nac, reg);
		return;
	}

	printf("Nivel Municipal(0 a 16)[16 resultados]:  ");
	scanf(" %d", &mun);
	verif_mun(dds, mun);
	if(mun==0)								//caso opte por ver um "bloco" distrital
	{
		most_mun(dds, nac, reg, dis);
		return;
	}

	propriedade(dds, nac, reg, dis, mun);					//caso opte por ver uma propriedade
}

void num_prop(props *prps)
{
	int n, i, soma=0;

	printf("Deseja ver os proprietarios que tem quantas casas(1 a 23040)?:  ");
	scanf(" %d", &n);
	if(n>0 && n<23041)							//verificação que o valor foi introduzido corretamente
	{
		for(i=0;prps[i].ncc; i++)
		{
			if(prps[i].n_casas==n)					//impressao de proprietarios que possuem o numero de casas que foi escolhido
				{
					printf(" %d  %s\n", prps[i].ncc, prps[i].nome);
					soma++;
				}
		}
		printf("Existem %d proprietarios com %d propriedades\n", soma, n);
	}
	else
	{
		printf("O valor que introduziu está incorreto!!!\n");
	}
}

int num_casas(int n, props *prps)			//funcao que verifica quandos proprietrios tem n casase retorna esse valor
{
	int i, vezes=0;
	for(i=0;prps[i].ncc;i++)
	{
		if(prps[i].n_casas==n)
		{
			vezes++;
		}
	}
	return vezes;
}

void hist_abs(props *prps)
{
	int n_prop[30];					//vetor que contem o numero de proprietarios por i num de casas (EXEMPLO: n_prop[20]=100, existem 100 proprietarios que contem 20 casas)
	int max=0, i, j;
	double sub_max=0, val_as=0, val_atual=0;
	for(i=0;prps[i].ncc;i++)
	{
		if(prps[i].n_casas>max)
		{
			max=prps[i].n_casas;		//verificaçao do numero de casas que o/s proprietario/s com mais casas tem
		}
	}
	for(i=0;i<=max;i++)
	{
		n_prop[i]=num_casas(i, prps);		//atribuicao a cada indice do vetor(numero de casa que possuem), o numero de proprietarios
	}
	for(j=2;j<=max;j++)
	{
		if(n_prop[j]>sub_max)
		{
			sub_max=n_prop[j];		//verificaçao do numero de proprietarios maximo que possuem o mesmo numero de casas(sem contar com 1 e 0, pedido no enunciado)
		}
	}
	val_as=(sub_max/40);				//consoante o valor maximo verificado na atriubiçao a cima, é calculado o valor de cada asterisco sabendo que para este valor(sub_max), no histograma tera de conter 40 *
	printf("Propriedades\tNumero\n");
	printf("%d\t\t%d\n", 1, n_prop[1]);
	for(i=2;i<=max;i++)
	{
		if(n_prop[i]!=0)
		{
			printf("%d\t\t%d\t: ",i, n_prop[i]);
			for(val_atual=0;val_atual<n_prop[i];val_atual+=val_as)
			{
				printf("*");		//é introduzido * consoante o numero de proprietarios que possuem i casas e o numero de * que ja foram impressos (sabendo anteriromente quanto vale cada unidade de *)
			}
			printf("\n");
		}
	}
}
void hist_rel(props *prps)
{
	int n_prop[30];					//vetor que contem o numero de proprietarios por i num de casas (EXEMPLO: n_prop[20]=100, existem 100 proprietarios que contem 20 casas)
	int max=0, i, j, sem_casa=0;
	double sub_max=0, val_as=0, val_atual=0, percentagem=0;
	for(i=0;prps[i].ncc;i++)
	{
		if(prps[i].n_casas>max)
		{
			max=prps[i].n_casas;		//verificaçao do numero de casas que o/s proprietario/s com mais casas tem
		}
	}
	for(i=0;i<=max;i++)
	{
		n_prop[i]=num_casas(i, prps);		//atribuicao a cada indice do vetor(numero de casa que possuem), o numero de proprietarios
	}
	for(j=2;j<=max;j++)
	{
		if(n_prop[j]>sub_max)
		{
			sub_max=n_prop[j];		//verificaçao do numero de proprietarios maximo que possuem o mesmo numero de casas(sem contar com 1 e 0, pedido no enunciado)
		}
	}
	val_as=(sub_max/40);				//consoante o valor maximo verificado na atriubiçao a cima, é calculado o valor de cada asterisco sabendo que para este valor(sub_max), no histograma tera de conter 40 *
	printf("\n%d\n", n_prop[1]);
	printf("Propriedades\tPerecentagem\n");
	for(i=max;i>=2;i--)
	{
		percentagem=(((float)n_prop[i])/50200)*100;	//calculo da percentagem de proprietarios que contem i casas sabendo que a populçao total é 50200
		if(n_prop[i]!=0)
		{
			printf("%d\t\t%.3f%%\t: ",i, percentagem);
			for(val_atual=0;val_atual<n_prop[i];val_atual+=val_as)
			{
				printf("*");		//é introduzido * consoante o numero de proprietarios que possuem i casas e o numero de * que ja foram impressos (sabendo anteriromente quanto vale cada unidade de *)
			}
			printf("\n");
		}

	}
	printf("%d\t\t%.3f%%\n", 1, (((float)n_prop[1]/50200)*100));		//percentagem de proprietarios com 1 casas(impressao)
	sem_casa=50200-(total_prop(prps));					//numero de proprietarios sem casas
	printf("%d\t\t%.3f%%\n", 0, (((float)sem_casa/50200)*100));		//percentagem de proprietarios com 0 casas(impressao)
}

void n_donos_c_mais(props *prps)
{
	int n_max, x=0, i, n, val=0, max_casas=0;

	for(i=0;prps[i].ncc;i++)
	{
		if(prps[i].n_casas>max_casas)
		{
			max_casas=prps[i].n_casas;				//verificaçao do numero de casas que o proprietario com mais casas tem
		}
	}
	printf("Deseja ver quantos proprietarios com mais casas? ");
	scanf(" %d", &n_max);
	for(n=max_casas;n>0;n--)						//n varia consoante o numero maximo de casas que um proprietario possui e é descrescente(para imprimir por exemplo primeiro os proprietarios+
	{									//+que contem 20 casas, depois 19, depois 18 etc...(ate ser atingido o numero escolhido de proprietarios impressos)
		for(i=0;prps[i].ncc;i++)
		{
			if(!i)							//no inicio de cada "bloco" de proprietarios com mais casas, é confirmado se o numero de proprietarios impressos é >= ao que foi pedido
			{
				if(x>=n_max)
				{	val=1;					//caso seja, nao imprime o "bloco" e termina
					break;
				}
			}
			if(prps[i].n_casas==n)					//se nao for, continua a imprimir ate ao fim do "bloco"
			{
				printf("%d   \t%s\t\t%d\n", prps[i].ncc, prps[i].nome, prps[i].n_casas);
				x++;						//incrementacao do numero de proprietarios impressos
			}
		}
		if(val==1)
		{
			break;
		}
	}
	printf("imprimiu %d proprietarios!\n", x);				//verificaçao de quantos proprietarios foram impressos
}
void menu(dados *dds, props *prps)
{
	char opcao;

	while(1)
	{
		//printf("\033[1;36m");(cores)
		printf("\n\t\tGestão de Propriedade Prediais\n\n");
		printf("\t0 - Sair do programa.\n");
		printf("\t1 - Ler ficheiro\n");
		printf("\t2 - Listar proprietários.\n");
		printf("\t3 - Compra e Venda de propriedades.\n");
		printf("\t4 - Escrita em um ficheiro.\n");
		printf("\t5 - Listar proprietário de uma região.\n");
		printf("\t6 - Escrita de proprietários por número de propriedades.\n");
		printf("\t7 - Histograma absoluto.\n");
		printf("\t8 - Histograma relativo.\n");
		printf("\t9 - Identificação das n pessoas com mais propriedades.\n\n");
		printf("O que pretende fazer? ");
		//printf("\033[0m");(cores)
		scanf(" %c", &opcao);

		switch(opcao)
		{
			case '1' : ler_file(dds, prps); break;
			case '2' : most_prop(dds, prps); break;
			case '3' : compra_venda(dds, prps); break;
			case '4' : guardar_dados(dds); break;
			case '5' : proprietario_reg(dds); break;
			case '6' : num_prop(prps); break;
			case '7' : hist_abs(prps); break;
			case '8' : hist_rel(prps); break;
			case '9' : n_donos_c_mais(prps); break;
			case '0' : saida(); break;
			default : printf("\nEscreveu um caracter ou um numero que não está entre 0 e 9. Tente novamente.\n");
		}
	}
}

int main(int argc, char *argv[])
{
	static dados dd[MAX_linhas]={0};		//incialização do vetor de estruturas onde vai ser guardado os dados do ficheiro
	dados *dds;					//inicialização de um apontador do mesmo tipo que a estrutura anterior
	dds=dd;

	static props pp[7000]={0};			//inicialização do vetor de estruturas onde vai se guardado os dados de cada proprietario
	props *prps;					//inicialização de um apontador do mesmo tipo que a estrutura anterior
	prps=pp;

    if(argc==2)						//caso se verifique que foi introduzido algo na linha de comandos
    {
        if(!strcmp(argv[1], "-h"))			//caso tenha sido -h impressao do pedido de ajdua
        {
            printf("\n\n\tUso: %s [ficheiro_de_registo]\n\t\tO ficheiro_de_registos contem TODAS as propriedades do país\n\n\t\tversao1\n\n", argv[0]);
	    exit(1);
        }
	if(!ler_fich(dds, argv[1], prps))		//caso tenha sido escrita outra coisa para alem de -h, é feita uma tentativa de abrir o ficheiro introduzido
	{
		printf("O ficheiro %s não foi aberto!!!\n", argv[1]);
		exit(1);
	}
	else
	{
		printf("O ficheiro %s foi aberto corretamente!!!\n", argv[1]);
	}
    }
	menu(dds, prps);				//menu onde contem todas as possiveis opcoes
}
