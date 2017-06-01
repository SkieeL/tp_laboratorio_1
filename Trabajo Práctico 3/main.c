#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

int main()
{
    char flagContinuar = 's';
    int opcion, retorno, maxRegistros = REGISTROS_INICIALES;
    FILE* archivoBinario;
    eMovie* contenedorPeliculas;

    contenedorPeliculas = (eMovie*) calloc(maxRegistros, sizeof(eMovie));
    archivoBinario = fopen(RUTA_ARCHIVO_BIN, "rb");

    retorno = lecturaCreacionArchivo(contenedorPeliculas, maxRegistros, archivoBinario);

    if (!retorno) {
        exit(1);
    }

    printf("Bienvenido/a!\n\n");

    while(flagContinuar == 's')
    {
        printf("1. Agregar pelicula\n");
        printf("2. Borrar pelicula\n");
        printf("3. Modificar pelicula\n");
        printf("4. Generar pagina web\n");
        printf("5. Salir\n\n");

        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        system("cls");

        switch(opcion)
        {
            case 1:
                agregarPelicula(contenedorPeliculas, maxRegistros, archivoBinario);
                break;
            case 2:
                borrarPelicula(contenedorPeliculas, maxRegistros, archivoBinario);
                break;
            case 3:
                modificarPelicula(contenedorPeliculas, maxRegistros, archivoBinario);
                break;
            case 4:
                generarPagina(contenedorPeliculas, maxRegistros, RUTA_ARCHIVO_HTM);
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
