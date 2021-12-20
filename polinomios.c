#include "polinomio.h"
/*info
Fecha:7/12/2021
Autor:Aguilar Erick
Ultima revision: 7/12/2021
*/
//<---------ARCHIVOS--------------->
/**
 * @brief Abre el archivo de entrada
 *
 * @param filename El nombre de nuestro archivo de entrad
 */
void open_in_file(char *filename)
{
    infile = fopen(filename, "r");
    if (!infile)
    {
        printf("No tienes permisos suficientes para abrir %s\n", filename);
    }
}
/**
 * @brief Abre el archivo de salida
 *
 * @param filename El nombre del archivo de salida
 */
void open_out_file(char *filename)
{
    outfile = fopen(filename, "a+");
    if (!outfile)
    {
        printf("No tienes permisos para abrir %s\n", filename);
    }
}
/**
 * @brief Abre el archivo de nuestro registro
 *
 * @param filename El nombre del achivo registro
 */
void open_registro(char *filename)
{
    registro = fopen(filename, "w");
    if (!registro)
    {
        printf("No tiene permisos para abrir el archivo\n");
    }
}
/**
 * @brief Cierra un archivo
 *
 * @param f El archvo a cerrar
 */
void close_file(FILE *f)
{
    fclose(f);
}
/**
 * @brief Lee un polinomio de un archivo
 *
 * @param in El archivo entrada
 * @return POL El polinomio obtenido
 */
POL fread_pol(FILE *in)
{
    POL A;
    A.ter = (TERMINO *)malloc(sizeof(TERMINO));
    char *pol = (char *)malloc(sizeof(char));
    char *termi = (char *)malloc(sizeof(char));
    char *c_c = (char *)malloc(sizeof(char));
    float c_f;
    char *exp = (char *)malloc(sizeof(char));
    int ep;
    int indice;
    size_t numbytes = 0;
    A.nter = 0;
    int i = 0;
    char c[1];
    fscanf(in, "%s", pol);
    for (;; pol = NULL)
    {
        termi = strtok(pol, "_");
        if (termi != NULL)
        {
            A.ter = (TERMINO *)realloc(A.ter, (A.nter + 1) * sizeof(TERMINO));
            A.nter++;
/*             puts(termi);
 */            if (find(termi, 'x'))
            {
                switch (strlen(termi))
                {
                case 1: // x
                    if (termi[0] == 'x')
                        A.ter[i] = conver(1.0, 1);
                    break;
                case 2:                    //#x -x
                    if (isdigit(termi[0])) //#x
                    {
                        c_c = strncpy(c_c, termi, 1);
                        puts(c_c);
                        c_f = strtof(c_c, NULL);
                        A.ter[i] = conver(c_f, 1);
                    }
                    else if (termi[0] == '-' && termi[1] == 'x')
                        A.ter[i] = conver(-1, 1);
                    break;
                case 3:                  //##x -#x x^#
                    if (termi[0] == 'x') // x^#
                    {
                        indice = findstrc(termi, '^');
                        exp = strcpyrng(termi, indice, 3);
                        ep = strtoi(exp);
                        A.ter[i] = conver(1, ep);
                    }
                    else if (isdigit(termi[0]) || termi[0] == '-') //##x , -#x
                    {
                        c_c = strncpy(c_c, termi, 2);
                        c_f = strtof(c_c, NULL);
                        A.ter[i] = conver(c_f, 1);
                    }
                    break;
                case 4:                  //###x -##x -x^# #x^#
                    if (termi[3] == 'x') //###x -##x
                    {
                        c_c = strncpy(c_c, termi, 3);
                        c_f = strtof(c_c, NULL);
                        A.ter[i] = conver(c_f, 1);
                    }
                    else if (termi[0] == '-') //-x^#
                    {
                        indice = findstrc(termi, '^');
                        exp = strcpyrng(termi, indice, 4);
                        ep = strtoi(exp);
                        A.ter[i] = conver(-1, ep);
                    }
                    else
                    {
                        c_c = strncpy(c_c, termi, findstrc(termi, 'x'));
                        c_f = strtof(c_c, NULL);
                        indice = findstrc(termi, '^');
                        exp = strcpyrng(termi, indice, strlen(termi));
                        ep = strtoi(exp);
                        A.ter[i] = conver(c_f, ep);
                    }
                    break;
                default:                                 //####x    -###x   ##x^#   #x^## x^### -x^##
                    if (termi[strlen(termi) - 1] == 'x') //#...#x   -#..#x
                    {
                        c_c = strncpy(c_c, termi, strlen(termi));
                        c_f = strtof(c_c, NULL);
                        A.ter[i] = conver(c_f, 1);
                    }
                    else if (termi[0] == '-' && termi[1] == 'x') //-x^#..#
                    {
                        indice = findstrc(termi, '^');
                        exp = strcpyrng(termi, indice, strlen(termi));
                        ep = strtoi(exp);
                        A.ter[i] = conver(-1, ep);
                    }
                    else if (termi[0] == 'x')
                    {
                        indice = findstrc(termi, '^');
                        exp = strcpyrng(termi, indice, strlen(termi));
                        ep = strtoi(exp);
                        A.ter[i] = conver(1, ep);
                    }
                    else
                    {
                        c_c = strncpy(c_c, termi, findstrc(termi, 'x'));
                        c_f = strtof(c_c, NULL);
                        indice = findstrc(termi, '^');
                        exp = strcpyrng(termi, indice, strlen(termi));
                        ep = strtoi(exp);
                        A.ter[i] = conver(c_f, ep);
                    }
                    break;
                }
            }
            else
            {
                A.ter[i].exp = 0;
                A.ter[i].coef = strtof(termi, NULL);
            }
        }
        i++;
        if (termi == NULL)
            break;
    }
    free(c_c);
    free(exp);
    free(pol);
    bubble_pol(A);
    pol_print(A);
    return A;
}
/**
 * @brief Escribe en un archivo
 *
 * @param h La poscion del polinomio que queremos escribir.
 */
