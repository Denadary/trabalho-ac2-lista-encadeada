#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#define maxopcoes 9
#define MAXNOME 60

typedef struct nota {
	short notalancadaav1, notalancadaav2, notalancadaavf;
	char disc[3];
	float nota[3];
	struct nota *proximo;
} notas;

typedef struct aluno {
	int mat;
	char nome[MAXNOME];
    struct aluno *proximo;
	struct aluno *anterior;
	struct nota *primeiro;
} alunos;

typedef struct header {
	int quant_nos;
	int menor;
	int maior;
	struct aluno *proximo;
	struct aluno *anterior;
} cabeca;
int looppergunta(int a,int b)
{
    while(a<0 || a > b)
        {
            printf("\nopcao invalida, insira um numero entre 0 e %i",b);
            scanf("%d",&a);
        }
    return a;
}
alunos* varrerlista(int matricula, int meio,cabeca* head,alunos* cabecao, alunos* tail)//retorna null se não econtrar a matricula desejada ou a matricula
{
    alunos* atual;
    alunos* novo;
    alunos* prev;

    if(matricula<=meio)
    {
        atual=cabecao->proximo;
        //printf("\nprimeiro da lista = %i",atual->mat);
        while(atual->mat!=matricula)
        {
            if(atual->mat==tail->mat)
            {
                 printf("\nmatricula não encontrada/disponivel");
                return atual=NULL;
            }
            atual=atual->proximo;
        }
    }
    else
    {
        atual=tail->anterior;
        //printf("\nultimo da lista = %i",atual->mat);
        while(atual->mat!=matricula)
        {
            if(atual->mat==cabecao->mat)
            {
            printf("\nmatricula não encontrada/disponivel");
            return atual=NULL ;
            }
            atual=atual->anterior;
        }

    }
    return atual;
}
short exibirdisciplinas(notas* primeiro,int teste)//devolve 1 se não ha disciplinas
{
    short nulo=0;
    notas* atual;
    atual=primeiro->proximo;

    if(atual==NULL)
    {
        return nulo=1;
    }
    if(teste)
    {
        do  {
        printf("%s\t\t%.2f\t%.2f\t%.2f\n",atual->disc,atual->nota[0],atual->nota[1],atual->nota[2]);
        atual=atual->proximo;
        //i++;
        }
        while(atual!=NULL);
        return nulo;
    }
    else// se teste=0, só imprime o nome das disciplinas
    {
        do  {
        printf("%s\n",atual->disc);
        atual=atual->proximo;
        //i++;
        }
        while(atual!=NULL);
        return nulo;
    }
}

short fexibirdisciplinas(FILE* pflista,notas* primeiro)//devolve 1 se não ha disciplinas
{
    short nulo=0;
    notas* atual;
    //int i=1;
    atual=primeiro->proximo;
    /*while(atual->proximo!=NULL)
    {
        printf("\n%i-\t%s\t%.2f\t%.2f\t%.2f",i,atual->disc,atual->nota[0],atual->nota[1],atual->nota[2]);
        atual=atual->proximo;
        i++;
    }*/
    //printf("\n");
    if(atual==NULL)
    {
        return nulo=1;
    }
    do  {
        fprintf(pflista,"%s\t\t%.2f\t%.2f\t%.2f\n",atual->disc,atual->nota[0],atual->nota[1],atual->nota[2]);
        atual=atual->proximo;
        //i++;
        }
        while(atual!=NULL);
    return nulo;
}

notas* procurardisciplina(notas* procura,notas* head)//retorna ponteiro para a disciplina ou nulo
{
    notas* atual;
    atual=head;

    //printf("\ndisciplina a procurar = %s",procura->disc);

    while(atual!=NULL)
    {
        //printf("\n%s",atual->disc);
        if(strcmp(atual->disc,procura->disc)==0)
        {
            break;
        }
        else
        {
            atual=atual->proximo;
        }
    }
    return atual;
}
void adddisciplina(notas* head,notas* novo )
{
    notas* atual;
    atual=head;
    while(atual->proximo!=NULL)
    {
        atual=atual->proximo;
    }
    atual->proximo=novo;
    novo->proximo=NULL;
    novo->notalancadaav1=novo->notalancadaav2=novo->notalancadaavf=0;
    //printf("\n%s\t%.2f\t%.2f\t%.2f",atual->disc,atual->nota[0],atual->nota[1],atual->nota[2]);
}

