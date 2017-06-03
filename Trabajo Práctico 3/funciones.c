#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"

int lecturaCreacionArchivo(eMovie** pelicula, int* pMaxRegistros, FILE** archivo) {

    if (*archivo == NULL) {
        *archivo = fopen(RUTA_ARCHIVO_BIN, "wb");

        if (*archivo == NULL) {
            printf("ERROR: No se pudo crear el archivo binario\n\n");
            return 0;
        }

        fwrite(*pelicula, sizeof(eMovie), *pMaxRegistros, *archivo);
    }
    else {
        int indexLibre, cantPeliculas = 0;

        rewind(*archivo);

        while (!feof(*archivo)) {
            indexLibre = obtenerEspacioLibre(pelicula, pMaxRegistros);

            if (indexLibre == -1) {
                return 0;
            }

            fread(*pelicula+indexLibre, sizeof(eMovie), 1, *archivo);

            cantPeliculas++;
        }

    }

    fclose(*archivo);

    return 1;
}

int agregarPelicula(eMovie** pelicula, int* pMaxRegistros, FILE** archivo) {

    int indexLibre;
    FILE* auxArchivo;

    indexLibre = obtenerEspacioLibre(pelicula, pMaxRegistros);

    if (indexLibre == -1) {
        return 0;
    }

    (*pelicula+indexLibre)->estado = 1;

    pedirTitulo(pelicula, indexLibre, 0);
    pedirGenero(pelicula, indexLibre, 0);
    pedirDuracion(pelicula, indexLibre, 0);
    pedirDescripcion(pelicula, indexLibre, 0);
    pedirPuntaje(pelicula, indexLibre, 0);
    pedirLink(pelicula, indexLibre, 0);

    auxArchivo = fopen(RUTA_ARCHIVO_BIN, "wb");

    if (auxArchivo == NULL) {
        printf("ERROR: No se pudo abrir el archivo binario\n\n");
        (*pelicula+indexLibre)->estado = 0;
        return 0;
    }

    *archivo = auxArchivo;

    fwrite(*pelicula, sizeof(eMovie), *pMaxRegistros, *archivo);

    fclose(*archivo);

    printf("Pelicula agredada exitosamente!\n\n");

    return 1;
}

int obtenerEspacioLibre(eMovie** pelicula, int* pMaxRegistros) {

    int i, indexLibre = -1;

    for (i = 0; i < *pMaxRegistros; i++) {

        if ((*pelicula+i)->estado == 1) {
            continue;
        }

        indexLibre = i;
        break;
    }

    if (indexLibre == -1) {
        eMovie* auxPelicula;

        *pMaxRegistros += 5;
        auxPelicula = (eMovie*) realloc(*pelicula, (*pMaxRegistros * sizeof(eMovie)));

        if (auxPelicula == NULL) {
            printf("ERROR: No hay espacio en memoria disponible\n\n");
            return indexLibre;
        }
        else {
            *pelicula = auxPelicula;
            indexLibre = *pMaxRegistros - 5;
        }
    }

    return indexLibre;
}

void pedirTitulo(eMovie** pelicula, int indexLibre, int modificar) {

    char buffer[1024];

    printf("Ingrese el%s titulo: ", modificar ? " nuevo" : "");
    fflush(stdin);
    gets(buffer);

    while (!validarString(buffer)) {
        printf("Titulo invalido, reingrese: ");
        fflush(stdin);
        gets(buffer);
    }

    strcpy((*pelicula+indexLibre)->titulo, buffer);

    system("cls");
}

int validarString(char cadena[]) {
    if (strcmp(cadena, "") == 0) {
        system("cls");
        printf("ERROR: Debe ingresar algun caracter\n");
        return 0;
    }

    int len, i;
    len = strlen(cadena);

    for (i = 0; i < len; i++) {
        if (cadena[i] != ' ') {
            return 1;
        }
    }

    system("cls");
    printf("ERROR: No puede ingresar solo espacios\n");

    return 0;
}

