#include "funcoeslista.c"

int main ()
{
    int teste,matricula,meio,escolha=9;
    cabeca* head;
    alunos* cabecao;
    alunos* tail;
    alunos* found;
    notas* atual2;
    notas* headnotas;
    char materia[3];
    FILE* pflista;
    char cflista[]="cflista.txt";

    tail=(alunos*)malloc(sizeof(alunos));
    cabecao=(alunos*)malloc(sizeof(alunos));
    cabecao->mat=0;
    cabecao->anterior=tail;
    cabecao->proximo=tail;

    tail->mat=999999;
    tail->anterior=cabecao;
    tail->proximo=cabecao;
    ///////////////////////////////////////////////
    head=malloc(sizeof(cabeca));
    head->menor=0;
    head->maior=99999;
    head->proximo=cabecao;
    head->anterior=tail;
    head->quant_nos=0;

    headnotas=malloc(sizeof(notas));
    headnotas->disc[0]='A';
    headnotas->disc[1]='A';
    headnotas->disc[2]='A';
    headnotas->proximo=NULL;

    headnotas=iniciadisciplinas(headnotas);
    //exibirdisciplinas(headnotas);
    while(escolha)
    {
        printf("\n--------OPCOES----------\n");
        printf("\n1 - inserir aluno\n2 - remover aluno");
        printf("\n3 - inserir disciplina\n4 - remover disciplina");
        printf("\n5 - inserir notas\n6 - alterar notas\n7 - exibir notas do aluno");
        printf("\n8 - imprimir\n9 - exibir info head\n0 - encerrar\n");
        scanf("%d",&escolha);
        while(escolha<0 || escolha > maxopcoes)
        {
            printf("\nopcao invalida, insira um numero entre 0 e %i",maxopcoes);
            scanf("%d",&escolha);
        }

        if(escolha==1)
        {
            teste=head->quant_nos;
            while(teste==head->quant_nos)
            {
                head=inseriraluno(head,cabecao,tail,0);
            }

        }
        if(escolha==2)
        {
            removeraluno(head,cabecao,tail);
        }
        if(escolha==3)
        {
            teste=7;
            printf("\nDigite a matricula do aluno: ");
            scanf("%d",&matricula);
            meio=(head->maior+head->menor)/2;
            found=varrerlista(matricula,meio,head,cabecao,tail);
            while(found==NULL)//matricula nao encontrada na lista
            {
                printf(". Deseja incluir novo aluno com essa matricula?(1-S/0-N)");
                scanf("%d",&teste);
                teste=looppergunta(teste,1);
                if(teste==0)
                {
                    printf("\nNenhuma disciplina foi incluida");
                    teste=-1;//Jumper
                    break;
                }
                else
                {
                    teste=head->quant_nos;
                    while(teste==head->quant_nos)
                    {
                        head=inseriraluno(head,cabecao,tail,matricula);

                    }
                    found=varrerlista(matricula,meio,head,cabecao,tail);
                }
            }
            if(teste!=-1)//Jumper
            {
                printf("\nnome do aluno: %s",found->nome);
                //printf("\ndisciplinas existentes");
                //exibirdisciplinas(headnotas);
                adddiscaluno(found->primeiro,headnotas);
            }

        }
        if(escolha==4)
        {
            printf("\nDigite a matricula do aluno");
            scanf("%d",&matricula);
            meio=(head->maior+head->menor)/2;
            found=varrerlista(matricula,meio,head,cabecao,tail);
            if (found==NULL)//matricula não encontrada
            {
                printf("\n");
            }
            else
            {
                printf("\nnome do aluno = %s",found->nome);
                printf("\ndisciplinas existentes");
                //exibirdisciplinas(found->primeiro);
                atual2=found->primeiro;
                atual2=atual2->proximo;
                do{
                    printf("\n%s",atual2->disc);
                    atual2=atual2->proximo;
                }
                while(atual2!=NULL);
                removerdisciplina(found->primeiro);
            }
        }
        if (escolha==5)
        {
            teste=7;
            printf("\nDigite a matricula do aluno:\t");
            scanf("%d",&matricula);
            meio=(head->maior+head->menor)/2;
            found=varrerlista(matricula,meio,head,cabecao,tail);
            while (found==NULL)//matricula não encontrada
            {
                printf(". Deseja incluir novo aluno com essa matricula?(1-S/0-N)");
                scanf("%d",&teste);
                teste=looppergunta(teste,1);
                if(teste==0)
                {
                    printf("\nNenhuma nota foi incluida");
                    teste=-1;//Jumper
                    break;
                }
                else
                {
                    teste=head->quant_nos;
                    while(teste==head->quant_nos)
                    {
                        head=inseriraluno(head,cabecao,tail,matricula);
                    }
                found=varrerlista(matricula,meio,head,cabecao,tail);
                }
            }
            if(teste!=-1)
            {
                printf("\nnome do aluno = %s",found->nome);
                inserirnotas(found,headnotas);
            }
        }
        if(escolha==6)
        {
            printf("\nDigite a matricula do aluno");
            scanf("%d",&matricula);
            meio=(head->maior+head->menor)/2;
            found=varrerlista(matricula,meio,head,cabecao,tail);
            if (found==NULL)//matricula não encontrada
            {
                printf("\nMatricula nao encontrada");
            }
            else
            {
                alterarnotas(found);
            }

        }
        if(escolha==7)
        {
            printf("\nDigite a matricula do aluno: ");
            scanf("%d",&matricula);
            meio=(head->maior+head->menor)/2;
            found=varrerlista(matricula,meio,head,cabecao,tail);
            if (found==NULL)//matricula não encontrada
            {
                printf("\nMatricula nao encontrada");
            }
            else
            {
                printf("=====================================");
                printf("\nmatricula\tnome\n");
                printf("%i\t\t%s\n",found->mat,found->nome);//matricula e nome
                printf("disciplinas\tAV1\tAV2\tAVF\n");//cabecalho
                teste=exibirdisciplinas(found->primeiro,1);
                if(teste==1)
                {
                    printf("\nnao ha disciplinas cadastradas para o aluno");
                }
            }

        }
        if (escolha==8)
        {
            imprimirtudo(head,cabecao,tail);
            
            pflista = fopen(cflista,"w");
            if(pflista == NULL)
            {printf("Erro, nao foi possivel abrir o arquivo cflista.txt\n");}
            else
            {
                fimprimirtudo(pflista,head,cabecao,tail);
                printf("\nArquivo cflista disponivel em txt para impressao\n");
            }
            fclose(pflista);

        }
        if(escolha==9)
        {
            exibirinfohead(head);
        }

    }
    return 0;
}