void fwrite_pol(int h)
{
    fputs(POLtoSTR(memoria.polis[h-1]),outfile);
    fputc('\n',outfile);
}
//<-------AUXILIARES-------->
/**
 * @brief Calcula la potencia entera
 *
 * @param base
 * @param expo
 * @return int El valor de la potencia
 */
int pot(int base, int expo)
{
    int res = 1;
    for (int i = 0; i < expo; i++)
    {
        res = res * base;
    }
    return res;
}
/**
 * @brief Comvierte una cadena que representa un entero en un numero enter
 *
 * @param str Cadena a convertir
 * @return int
 */
int strtoi(char *str)
{
    int res = 0;
    int num;
    int exp = strlen(str) - 1;
    for (int i = 0; i < strlen(str); i++)
    {
        num = ((int)str[i] - 48) * pot(10, exp - i);
        res += num;
    }
    return res;
}

/**
 * @brief Copia de una cadena un intervalo de caracteres
 *
 * @param str Cadena fuente
 * @param a (a,b] Rango
 * @param b
 * @return char* La sub cadena
 */
char *strcpyrng(char *str, int a, int b)
{
    char *ret = (char *)malloc(sizeof(char));
    char aux[2];
    aux[1] = '\0';
    for (int i = a + 1; i < b; i++)
    {
        aux[0] = str[i];
        strcat(ret, aux);
    }
    return ret;
}
/**
 * @brief Busca un carracter en un a cadena
 *
 * @param a Cadena en la que buscar
 * @param b El caracter a buscar
 * @return true
 * @return false
 */
bool find(char *a, char b)
{
    int o = strlen(a);
    bool flag = false;
    for (int i = 0; i < o; i++)
    {
        if (a[i] == b)
        {
            flag = true;
            return flag;
        }
    }
    return flag;
}
/**
 * @brief Busca un caracter en un arrgleo y si no lo encuantra devuelva la longitud de la cadena
 *
 * @param str El arreglo en que buscar
 * @param c El caracter a buscar
 * @return int El indice en el que encuentra el primer caracter igual a c
 */