void pedirGenero(eMovie** pelicula, int indexLibre, int modificar) {

    char buffer[1024];

    printf("Ingrese el%s genero: ", modificar ? " nuevo" : "");
    fflush(stdin);
    gets(buffer);

    while (!validarString(buffer)) {
        printf("Genero invalido, reingrese: ");
        fflush(stdin);
        gets(buffer);
    }

    strcpy((*pelicula+indexLibre)->genero, buffer);

    system("cls");
}

void pedirDuracion(eMovie** pelicula, int indexLibre, int modificar) {

    char buffer[1024];
    int num;

    printf("Ingrese la%s duracion (en minutos): ", modificar ? " nueva" : "");
    fflush(stdin);
    gets(buffer);
    num = atoi(buffer);

    while (!validarDuracion(num) || !validarInt(buffer)) {
        system("cls");
        printf("Duracion invalida, reingrese: ");
        fflush(stdin);
        gets(buffer);
        num = atoi(buffer);
    }

    (*pelicula+indexLibre)->duracion = num;

    system("cls");
}

int validarDuracion(int num) {
    if (num < 1 || num > 500) {
        system("cls");
        return 0;
    }

    return 1;
}

int validarInt(char numero[]) {
    int len, i;
    len = strlen(numero);

    for (i = 0; i < len; i++) {
        if (!isdigit(numero[i])) {
            return 0;
        }
    }

    return 1;
}

void pedirDescripcion(eMovie** pelicula, int indexLibre, int modificar) {

    char buffer[1024];

    printf("Ingrese la%s descripcion: ", modificar ? " nueva" : "");
    fflush(stdin);
    gets(buffer);

    while (!validarString(buffer)) {
        printf("Descripcion invalida, reingrese: ");
        fflush(stdin);
        gets(buffer);
    }

    strcpy((*pelicula+indexLibre)->descripcion, buffer);

    system("cls");
}

void pedirPuntaje(eMovie** pelicula, int indexLibre, int modificar) {

    char buffer[1024];
    int num;

    printf("Ingrese el%s puntaje (0-100): ", modificar ? " nuevo" : "");
    fflush(stdin);
    gets(buffer);
    num = atoi(buffer);

    while (!validarPuntaje(num) || !validarInt(buffer)) {
        system("cls");
        printf("Puntaje invalido, reingrese: ");
        fflush(stdin);
        gets(buffer);
        num = atoi(buffer);
    }

    (*pelicula+indexLibre)->puntaje = num;

    system("cls");
}

int validarPuntaje(int num) {
    if (num < 1 || num > 100) {
        system("cls");
        return 0;
    }

    return 1;
}

void pedirLink(eMovie** pelicula, int indexLibre, int modificar) {

    char buffer[1024];

    printf("Ingrese el%s link de la imagen: ", modificar ? " nuevo" : "");
    fflush(stdin);
    gets(buffer);

    while (!validarString(buffer)) {
        printf("Link invalido, reingrese: ");
        fflush(stdin);
        gets(buffer);
    }

    strcpy((*pelicula+indexLibre)->linkImagen, buffer);

    system("cls");
}

int eliminarPelicula(eMovie** pelicula, int maxRegistros, FILE** archivo) {

    char buffer[1024];
    FILE* auxArchivo;
    int i, cantPeliculas = 0;

    printf("------------------\n");
    printf("Peliculas cargadas\n");
    printf("------------------\n\n");

    printf("Numero\tTitulo\n");

    for (i = 0; i < maxRegistros; i++) {
        if ((*pelicula+i)->estado == 1) {

            cantPeliculas++;
            printf("%d\t%s\n", cantPeliculas, (*pelicula+i)->titulo);
        }
    }

    if (!cantPeliculas) {
        system("cls");

        printf("No hay peliculas cargadas\n\n");
        return 0;
    }

    printf("\n");

    printf("Ingrese el titulo de la pelicula a eliminar: ");
    fflush(stdin);
    gets(buffer);

    for (i = 0; i < maxRegistros; i++) {
        if (strcmp((*pelicula+i)->titulo, buffer) == 0 && (*pelicula+i)->estado == 1) {
            (*pelicula+i)->estado = 0;

            auxArchivo = fopen(RUTA_ARCHIVO_BIN, "wb");

            if (auxArchivo == NULL) {
                printf("ERROR: No se pudo abrir el archivo");
                return 0;
            }

            *archivo = auxArchivo;

            fwrite(*pelicula, sizeof(eMovie), maxRegistros, *archivo);
            fclose(*archivo);

            system("cls");
            printf("Pelicula borrada exitosamente!\n\n");
            return 1;
        }
    }

    system("cls");
    printf("No se pudo encontrar la pelicula a eliminar\n\n");

    return 0;
}