void adddiscaluno(notas* headdoaluno,notas* headnotamain)
{
    char materia[3];
    int escolha;
    notas* atual;
    notas* atual2;
    notas* novo;
    notas* resposta;

    atual2=headdoaluno;
    atual2=headdoaluno->proximo;
    printf("\ndisciplinas ligadas ao aluno:\n");
    if(atual2==NULL)
    {
        printf("Nao ha disciplinas ligadas ao aluno");
    }
    else
    {
        do{
        printf("%s",atual2->disc);
        atual2=atual2->proximo;
        }
        while(atual2!=NULL);
    }
    printf("\n\nDisciplinas cadastradas no sistema:\n");
    exibirdisciplinas(headnotamain,0);

    printf("\nDigite a materia:\t");
    scanf(" %[^\n]s%*c", materia);
    novo=malloc(sizeof(notas));
    resposta=malloc(sizeof(notas));
    strcpy(novo->disc,materia);
    resposta=procurardisciplina(novo,headdoaluno);
    if(resposta==NULL)//disciplina não vinculada ao aluno
    {
        printf("\nDisciplina não vinculada ao aluno. Deseja incluir disciplina?(1-S/0-N)");
        scanf("%d",&escolha);
        escolha=looppergunta(escolha,1);
        if(escolha==1)//quer adicionar
        {
            //printf("\nescolhido SIM");
            //strcpy(novo->disc,materia);
            resposta=procurardisciplina(novo,headnotamain);//existe a disciplina na lista principal?
            if(resposta==NULL)//não. incluir na lista principal
            {
                strcpy(novo->disc,materia);
                //printf("\ndisciplina nao encontrada na lista principal");
                adddisciplina(headnotamain,novo);//inclui na lista principal
                adddisciplina(headdoaluno,novo);//inclui na lista do aluno;
                printf("\nDisciplina incluida com sucesso");
            }
            else//já existe na lista principal. incluir na lista do aluno;
            {
                //printf("\ndisciplina encontrada na lista principal");
                adddisciplina(headdoaluno,novo);//inclui na lista do aluno;
                printf("\nDisciplina incluida com sucesso");
            }
        }
        else//não quer adicionar
        {
            //printf("\nEscolhido NAO");
            printf("\nNova disciplina nao adicionada");
        }
    }
    else//disciplina já vinculada ao aluno
    {
        printf("\nDisciplina ja vinculada ao aluno");
    }
}
void removerdisciplina(notas* headdoaluno)
{
    char materia[3];
    notas* atual;
    notas* novo;
    notas* anterior;

    novo=malloc(sizeof(notas));
    printf("\nDigite a disciplina a ser removida");
    scanf(" %[^\n]s%*c", materia);
    strcpy(novo->disc,materia);
    novo=procurardisciplina(novo,headdoaluno);
    if(novo->disc!=NULL)//disciplina encontrada
    {
        anterior=headdoaluno;
        atual=anterior->proximo;
        while(atual!=novo)
        {
            anterior=atual;
            atual=anterior->proximo;
        }
        anterior->proximo=atual->proximo;
        free(atual);
        printf("\ndisciplina %s removida com sucesso",materia);
    }
    else//disciplina nao encontrada
    {
        printf("\ndisciplina nao encontrada");
    }
}
notas* iniciadisciplinas(notas* headnotas)
{
    notas* novo;
    notas* mat;
    notas* hist;
    notas* geo;
    notas* fis;
    notas* qui;
    notas* bio;
    notas* ing;
    int i;

    novo=malloc(sizeof(notas));
    novo->disc[0]='P';
    novo->disc[1]='O';
    novo->disc[2]='R';
    for(i=0;i<3;i++)
    {
        novo->nota[i]=0;
    }
    adddisciplina(headnotas,novo);

    mat=malloc(sizeof(notas));
    mat->disc[0]='M';
    mat->disc[1]='A';
    mat->disc[2]='T';
    for(i=0;i<3;i++)
    {
        mat->nota[i]=0;
    }
    adddisciplina(headnotas,mat);

    hist=malloc(sizeof(notas));
    hist->disc[0]='H';
    hist->disc[1]='I';
    hist->disc[2]='S';
    for(i=0;i<3;i++)
    {
        hist->nota[i]=0;
    }
    adddisciplina(headnotas,hist);

    geo=malloc(sizeof(notas));
    geo->disc[0]='G';
    geo->disc[1]='E';
    geo->disc[2]='O';
    for(i=0;i<3;i++)
    {
        geo->nota[i]=0;
    }
    adddisciplina(headnotas,geo);

    fis=malloc(sizeof(notas));
    fis->disc[0]='F';
    fis->disc[1]='I';
    fis->disc[2]='S';
    for(i=0;i<3;i++)
    {
        fis->nota[i]=0;
    }
    adddisciplina(headnotas,fis);

    qui=malloc(sizeof(notas));
    qui->disc[0]='Q';
    qui->disc[1]='U';
    qui->disc[2]='I';
    for(i=0;i<3;i++)
    {
        qui->nota[i]=0;
    }
    adddisciplina(headnotas,qui);

    bio=malloc(sizeof(notas));
    bio->disc[0]='B';
    bio->disc[1]='I';
    bio->disc[2]='O';
    for(i=0;i<3;i++)
    {
        bio->nota[i]=0;
    }
    adddisciplina(headnotas,bio);

    ing=malloc(sizeof(notas));
    ing->disc[0]='I';
    ing->disc[1]='N';
    ing->disc[2]='G';
    for(i=0;i<3;i++)
    {
        bio->nota[i]=0;
    }
    adddisciplina(headnotas,ing);

    return headnotas;
}