int findstrc(char *str, char c)
{
    int pos = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == c)
        {
            return i;
        }
        pos++;
    }
    return pos;
}
void menu()
{
    printf("----------CALCULADORA DE POLINOMIOS------------\n");
    printf("Opciones\n");
    printf("1.Suma\n");
    printf("2.Resta\n");
    printf("3.Multiplicacion por un escalar\n");
    printf("4.Multiplicacion\n");
    printf("5.Division\n");
    printf("6.Imprimir memoria\n");
    printf("7.Leer polinomio de teclado\n");
    printf("8.Leer polinomio de archivo\n");
    printf("9.Escribir polinomio en archivo\n");
    printf("10.Salir\n");
}
void init()
{
    memoria.polis = initmemory();
    memoria.cont = 0;
}
//<-------------OPERACIONES------------>
/**
 * @brief Elimina los ceros de un polinomio no importando en que posicion se encuentre
 *
 * @param A Polinomio a eliminar
 * @return POL
 */
POL del_zero(POL A)
{
    POL C;
    C = cpy(A);
    int cont = 0;
    int pas = 0; // 0x^3 2x^2 x
    // x 2x^2
    TERMINO aux;
    bool flag = true;
    int i = 0;
    while (flag)
    {
        i = 0;
        flag = false;
        pas++;
        while (i < C.nter - pas)
        {
            if (C.ter[i].coef == 0.0f)
            {
                flag = true;
                aux = C.ter[i];
                C.ter[i] = C.ter[i + 1];
                C.ter[i + 1] = aux;
            }
            i++;
        }
    }
    if (C.ter[0].coef == 0.0f)
    {
        C.ter = (TERMINO *)realloc(C.ter, (sizeof(TERMINO)));
        C.nter = 1;
        C.ter[0].coef = 0;
        C.ter[0].exp = 0;
        return C;
    }
    i = C.nter - 1;
    while (C.ter[i].coef == 0.0f)
    {
        cont++;
        i--;
    }
    C.ter = (TERMINO *)realloc(C.ter, (C.nter - cont) * (sizeof(TERMINO)));
    C.nter = C.nter - cont;
    bubble_pol(C);
    return C;
}
/**
 * @brief Suma polinomios A+B
 *
 * @param A
 * @param B
 * @return POL El resultado C
 */
POL add(POL A, POL B)
{
    POL C;
    //<------INIDICES------>
    int i = 0;
    int j = 0;
    int k = 0;
    //<-------VOLORES------>
    //<-------PROCESO------->
    if (A.ter[0].exp >= B.ter[0].exp)
    {
        C.ter = (TERMINO *)malloc((A.ter[0].exp + 1) * sizeof(TERMINO));
        C.nter = A.ter[0].exp + 1;
    }
    else
    {
        C.ter = (TERMINO *)malloc((B.ter[0].exp + 1) * sizeof(TERMINO));
        C.nter = B.ter[0].exp + 1;
    }
    //<<--------SUMA------->
    for (k = 0; k < C.nter; k++)
    {
        if (A.ter[i].exp == B.ter[j].exp)
        {
            C.ter[k].coef = A.ter[i].coef + B.ter[j].coef;
            C.ter[k].exp = A.ter[i].exp;
            i++;
            j++;
            /* printf("a\n"); */
        }
        else if (A.ter[i].exp > B.ter[j].exp)
        {
            C.ter[k] = A.ter[i];
            i++;
            /*printf("b\n");*/
        }
        else if (A.ter[i].exp < B.ter[j].exp)
        {
            C.ter[k].coef = B.ter[j].coef;
            C.ter[k].exp = B.ter[j].exp;
            j++;
            /* printf("c\n"); */
        }
        if (j == B.nter && i == A.nter)
            break;
    }
    C = del_zero(C);
    return C;
}

/**
 * @brief Resta de polinomio A-B
 *
 * @param A
 * @param B
 * @return POL
 */