int modificarPelicula(eMovie** pelicula, int maxRegistros, FILE** archivo) {

    char buffer[1024];
    FILE* auxArchivo;
    int i, cantPeliculas = 0;

    printf("------------------\n");
    printf("Peliculas cargadas\n");
    printf("------------------\n\n");

    printf("Numero\tTitulo\n");

    for (i = 0; i < maxRegistros; i++) {
        if ((*pelicula+i)->estado == 1) {

            cantPeliculas++;
            printf("%d\t%s\n", cantPeliculas, (*pelicula+i)->titulo);
        }
    }

    if (!cantPeliculas) {
        system("cls");

        printf("No hay peliculas cargadas\n\n");
        return 0;
    }

    printf("\n");

    printf("Ingrese el titulo de la pelicula a modificar: ");
    fflush(stdin);
    gets(buffer);

    for (i = 0; i < maxRegistros; i++) {
        if (strcmp((*pelicula+i)->titulo, buffer) == 0 && (*pelicula+i)->estado == 1) {
            system("cls");
            pedirTitulo(pelicula, i, 1);
            pedirGenero(pelicula, i, 1);
            pedirDuracion(pelicula, i, 1);
            pedirDescripcion(pelicula, i, 1);
            pedirPuntaje(pelicula, i, 1);
            pedirLink(pelicula, i, 1);

            auxArchivo = fopen(RUTA_ARCHIVO_BIN, "wb");

            if (auxArchivo == NULL) {
                printf("ERROR: No se pudo abrir el archivo");
                return 0;
            }

            *archivo = auxArchivo;

            fwrite(*pelicula, sizeof(eMovie), maxRegistros, *archivo);
            fclose(*archivo);

            system("cls");
            printf("Pelicula modificada exitosamente!\n\n");
            return 1;
        }
    }

    system("cls");
    printf("No se pudo encontrar la pelicula a modificar\n\n");

    return 0;
}

int generarPagina(eMovie** pelicula, int maxRegistros, char nombre_file[]) {
    FILE* archivoIndex;
    int i;

    archivoIndex = fopen(nombre_file, "w");

    if (archivoIndex == NULL) {
        printf("ERROR: No se pudo generar el archivo HTML\n\n");
        return 0;
    }

    fprintf(archivoIndex, "<html><head><title>Lista de peliculas</title></head><body>");

    for (i = 0; i < maxRegistros; i++) {
        if ((*pelicula+i)->estado == 0) {
            continue;
        }

        fprintf(archivoIndex,   "<a href='#'>\
                                    <img src='%s'>\
                                </a>\
                                <h3>\
                                    <a href='#'>%s</a>\
                                </h3>\
                                <ul>\
                                    <li>Genero: %s</li>\
                                    <li>Puntaje: %d</li>\
                                    <li>Duracion: %d</li>\
                                </ul>\
                                <p>%s</p>", (*pelicula+i)->linkImagen, (*pelicula+i)->titulo, (*pelicula+i)->genero, (*pelicula+i)->puntaje, (*pelicula+i)->duracion, (*pelicula+i)->descripcion);
    }

    fprintf(archivoIndex, "</body></html>");

    fclose(archivoIndex);

    printf("Pagina web generada exitosamente!\n\n");

    return 1;
}
