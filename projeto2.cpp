
#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAGENTA "\x1b[45m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"
#define YELLOW "\x1b[33m"
#define RED "\x1b[31m"
#define BLUE "\x1b[34m"

int main()
{

    system("chcp 65001");
    setlocale(LC_ALL, "pt_BR.UTF-8");
    system("CLS");
    
    char linha[40] = "-~--~--~--~--~--~--~--~--~--~--~--~-";
    char destinos[100][28], pessoas[4], menores[4], assentos[4], posicao[4];
    char *destino;
    int assen_da_reser[200][201], assentos_disp[50][201], assentos_reser[50][201], assentos_confir[50][201];
    int id_reservas[200] = {0}, assentos_aviao[200] = {0};
    int id_reserva = 0, num_aviao = 0, confirmacao = 0, id_atual = 1, aviao = 0, id_temp = 0;
    float valor_final = 0;
    float valor_reser[200] = {0}, confirmados[200] = {0};

    while (true)
    {
        printf("\n%s\n", linha);
        printf(YELLOW "       SALUMAR LINHAS AEREAS        \n" RESET);
        printf("%s\n", linha);
        printf("DIGITE O QUE QUER FAZER\n");
        printf("1-REALIZAR SUA RESERVA?\n2-CONFIRMAR RESERVA\n3-CANCELAR SUA RESERVA\n4-CONSULTAR STATUS DE VOO\n5-TABELA DE VALORES\nESC-SAIR\n");
        printf("APERTE UM NUMERO CORRESPONDENTE\n");
        int opcao_inicio;
        opcao_inicio = getch();
        if (opcao_inicio - 48 == 1)
        {
            system("CLS");
            printf("\n%s\n", linha);
            fflush(stdin);
            printf("DESTINO: ");
            fgets(destinos[id_atual], 27, stdin);
            printf("%s\n", linha);
            fflush(stdin);
            printf("QUANTIDADE DE PASSAGENS?: ");
            fgets(pessoas, 4, stdin);
            //aqui tem o loop para fazer a verificação do que foi inserido
            while (isalpha(pessoas[0]) != 0 || isalpha(pessoas[1]) != 0 || isalpha(pessoas[2]) != 0 ||
                   atoi(pessoas) < 1 || atoi(pessoas) > 200)
            {
                system("CLS");
                printf(MAGENTA "VALOR INSERIDO INVALIDO\n" RESET);
                printf("QUANTIDADE DE PASSAGENS ?: ");
                fgets(pessoas, 4, stdin);
            }
            printf("HÁ MENORES DE 5 ANOS DE IDADE?: ");
            fgets(menores, 4, stdin);
            while (isalpha(menores[0]) != 0 || isalpha(menores[1]) != 0 || isalpha(menores[2]) != 0 ||
                   atoi(menores) < 0 || atoi(menores) > atoi(pessoas))
            {
                system("CLS");
                printf(MAGENTA "VALOR INVÁLIDO, DIGITE OUTRO VALOR\n" RESET);
                printf("QUANTOS MENORES DE 5 ANOS?: ");
                fgets(menores, 4, stdin);
            }
            valor_final = (atoi(pessoas) - atoi(menores)) * 1000 + atoi(menores) * 500;
            valor_reser[id_atual] = valor_final;
            printf("%s\n", linha);
            printf("VALOR A PAGAR R$:%.2f\n", valor_final);
            fflush(stdin);
            system("PAUSE");
            system("CLS");
            printf("%s\n", linha);
            fflush(stdin);
            printf("QUAL A QUANTIDADE DE ASSENTOS NO AVIÃO?: ");
            fgets(assentos, 4, stdin);
            while (isalpha(assentos[0]) != 0 || isalpha(assentos[1]) != 0 || isalpha(assentos[2]) != 0 ||
                   atoi(assentos) < 90 || atoi(assentos) > 200)
            {
                system("CLS");
                printf(MAGENTA "DIGITE UM VALOR VALIDO\n" RESET);
                printf("QUANTOS ASSENTOS ?: ");
                fgets(assentos, 4, stdin);
            }
           
            //loop de identificação do destino atual nos que estão na lista para acessar o mesmo voo
            for (int i = 1; i <= 100; i++)
            { //condicional que compara os destinos dos voos
                if (strcmp(destino, destinos[i]) == 0)
                {
                    num_aviao = i;
                    //aqui verifica se o número de assentos do avião é o mesmo que foi inserido pelo cliente
                    if (atoi(assentos) != assentos_aviao[num_aviao])
                    {
                        printf(MAGENTA "ESTE NÚMERO ESTÁ ERRADO O AVIÃO %d POSSUI %d ASSENTOS\n" RESET, num_aviao, assentos_aviao[num_aviao]);
                        fflush(stdin);
                    }
                    break;
                }
                else
                {
                    num_aviao = id_atual;
                    assentos_aviao[num_aviao] = atoi(assentos);
                }
            }
            printf("%s\n", linha);
            printf("ESCOLHA OS ASSENTOS DESEJADOS\n");
            printf("%s\n", linha);
            printf(BLUE "C-CONFIRMADOS\n" MAGENTA "R-RESERVADOS\n" GREEN "D-DISPONIVEIS\n" RESET);
            printf("%s\n", linha);
            fflush(stdin);
            for (int i = 1; i <= assentos_aviao[num_aviao]; i++)
            {
                assentos_disp[num_aviao][i] = i;
                //aqui é pra verificar o status do assento
                if (assentos_confir[num_aviao][i] != 0)
                {
                    printf(BLUE "%d" RESET "--", assentos_confir[num_aviao][i]);
                    fflush(stdin);
                    continue;
                }
                else if (assentos_reser[num_aviao][i] == assentos_disp[num_aviao][i])
                {
                    printf(RED "%d" RESET "--", assentos_reser[num_aviao][i]);
                    fflush(stdin);
                    continue;
                }
                else
                {
                    printf(GREEN "%d" RESET "--", assentos_disp[num_aviao][i]);
                    fflush(stdin);
                    continue;
                }
            }
            printf("\n");
            for (int i = 1; i <= atoi(pessoas); i++)
            {
                printf("%s\n", linha);
                printf("ESCOLHA O %dº ASSENTO: ", i);
                fflush(stdin);
                fgets(posicao, 4, stdin);
                //loop para verificação do input oque foi inserido no caso
                while (isalpha(posicao[0]) != 0 || isalpha(posicao[1]) != 0 || isalpha(posicao[2]) != 0 ||
                       atoi(posicao) < 1 || atoi(posicao) > assentos_aviao[num_aviao])
                {
                    system("CLS");
                    printf(MAGENTA "VALOR INVALIDO\n" RESET);
                    printf("ESCOLHA O %dº ASSENTO: ", i);
                    fflush(stdin);
                    fgets(posicao, 4, stdin);
                }
                assen_da_reser[id_atual][atoi(posicao)] = atoi(posicao);
                assentos_reser[num_aviao][atoi(posicao)] = atoi(posicao);
            }
            printf("%s\n", linha);
            printf("ID DESUA RESERVA: %d\n", id_atual);
            fflush(stdin);
            printf(GREEN "RESERVA COCLUIDA, AGUARDAMOS CONFIRMACAO\n" RESET);
            id_reservas[id_atual] = id_atual;
            id_atual++;
            system("PAUSE");
            system("CLS");
        }
        else if (opcao_inicio - 48 == 2)
        {
            id_reserva = 0;
            system("CLS");
            printf("%s\n", linha);
            printf("DIGITE SEU ID DA RESERVA: ");
            scanf("%d", &id_reserva);
            //condicional para verificar se o id é existente
            if (id_reserva != id_reservas[id_reserva])
            {
                while (id_reserva != id_reservas[id_reserva])
                {
                    system("CLS");
                    printf(MAGENTA "ESTE ID NÃO EXISTE, TENTE DENOVO\n" RESET);
                    printf("ENSIRA SEU ID DE RESERVA: ");
                    scanf("%d", &id_reserva);
                    fflush(stdin);
                }
            }
            id_temp = id_reserva;
            printf("VALOR A SER PAGO R$:%.2f\n", valor_reser[id_reserva]);
            fflush(stdin);
            printf("DESEJA CONFIRMAR SUA RESERVA?\nS-SIM\nN-NÃO\n");
            confirmacao = getch();
            if (confirmacao == 115 || confirmacao == 83)
            { //loop para comparar destinos e realizar modificações no mesmo voo
                for (int i = 1; i <= 100; i++)
                {
                    if (strcmp(destinos[i], destinos[id_reserva]) == 0)
                    {
                        id_reserva = i;
                        break;
                    }
                }
                printf("ASSENTOS RESERVADOS: ");
                //verificação de quais foram os assentos reservados e adicionar aos assentos confirmados
                for (int assen = 1; assen <= 200; assen++)
                {
                    if (assen_da_reser[id_temp][assen] != 0)
                    {
                        assentos_confir[id_reserva][assen] = assen;
                        printf("%d ", assentos_confir[id_reserva][assen]);
                    }
                }
                confirmados[id_reserva] += valor_reser[id_temp];
                printf("\n");
                printf(BLUE "RESERVA CONFIRMADA COM SUCESSO\n" RESET);
            }
            else if (confirmacao == 110 || confirmacao == 78)
            {
                printf(MAGENTA "OK, VC TEM ATE 1 SEMANA PARA CONFIRMAÇÃO VOLTE LOGO\n" RESET);
            }
            system("PAUSE");
            system("CLS");
        }
        else if (opcao_inicio - 48 == 3)
        {
            id_reserva = 0;
            system("CLS");
            printf("%s\n", linha);
            printf("DIGITE O ID DA RESERVA QUE DESEJA CANCELAR: ");
            scanf("%d", &id_reserva);
            if (id_reserva != id_reservas[id_reserva])
            {
                while (id_reserva != id_reservas[id_reserva])
                {
                    system("CLS");
                    printf(MAGENTA "ID NÃO ENCONTRADO,TENTE NOVAMENTE\n" RESET);
                    printf("DIGITE O ID DA RESERVA: ");
                    scanf("%d", &id_reserva);
                    fflush(stdin);
                }
            }
            printf("ASSENTOS DA RESERVA: ");
            for (int assen = 1; assen < 201; assen++)
            {
                if (assen_da_reser[id_reserva][assen] != 0)
                {
                    printf("%d ", assen_da_reser[id_reserva][assen]);
                }
            }
            printf("\n");
            fflush(stdin);
            printf("CONFIRMAR CANCELAMENTO\nS-SIM\nN-NÃO\n");
            confirmacao = getch();
            if (confirmacao == 115 || confirmacao == 83)
            {
                for (int assen = 1; assen <= 200; assen++)
                {
                    if (assen_da_reser[id_reserva][assen] != 0)
                    {
                        for (int i = 1; i <= 100; i++)
                        {
                            if (strcmp(destinos[i], destinos[id_reserva]) == 0)
                            {
                                id_temp = i;
                                break;
                            }
                        }
                        assentos_reser[id_temp][assen] = 0;
                    }
                }
                printf(MAGENTA"RESERVA CANCELADA\n" RESET);
            }
            else if (confirmacao == 110 || confirmacao == 78)
            {
                printf(BLUE "NENHUMA ALTEAÇÃO FEITA NA RESERVA\n" RESET);
            }
            system("PAUSE");
            system("CLS");
        }
        else if (opcao_inicio - 48 == 4)
        {
            system("CLS");
            printf("%s\n", linha);
            fflush(stdin);
            printf("QUAL DESTINO DE VOO QUE DESEJA CONSULTAR?: ");
            fgets(destino, 27, stdin);
            printf("%s\n", linha);
            fflush(stdin);
            for (int i = 1; i <= 100; i++)
            {
                if (strcmp(destino, destinos[i]) == 0)
                {
                    aviao = i;
                    break;
                }
            }
            printf(BLUE "C- CONFIRMADOS\n" RED "R-RESERVADOS\n" GREEN "D- DISPONIVEIS\n" RESET);
            printf("%s\n", linha);
            fflush(stdin);
            for (int i = 1; i <= assentos_aviao[aviao]; i++)
            {
                assentos_disp[aviao][i] = i;
                if (assentos_confir[aviao][i] != 0)
                {
                    printf(BLUE "%d" RESET "--", assentos_confir[aviao][i]);
                    fflush(stdin);
                    continue;
                }
                else if (assentos_reser[aviao][i] == assentos_disp[aviao][i])
                {
                    printf(RED "%d" RESET "--", assentos_reser[aviao][i]);
                    fflush(stdin);
                    continue;
                }
                else
                {
                    printf(GREEN "%d" RESET "--", assentos_disp[aviao][i]);
                    fflush(stdin);
                    continue;
                }
            }
            printf("\n%s\n", linha);
            printf("O VALOR TOTAL: R$:%.2f\n", confirmados[aviao]);
            printf("%s\n", linha);
            fflush(stdin);
            system("PAUSE");
            system("CLS");
        }
         else if (opcao_inicio - 48 == 5) //aqui so um auxílio para o cliente
		{
            printf("\n%s\n", linha);
            printf(BLUE "MAIORES DE 5 ANOS R$1000" RESET);
            printf(BLUE "MENORES, METADE DO valor R$500" RESET);
            printf("ESC-PARA SAIR\n");
            printf("%s\n", linha);
            fflush(stdin);
			system("PAUSE");
            system("CLS");
        }
        else if (opcao_inicio == 27)
        {
            break;
        }

        fflush(stdin);
    }
    return 0;
}