POL sub(POL A, POL B)
{
    POL C;
    //<------INIDICES------>
    int i = 0;
    int j = 0;
    int k = 0;
    //<-------PROCESO------->
    if (A.ter[0].exp >= B.ter[0].exp)
    {
        C.ter = (TERMINO *)malloc((A.ter[0].exp + 1) * sizeof(TERMINO));
        C.nter = A.ter[0].exp + 1;
    }
    else
    {
        C.ter = (TERMINO *)malloc((B.ter[0].exp + 1) * sizeof(TERMINO));
        C.nter = B.ter[0].exp + 1;
    }
    //<<--------RESTA------->
    for (k = 0; k < C.nter; k++)
    {
        if (A.ter[i].exp == B.ter[j].exp)
        {
            C.ter[k].coef = A.ter[i].coef - B.ter[j].coef;
            C.ter[k].exp = A.ter[i].exp;
            i++;
            j++;
        }
        else if (A.ter[i].exp > B.ter[j].exp)
        {
            C.ter[k] = A.ter[i];
            i++;
        }
        else
        {
            C.ter[k].coef = (-1) * B.ter[j].coef;
            C.ter[k].exp = B.ter[j].exp;
            j++;
        }
        if (j == B.nter && i == A.nter)
            break;
    }
    C = del_zero(C);
    return C;
}
/**
 * @brief Multiplicacion por escalar
 *
 * @param A polinomio
 * @param s escalar
 * @return POL
 */
POL esc_pol(POL A, double s)
{
    POL C;
    C.ter = (TERMINO *)malloc(A.nter * sizeof(TERMINO));
    printf("Nterm A: %d\n",A.nter);
    C.nter = A.nter;
    for (int i = 0; i < C.nter; i++)
    {
        C.ter[i].coef = A.ter[i].coef * s;
        C.ter[i].exp = A.ter[i].exp;
    }
    return C;
}
/**
 * @brief Producto de pólinomios A*B
 *
 * @param A
 * @param B
 * @return POL
 */
POL pol_prod(POL A, POL B)
{
    POL C;
    TERMINO tauxi;
    C.ter = (TERMINO *)malloc((A.ter[0].exp + B.ter[0].exp + 1) * sizeof(TERMINO));
    C.nter = A.ter[0].exp + B.ter[0].exp + 1;
    C.ter[0].exp = A.ter[0].exp + B.ter[0].exp;
    for (int i = 0; i < A.nter; i++)
    {
        for (int j = 0; j < B.nter; j++)
        {
            tauxi.coef = A.ter[i].coef * B.ter[j].coef;
            tauxi.exp = A.ter[i].exp + B.ter[j].exp;
            for (int k = 0; k < C.nter; k++)
            {
                if (tauxi.exp == C.ter[k].exp)
                {
                    C.ter[k].coef = C.ter[k].coef + tauxi.coef;
                    C.ter[k].exp = tauxi.exp;
                    break;
                }
                else if (C.ter[k + 1].coef == 0.0)
                {
                    C.ter[k + 1] = tauxi;
                    break;
                }
            }
        }
    }
    C = del_zero(C);
    return C;
}
/**
 * @brief Division P/Q
 *
 * @param P
 * @param Q
 * @return POL
 */
