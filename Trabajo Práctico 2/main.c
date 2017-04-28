#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main()
{
    char flagContinuar = 's';
    int opcion = 0;

    printf("Bienvenido/a!\n\n");

    while(flagContinuar == 's')
    {

        printf("1. Agregar persona\n");
        printf("2. Borrar persona\n");
        printf("3. Imprimir lista ordenada por nombre\n");
        printf("4. Imprimir grafico de edades\n");
        printf("5. Salir\n\n");

        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        system("cls");

        switch(opcion)
        {
            case 1:
                agregarPersona(contenedorPersonas, MAX_REGISTROS);
                break;
            case 2:
                eliminarPersona(contenedorPersonas, MAX_REGISTROS);
                break;
            case 3:
                ordenarPersonas(contenedorPersonas, MAX_REGISTROS);
                break;
            case 4:
                mostrarGrafico(contenedorPersonas, MAX_REGISTROS);
                break;
            case 5:
                printf("Hasta pronto!\n");
                flagContinuar = 'n';
                break;
            default:
                printf("ERROR: Opcion invalida\n\n");
                break;
        }
    }

    return 0;
}
