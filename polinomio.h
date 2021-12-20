#ifndef __POLINOMIO_H__
#define __POLINOMIO_H__
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
/* struct cadenas
{
    int cont; //Numero de cadenas
    char **cdn;
};
typedef struct cadenas CADENAS;
CADENAS almacen; */
struct _termino
{
    float coef;
    int exp;
    //char variable;
};
typedef struct _termino TERMINO;
struct polinomio
{
    int nter;
    int grd;
    TERMINO *ter;
};
typedef struct polinomio POL;
struct _mpol
{
    int cont; //Indice en la que vamos a guardar el polinomio
    POL *polis; //[p1,p2,p3,p4,....]
};
typedef struct _mpol mem; 
mem memoria;
struct division
{
    POL cociente;
    POL residuo;
};
typedef struct division DIV;


//<-------ARCHIVOS--------->
FILE *infile;
FILE *outfile;
FILE *registro;
void open_in_file(char *);
void open_out_file(char*);
void open_registro(char*);
void close_file(FILE *f);
POL fread_pol(FILE*);
void fwrite_pol(int);
//<-------AUXILIARES-------->
int pot(int base, int expo);
int strtoi(char *str);
char*strcpyrng(char*,int a,int b);
bool find(char*,char);
int findstrc(char *str, char c);
void menu();
void init();
//<-------------OPERACIONES------------>
POL del_zero(POL);
POL add(POL,POL);
POL sub(POL,POL);
POL esc_pol(POL,double);
POL pol_prod(POL,POL);
POL pol_div(POL,POL);
DIV div_larga(POL,POL);
POL polcpy(POL);
POL cpy(POL);
TERMINO conver(float,int);
//<-------------MEMORIA---------------->
POL pol_creat();
void pol_del(POL A);
POL* initmemory();
void cpyinmem(POL A);
/* void cpy_in_almacen(char*);
 */void printMemory(mem);
POL recoMemory(mem,int);
/* void cdnprint();
 */char* POLtoSTR(POL);
//<--------ESCRITURA----------->
void pol_print(POL A);
//<--------ORDENAMIENTO-------->
void bubble_sort(int a[], int n);
void bubble_pol(POL);
#endif