POL pol_div(POL P, POL Q)
{
    POL C;
    POL ax;
    C.ter = (TERMINO *)malloc((P.grd - Q.grd + 1) * sizeof(TERMINO));
    C.nter = P.grd - Q.grd + 1;
    float f = (-1) * Q.ter[1].coef / Q.ter[0].coef;
    ax = polcpy(P);
    pol_print(ax);
    C.ter[0].coef = P.ter[0].coef;
    C.ter[0].exp = P.ter[0].exp - 1;
    for (int i = 1; i < C.nter; i++)
    {
        C.ter[i].coef = ax.ter[i].coef + (f * C.ter[i - 1].coef);
        C.ter[i].exp = ax.ter[i].exp - 1;
    }
    free(ax.ter);
    int cont = 0;
    int i = C.nter - 1;
    while (C.ter[i].coef == 0.0f)
    {
        cont++;
        i--;
    }
    C.ter = (TERMINO *)realloc(C.ter, (C.nter - cont) * sizeof(TERMINO));
    C.nter = C.nter - cont;
    bubble_pol(C);
    return C;
}
DIV div_larga(POL A, POL B)
{
    DIV C;
    C.cociente.ter = (TERMINO *)malloc(sizeof(TERMINO));
    C.cociente.nter = 0;
    POL auxi;
    auxi = cpy(A);
    POL auxi2;
    POL mono;
    mono.ter = (TERMINO *)malloc(sizeof(TERMINO));
    mono.nter = 1;
    while (auxi.ter[0].exp >= B.ter[0].exp)
    {
        mono.ter[0].coef = auxi.ter[0].coef / B.ter[0].coef;
        mono.ter[0].exp = auxi.ter[0].exp - B.ter[0].exp;

        C.cociente.ter = (TERMINO *)realloc(C.cociente.ter, (C.cociente.nter + 1) * sizeof(TERMINO));
        C.cociente.ter[C.cociente.nter] = mono.ter[0];
        pol_print(C.cociente);
        C.cociente.nter++;
        auxi2 = pol_prod(mono, B);
        pol_print(auxi2);
        auxi = sub(auxi, auxi2);
    }
    C.residuo = auxi;
    return C;
}
/**
 * @brief Copia un polinomio A y le baja el grado en 1 y llena de ceros
 *
 * @param A 4x^4
 * @return POL 4x^3 +0x^3 0x^2 0x 0
 */
POL polcpy(POL A)
{
    POL C;
    C.ter = (TERMINO *)malloc((A.grd + 1) * sizeof(TERMINO));
    C.nter = A.grd + 1;
    int j = 0;
    for (int i = 0; i < C.nter; i++)
    {
        C.ter[i].exp = C.nter - i - 1;
    }
    for (int i = 0; i < C.nter; i++)
    {
        if (C.ter[i].exp == A.ter[j].exp)
        {
            C.ter[i].coef = A.ter[j].coef;
            j++;
        }
    }
    C.grd = C.nter - 1;
    return C;
}
POL cpy(POL A)
{
    POL B;
    B.ter = (TERMINO *)malloc(A.nter * sizeof(TERMINO));
    for (int i = 0; i < A.nter; i++)
    {
        B.ter[i] = A.ter[i];
    }
    B.nter = A.nter;
    return B;
}
TERMINO conver(float coef, int exp)
{
    TERMINO a;
    a.coef = coef;
    a.exp = exp;
    return a;
}
//<-------------MEMORIA---------------->
/**
 * @brief Crea un polinomio con una cantida de terminos igual a nterl y lee
 *
 * @param nterl El numero de terminos
 * @return POL La direccion de memoria para la estructura POL con ntel terminos
 */
