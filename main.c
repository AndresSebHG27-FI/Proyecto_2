#include "polinomio.h"
// ./a,out -in entrada.txt -out salida.txt -re registro
int main(int argc, char **argv)
{
    if (argc == 7)
    {
        if (strcmp(argv[1], "-in") == 0)
        {
            open_in_file(argv[2]);
        }
        else if (strcmp(argv[1], "-out") == 0)
        {
            open_out_file(argv[2]);
        }
        else if (strcmp(argv[1], "-re") == 0)
        {
            open_registro(argv[2]);
        }
        if (strcmp(argv[3], "-in") == 0)
        {
            open_in_file(argv[4]);
        }
        else if (strcmp(argv[3], "-out") == 0)
        {
            open_out_file(argv[4]);
        }
        else if (strcmp(argv[3], "-re") == 0)
        {
            open_registro(argv[4]);
        }
        if (strcmp(argv[5], "-in") == 0)
        {
            open_in_file(argv[6]);
        }
        else if (strcmp(argv[5], "-out") == 0)
        {
            open_out_file(argv[6]);
        }
        else if (strcmp(argv[5], "-re") == 0)
        {
            open_registro(argv[6]);
        }
    }
    if (argc == 5)
    {
        if (strcmp(argv[1], "-in") == 0)
        {
            open_in_file(argv[2]);
        }
        else if (strcmp(argv[1], "-out") == 0)
        {
            open_out_file(argv[2]);
        }
        else if (strcmp(argv[1], "-re") == 0)
        {
            open_registro(argv[2]);
        }
        if (strcmp(argv[3], "-in") == 0)
        {
            open_in_file(argv[4]);
        }
        else if (strcmp(argv[3], "-out") == 0)
        {
            open_out_file(argv[4]);
        }
        else if (strcmp(argv[3], "-re") == 0)
        {
            open_registro(argv[4]);
        }
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "-in") == 0)
        {
            open_in_file(argv[2]);
        }
        else if (strcmp(argv[1], "-out") == 0)
        {
            open_out_file(argv[2]);
        }
        else if (strcmp(argv[1], "-re") == 0)
        {
            open_registro(argv[2]);
        }
    }
    POL A, B, C;
    DIV D;
    int t, t1;
    int op;
    float l;
    char *polC;
    init();
    while (op != 12)
    {
        menu();
        printf("¿Qué desea realizar?\n");
        scanf("%d", &op);
        if (op < 1 || op > 10)
        {
            printf("Opción incorrecta, introduzca de nuevo\n");
            scanf("%d", &op);
        }
        switch (op)
        {
        case 1:
            printf("Suma\n");
            printMemory(memoria);
            printf("Selecione 2 de acuerdo al numero y separados por un tabulador\n");
            scanf("%d\t%d", &t, &t1);
            A = recoMemory(memoria, t);
            B = recoMemory(memoria, t1);
            C = add(A, B);
            cpyinmem(C);
            break;
        case 2:
            printf("Resta\n");
            printMemory(memoria);
            printf("Selecione 2 de acuerdo al numero y separados por un tabulador\n");
            scanf("%d\t%d", &t, &t1);
            A = recoMemory(memoria, t);
            B = recoMemory(memoria, t1);
            C = sub(A, B);
            cpyinmem(C);
            break;
        case 3:
            printf("Multiplicacion por escalar\n");
            printMemory(memoria);
            printf("Selecione 1 deacuerdo al numero y un escalar separados por un tabulador\n");
            scanf("%d\t%f", &t, &l);
            A = recoMemory(memoria, t);
            C = esc_pol(A, l);
            cpyinmem(C);
            break;
        case 4:
            printf("Multiplicación\n");
            printMemory(memoria);
            printf("Selecione 2 deacuerdo al numero y separelos por un tabulador\n");
            scanf("%d\t%d", &t, &t1);
            A = recoMemory(memoria, t);
            B = recoMemory(memoria, t1);
            C = pol_prod(A, B);
            cpyinmem(C);
            break;
        case 5:
            printf("Division\n");
            printMemory(memoria);
            printf("Selecione 2 deacuerdo al numero y separelos por un tabulador\n");
            scanf("%d\t%d", &t, &t1);
            A = recoMemory(memoria, t);
            B = recoMemory(memoria, t1);
            D = div_larga(A, B);
            cpyinmem(D.cociente);
            cpyinmem(D.residuo);
            break;
        case 6:
            if (memoria.cont == 0)
            {
                printf("No hay nada en la memoria");
            }
            else
            {
                printMemory(memoria);
            }
            break;
        case 7:
            printf("Leer polinomio de teclado\n");
            A = pol_creat();
            pol_print(A);
            cpyinmem(A);
            break;
        case 8:
            printf("8.Leer polinomio de archivo\n");
            C = fread_pol(infile);
            cpyinmem(C);
            break;
        case 9:
            printf("Escribir polinomio en archivo\n");
            printMemory(memoria);
            printf("Seleciona tu polinomio: ");
            scanf("%d", &t);
            fwrite_pol(t);
            break;
        case 10:
            printf("Salir\n");
            exit(0);
            break;
        }
    }
return 0;
}