cabeca* inseriraluno(cabeca* head,alunos* cabecao,alunos* tail,int mat)
{
    alunos* atual;
    alunos* novo;
    alunos* prev;
    alunos* teste;
    notas* headdoaluno;
    int /*matricula,*/meio;

    meio=(head->maior+head->menor)/2;

    novo=malloc(sizeof(alunos));
    printf("\ninsira o nome:\t");
    scanf(" %[^\n]s%*c", novo->nome);
    if(mat==0){
    printf("\ninsira a matricula:\t");
    scanf("%d",&mat/*ricula*/);}
    teste=varrerlista(mat/*ricula,*/,meio,head,cabecao,tail);
    if(teste==NULL)
    {novo->mat=mat/*ricula*/;

        atual=cabecao;
        while(novo->mat > atual->mat)
        {
            atual=atual->proximo;
        }
    //alocacao do novo aluno em ordem de matricula:
    prev=atual->anterior;
    prev->proximo=novo;
    atual->anterior=novo;
    novo->proximo=atual;
    novo->anterior=prev;
    //o ponteiro primeiro:
    headdoaluno=malloc(sizeof(notas));
    headdoaluno->proximo=NULL;
    headdoaluno->disc[0]='A';
    headdoaluno->disc[1]='A';
    headdoaluno->disc[2]='A';
    headdoaluno->notalancadaav1=headdoaluno->notalancadaav2=headdoaluno->notalancadaavf=0;
    novo->primeiro=headdoaluno;
    //informações no header:
    if(head->quant_nos==0)//nenhum item na lista
    {
        head->maior=head->menor=novo->mat;
    }
    head->quant_nos++;
    if(novo->mat < head->menor)
    {
        head->menor=novo->mat;
    }
    if(novo->mat > head->maior)
    {
        head->maior=novo->mat;
    }
    printf("\nnovo item inserido");
    return head;
    }
    else
    {
        printf("\nMatricula já existente. Cadastre o Aluno com outra matricula");
        return head;
    }

}
void removeraluno(cabeca* head,alunos* cabecao,alunos* tail)
{
    int x,matricula;
    alunos* atual;
    alunos* novo;
    alunos* prev;

    x=(head->maior+head->menor)/2;
    printf("\ninsira a matricula:\t");
    scanf("%i",&matricula);
    atual=varrerlista(matricula,x,head,cabecao,tail);
    if(atual!=NULL){
            prev=atual->anterior;
            novo=atual->proximo;//usarei o ponteiro novo nessa funcao para ao prximo do atual, o atual será excluido.
            prev->proximo=novo;
            novo->anterior=prev;
            //ainda preciso excluir aqui as disciplinas e notas ligadas pelo ponteiro primeiro;
            if(matricula==head->menor)
            {
                head->menor=novo->mat;
            }
            if(matricula==head->maior)
            {
                head->maior=prev->mat;
            }
            head->quant_nos--;
            free(atual);
            printf("\nMatricula %i excluida com sucesso",matricula);
    }
    else
    {
        return;
    }
}
void inserirnotas(alunos* headdoaluno,notas* headprincipal)
{
    float nota;
    char materia[3];
    int escolha,escolha2,escolha3;
    notas* headnota1;
    notas* headnota;
    notas* novo;
    notas* resposta;
    notas* resposta2;
    notas* atual;
    headnota1=headdoaluno->primeiro;//AAA
    headnota=headnota1->proximo;//AAA->proximo
    printf("\nOpcoes");
    printf("\n1- lancar nota de AV1");
    printf("\n2- lancar nota de AV2");
    printf("\n3- lancar nota de AVF\nDigite sua opcao:\t");
    scanf("%d",&escolha);
    escolha=looppergunta(escolha,3);
    printf("\nInsira a nota do aluno:\t");
    scanf("%f",&nota);
    //a aluno já tem disciplinas cadastradas?
    if(headnota!=NULL)// se sim:
    {
        printf("\ndisciplinas existentes");
        do{
        printf("\n%s",headnota->disc);
        headnota=headnota->proximo;}
        while(headnota!=NULL);

        printf("\ndigite a disciplina:\t");
    scanf(" %[^\n]s%*c", materia);
    novo=malloc(sizeof(notas));
    strcpy(novo->disc,materia);
    resposta2=procurardisciplina(novo,headdoaluno->primeiro);
    if(resposta2==NULL)//disciplina não encontrada
    {
        printf("\ndisciplina nao encontrada. Deseja vincular disciplina ao aluno?(1-S/0-N");
        scanf("%d",&escolha2);
        escolha2=looppergunta(escolha2,1);
        if(escolha2==0)
        {
            printf("\nNenhuma nota foi cadastrada");
            return;
        }
        else
        {
            resposta=procurardisciplina(novo,headprincipal);//existe a disciplina na lista principal?
            if(resposta==NULL)//não. incluir na lista principal
            {
                adddisciplina(headprincipal,novo);//inclui na lista principal
                adddisciplina(headnota1,novo);//inclui na lista do aluno;
                printf("\nDisciplina incluida com sucesso");
            }
            else//já existe na lista principal. incluir na lista do aluno;
            {
                adddisciplina(headnota1,novo);//inclui na lista do aluno;
                printf("\nDisciplina incluida com sucesso");
            }

            //continua aqui:
            atual=headnota1;
            while(atual->proximo!=NULL)
            {atual=atual->proximo;}
        if(escolha==1)//se quer adicionar nota na av1
        {
        if(atual->notalancadaav1==1)
            {
                printf("A nota já foi lancada. Para alterar a nota, favor usar a opcao 6 do menu inicial");
            }
        else
            {
                atual->nota[0]=nota;//lança nota em av1
                atual->notalancadaav1=1;
                printf("\nNota lancada com sucesso");
            }

        }
        if(escolha==2)//se quer adicionar nota na av2
        {
            if(atual->notalancadaav2==1)
            {
                printf("A nota já foi lancada. Para alterar a nota, favor usar a opcao 6 do menu inicial");
            }
            else
            {
                atual->nota[1]=nota;//lança nota em av2
                atual->notalancadaav2=1;
                printf("\nNota lancada com sucesso");
            }

        }
        if(escolha==3)//se quer adicionar nota na av3
        {
            if(atual->notalancadaavf==1)
            {
                printf("A nota já foi lancada. Para alterar a nota, favor usar a opcao 6 do menu inicial");
            }
            else
            {
                atual->nota[2]=nota;//lança nota em avf
                atual->notalancadaavf=1;
                printf("\nNota lancada com sucesso");
            }

        }
        return;
        }
    }
    else//essa disciplina ja existe na lista do aluno
    {
        if(escolha==1)//se quer adicionar nota na av1
        {
        if(novo->notalancadaav1==1)
            {
                printf("A nota já foi lancada. Para alterar a nota, favor usar a opcao 6 do menu inicial");
            }
        else
            {
                novo->nota[0]=nota;//lança nota em av1
                novo->notalancadaav1=1;
                printf("\nNota lancada com sucesso");
            }

        }
        if(escolha==2)//se quer adicionar nota na av2
        {
            if(novo->notalancadaav2==1)
            {
                printf("A nota já foi lancada. Para alterar a nota, favor usar a opcao 6 do menu inicial");
            }
            else
            {
                novo->nota[1]=nota;//lança nota em av2
                novo->notalancadaav2=1;
                printf("\nNota lancada com sucesso");
            }

        }
        if(escolha==3)//se quer adicionar nota na av3
        {
            if(novo->notalancadaavf==1)
            {
                printf("A nota já foi lancada. Para alterar a nota, favor usar a opcao 6 do menu inicial");
            }
            else
            {
                novo->nota[2]=nota;//lança nota em avf
                novo->notalancadaavf=1;
                printf("\nNota lancada com sucesso");
            }

        }
        return;
    }

    }
    else// se não
    {
        printf("\nNao ha disciplinas cadastradas para o aluno. Deseja cadastrar uma disciplina?(1-S/0-N)");
        scanf("%d",&escolha2);
        escolha2=looppergunta(escolha2,1);
        if(escolha2==0)
        {
            printf("\nNenhuma nota foi cadastrada");
            return;
        }
        else
        {
            ///////////////////////////////////
            printf("\disciplinas cadastradas no sistema:\n");
            exibirdisciplinas(headprincipal,0);
            novo=malloc(sizeof(notas));
            printf("\ndigite a disciplina");
            scanf(" %[^\n]s%*c", materia);
            strcpy(novo->disc,materia);
            resposta=procurardisciplina(novo,headprincipal);//existe a disciplina na lista principal?
            if(resposta==NULL)//não. incluir na lista principal
            {
                //strcpy(novo->disc,materia);
                //printf("\ndisciplina nao encontrada na lista principal");
                adddisciplina(headprincipal,novo);//inclui na lista principal
                adddisciplina(headnota1,novo);//inclui na lista do aluno;
                printf("\nDisciplina incluida com sucesso");
            }
            else//já existe na lista principal. incluir na lista do aluno;
            {
                //printf("\ndisciplina encontrada na lista principal");
                adddisciplina(headnota1,novo);//inclui na lista do aluno;
                printf("\nDisciplina incluida com sucesso");
            }

            //continua aqui:
        if(escolha==1)//se quer adicionar nota na av1
        {
        if(novo->notalancadaav1==1)
            {
                printf("A nota já foi lancada. Para alterar a nota, favor usar a opcao 6 do menu inicial");
            }
        else
            {
                novo->nota[0]=nota;//lança nota em av1
                novo->notalancadaav1=1;
                printf("\nNota lancada com sucesso");
            }

        }
        if(escolha==2)
        {
            if(novo->notalancadaav2==1)
            {
                printf("A nota já foi lancada. Para alterar a nota, favor usar a opcao 6 do menu inicial");
            }
            else
            {
                novo->nota[1]=nota;//lança nota em av2
                novo->notalancadaav2=1;
                printf("\nNota lancada com sucesso");
            }

        }
        if(escolha==3)
        {
            if(novo->notalancadaavf==1)
            {
                printf("A nota já foi lancada. Para alterar a nota, favor usar a opcao 6 do menu inicial");
            }
            else
            {
                novo->nota[2]=nota;//lança nota em avf
                novo->notalancadaavf=1;
                printf("\nNota lancada com sucesso");
            }

        }

        }
    return;
    }
}
void alterarnotas(alunos* headdoaluno)
{
    float nota;
    char materia[3];
    char av1[]="AV1";
    char av2[]="AV2";
    char avf[]="AVF";
    int i;
    int escolha,escolha2;
    notas* headnota;
    notas* novo;
    headnota=headdoaluno->primeiro;
    headnota=headnota->proximo;

    exibirdisciplinas(headdoaluno->primeiro,1);

    printf("Opcoes");
    printf("\n1- alterar nota de AV1");
    printf("\n2- alterar nota de AV2");
    printf("\n3- alterar nota de AVF");
    scanf("%d",&escolha);
    escolha=looppergunta(escolha,3);
    printf("\ndigite a disciplina");
    scanf(" %[^\n]s%*c", materia);
    novo=malloc(sizeof(notas));
    strcpy(novo->disc,materia);
    novo=procurardisciplina(novo,headdoaluno->primeiro);
    while(novo==NULL)
    {
        printf("\nDisciplina nao encontrada");
        printf("\ndigite a disciplina");
        scanf(" %[^\n]s%*c", materia);
        strcpy(novo->disc,materia);
        novo=procurardisciplina(novo,headdoaluno->primeiro);
    }

    printf("\nInsira a nova nota do aluno");
    scanf("%f",&nota);

        if(escolha==1)
        {
            printf("\nA nota %.2f sera modificada para %.2f.Confirma alteracao?(1-S/0-N)",novo->nota[0],nota);
            scanf("%d",&escolha2);
            escolha2=looppergunta(escolha2,1);
            if(escolha2==1)
            {
                novo->nota[0]=nota;//lança nota em av1
            }
            else
            {
                printf("\nAleracao cancelada. Nota nao foi alterada");
            }

        }
        if(escolha==2)
        {
            printf("\nA nota %.2f sera modificada para %.2f.Confirma alteracao?(1-S/0-N)",novo->nota[1],nota);
            scanf("%d",&escolha2);
            escolha2=looppergunta(escolha2,1);
            if(escolha2==1)
            novo->nota[1]=nota;//lança nota em av2
            else
            {
                printf("\nAleracao cancelada. Nota nao foi alterada");
            }
        }
        if(escolha==3)
        {
            printf("\nA nota %.2f sera modificada para %.2f.Confirma alteracao?(1-S/0-N)",novo->nota[2],nota);
            scanf("%d",&escolha2);
            escolha2=looppergunta(escolha2,1);
            if(escolha2==1)
            novo->nota[2]=nota;//lança nota em avf
            else
            {
                printf("\nAleracao cancelada. Nota nao foi alterada");
            }
        }
        printf("\nNota lancada com sucesso");

}
void imprimirtudo(cabeca* head,alunos* cabecao,alunos* tail)
{
    alunos* alunoatual;
    notas* notaatual;
    short nulo;

    alunoatual=cabecao->proximo;
    notaatual=alunoatual->primeiro;
    //notaatual=notaatual->proximo;


    while(alunoatual!=tail)
    {
        printf("=====================================");
        printf("\nmatricula\tnome\n");
        printf("%i\t\t%s\n",alunoatual->mat,alunoatual->nome);//matricula e nome
        printf("disciplinas\tAV1\tAV2\tAVF\n");//cabecalho
        /*if(notaatual!=NULL)
        {*/nulo=exibirdisciplinas(notaatual,1);/*}*/
        if(nulo==1)
        {
            printf("\nNao ha disciplinas cadastradas para o aluno\n");
        }
        /*else
        {
            printf("\nNao ha disciplinas cadastradas para o aluno");
        }*/
        alunoatual=alunoatual->proximo;
        notaatual=alunoatual->primeiro;
    }
}
void fimprimirtudo(FILE* pflista,cabeca* head,alunos* cabecao,alunos* tail)
{
    alunos* alunoatual;
    notas* notaatual;
    short nulo;

    alunoatual=cabecao->proximo;
    notaatual=alunoatual->primeiro;

    while(alunoatual!=tail)
    {
        fprintf(pflista,"=====================================");
        fprintf(pflista,"\nmatricula\tnome\n");
        fprintf(pflista,"%i\t\t%s\n",alunoatual->mat,alunoatual->nome);//matricula e nome
        fprintf(pflista,"disciplinas\tAV1\tAV2\tAVF\n");//cabecalho
        /*if(notaatual!=NULL)
        {*/nulo=fexibirdisciplinas(pflista,notaatual);/*}*/
        if(nulo==1)
        {
            fprintf(pflista,"\nNao ha disciplinas cadastradas para o aluno\n");
        }

        alunoatual=alunoatual->proximo;
        notaatual=alunoatual->primeiro;
    }
}
void exibirinfohead(cabeca* head)
{
    printf("\n");
    printf("quant nos = %d\n",head->quant_nos);
    printf("maior = %d\n",head->maior);
    printf("menor = %d\n",head->menor);
}