POL pol_creat()
{
    //<-----VARIABLES------>
    POL A;
    A.ter = (TERMINO *)malloc(sizeof(TERMINO));
    char c = '1';
    char *pol_aux = (char *)malloc(sizeof(char));
    char *termi = (char *)malloc(sizeof(char));
    char *c_c = (char *)malloc(sizeof(char));
    float c_f;
    char *exp = (char *)malloc(sizeof(char));
    int ep;
    int indice;
    A.nter = 0;
    //<-----INDICES----->
    int i = 0;
    int j;
    printf("Introduzca su polinomio: ");
    fflush(stdin);
    while (c != '\n')
    {
        setbuf(stdin, NULL);
        c = getc(stdin);
        if (c == '\n')
        {
            pol_aux = realloc(pol_aux, (i + 1) * sizeof(char));
            break;
        }
        pol_aux = (char *)realloc(pol_aux, (i + 2) * sizeof(char));
        pol_aux[i] = c;
        i++;
    }
    puts(pol_aux);
    i = 0;
    j = 0;
    for (;; pol_aux = NULL)
    {
        termi = strtok(pol_aux, " ");
        if (termi != NULL)
        {
            A.ter = (TERMINO *)realloc(A.ter, (A.nter + 1) * sizeof(TERMINO));
            A.nter++;
            puts(termi);
            if (find(termi, 'x'))
            {
                printf("Longitud: %ld\n", strlen(termi));
                switch (strlen(termi))
                {
                case 1: // x
                    if (termi[0] == 'x')
                        A.ter[i] = conver(1.0, 1);
                    break;
                case 2:                    //#x -x
                    if (isdigit(termi[0])) //#x
                    {
                        c_c = strncpy(c_c, termi, 1);
                        puts(c_c);
                        c_f = strtof(c_c, NULL);
                        A.ter[i] = conver(c_f, 1);
                    }
                    else if (termi[0] == '-' && termi[1] == 'x')
                        A.ter[i] = conver(-1, 1);
                    break;
                case 3:                  //##x -#x x^#
                    if (termi[0] == 'x') // x^#
                    {
                        indice = findstrc(termi, '^');
                        exp = strcpyrng(termi, indice, 3);
                        ep = strtoi(exp);
                        A.ter[i] = conver(1, ep);
                    }
                    else if (isdigit(termi[0]) || termi[0] == '-') //##x , -#x
                    {
                        c_c = strncpy(c_c, termi, 2);
                        c_f = strtof(c_c, NULL);
                        A.ter[i] = conver(c_f, 1);
                    }
                    break;
                case 4:                  //###x -##x -x^# #x^#
                    if (termi[3] == 'x') //###x -##x
                    {
                        c_c = strncpy(c_c, termi, 3);
                        c_f = strtof(c_c, NULL);
                        A.ter[i] = conver(c_f, 1);
                    }
                    else if (termi[0] == '-') //-x^#
                    {
                        indice = findstrc(termi, '^');
                        exp = strcpyrng(termi, indice, 4);
                        ep = strtoi(exp);
                        A.ter[i] = conver(-1, ep);
                    }
                    else
                    {
                        c_c = strncpy(c_c, termi, findstrc(termi, 'x'));
                        c_f = strtof(c_c, NULL);
                        indice = findstrc(termi, '^');
                        exp = strcpyrng(termi, indice, strlen(termi));
                        ep = strtoi(exp);
                        A.ter[i] = conver(c_f, ep);
                    }
                    break;
                default:                                 //####x    -###x   ##x^#   #x^## x^### -x^##
                    if (termi[strlen(termi) - 1] == 'x') //#...#x   -#..#x
                    {
                        c_c = strncpy(c_c, termi, strlen(termi));
                        c_f = strtof(c_c, NULL);
                        A.ter[i] = conver(c_f, 1);
                    }
                    else if (termi[0] == '-' && termi[1] == 'x') //-x^#..#
                    {
                        indice = findstrc(termi, '^');
                        exp = strcpyrng(termi, indice, strlen(termi));
                        ep = strtoi(exp);
                        A.ter[i] = conver(-1, ep);
                    }
                    else if (termi[0] == 'x')
                    {
                        indice = findstrc(termi, '^');
                        exp = strcpyrng(termi, indice, strlen(termi));
                        ep = strtoi(exp);
                        A.ter[i] = conver(1, ep);
                    }
                    else
                    {
                        c_c = strncpy(c_c, termi, findstrc(termi, 'x'));
                        c_f = strtof(c_c, NULL);
                        indice = findstrc(termi, '^');
                        exp = strcpyrng(termi, indice, strlen(termi));
                        ep = strtoi(exp);
                        A.ter[i] = conver(c_f, ep);
                    }
                    break;
                }
            }
            else
            {
                A.ter[i].exp = 0;
                A.ter[i].coef = strtof(termi, NULL);
            }
        }
        i++;
        if (termi == NULL)
            break;
    }
    bubble_pol(A);
    A.grd = A.ter[0].exp;
    return A;
}
/**
 * @brief Elimina el arreglo de terminos que esta dentro de la estructura POL
 *
 * @param A Polinomio al que borra los terminos
 */
void pol_del(POL A)
{
    free(A.ter);
}
/**
 * @brief Creacion de la memoria
 *
 * @return POL*
 */
POL *initmemory()
{
    POL *d;
    d = (POL *)malloc(10 * sizeof(POL));
    return d;
}
void cpyinmem(POL A)
{
    if (memoria.cont < 10)
    {
        printf("\tcont_%d\n",memoria.cont);
        memoria.polis[memoria.cont] = A;
        memoria.cont++;
        printf("\tcont_%d\n",memoria.cont);
    }
    else
    {
        printf("\tcont_%d\n",memoria.cont);
        memoria.polis = (POL *)realloc(memoria.polis, (memoria.cont + 1) * sizeof(POL));
        memoria.polis[memoria.cont] = A;
        memoria.cont++;
        printf("\tcont_%d\n",memoria.cont);
    }
}
/**
 * @brief Imprime la memoria hasta el momento
 *
 * @param a La memoria que vamos a imprimir
 */
void printMemory(mem a)
{
    printf("-------------Memoria\n");
    for (int i = 0; i < a.cont; i++)
    {
        printf("%d) ", i + 1);
        pol_print(a.polis[i]);
    }
}
/**
 * @brief Recupera de la memoria un polinomio
 *
 * @param a La memoria a la que tenemos que acceder
 * @param h La poscicion en la que esta dicho polinomio
 * @return POL El polinomio recuperado
 */
POL recoMemory(mem a, int h)
{
    POL C;
    C.ter = (TERMINO *)malloc(a.polis[h - 1].nter * sizeof(TERMINO));
    C.nter = a.polis[h - 1].nter;
    for (int i = 0; i < C.nter; i++)
    {
        C.ter[i] = a.polis[h - 1].ter[i];
    }
    C.grd = a.polis[h - 1].grd;
    return C;
}
char *POLtoSTR(POL A)
{
    char *ter = (char *)malloc(sizeof(char));
    char *pol = (char *)malloc(sizeof(char));
    for (int i = 0; i < A.nter; i++)
    {
        if (i == A.nter - 1)
        {
            if (A.ter[i].exp == 0)
                sprintf(ter, "%.4f", A.ter[i].coef);
            else if (A.ter[i].exp == 1)
                sprintf(ter, "%.4fx", A.ter[i].coef);
            else
                sprintf(ter, "%.4fx^%d", A.ter[i].coef, A.ter[i].exp);
            strcat(pol,ter);
        }
        else
        {
            if (A.ter[i].exp == 0)
                sprintf(ter, "%.4f_", A.ter[i].coef);
            else if (A.ter[i].exp == 1)
                sprintf(ter, "%.4fx_", A.ter[i].coef);
            else
                sprintf(ter, "%.4fx^%d_", A.ter[i].coef, A.ter[i].exp);
            strcat(pol,ter);
        }
    }
    free(ter);
    return pol;
}
//<--------ESCRITURA----------->
/**
 * @brief Imprime un polinomio A
 *
 * @param A
 */
void pol_print(POL A)
{
    for (int i = 0; i < A.nter; i++)
    {
        printf("%.4fx^%d  ", A.ter[i].coef, A.ter[i].exp);
    }
    printf("\n");
}
//<--------ORDENAMIENTO-------->
/**
 * @brief Implementacion del metodo de ordenamiento por burbuja para las estrucutras pol
 *
 * @param A Polinomio a ordenar de manera decreciente sus exponentes
 */
void bubble_pol(POL A)
{
    bool follow = true;
    int pasada;
    int j;
    TERMINO aux;
    for (pasada = 0; pasada < A.nter && follow; pasada++)
    {
        follow = false;
        for (j = 0; j < A.nter - 1 - pasada; j++)
        {
            if (A.ter[j].exp < A.ter[j + 1].exp)
            {
                aux = A.ter[j];
                A.ter[j] = A.ter[j + 1];
                A.ter[j + 1] = aux;
                follow = true;
            }
        }
    }
}