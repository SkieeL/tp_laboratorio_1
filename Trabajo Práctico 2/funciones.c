#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

int obtenerEspacioLibre(ePersona listaPersonas[], int len) {
    int i, indexLibre = -1;

    for (i = 0; i < len; i++) {
        if (listaPersonas[i].estadoPer == 0) {
            indexLibre = i;
            break;
        }
    }

    return indexLibre;
}

int buscarPorDNI(ePersona listaPersonas[], int len, int DNI) {
    int i, indexDNI = -1;

    for (i = 0; i < len; i++) {
        if (listaPersonas[i].dniPer == DNI) {
            indexDNI = i;
            break;
        }
    }

    return indexDNI;
}

void agregarPersona(ePersona persona[], int len) {
    int indexLibre;

    indexLibre = obtenerEspacioLibre(persona, len);

    if (indexLibre == -1) {
        printf("ERROR: No se pueden cargar mas personas\n\n");
    }
    else {
        pedirNombre(persona, indexLibre);
        persona[indexLibre].edadPer = pedirEdad();
        persona[indexLibre].dniPer = pedirDNI(persona, len, 1);
        persona[indexLibre].estadoPer = 1;
        printf("Persona agregada exitosamente!\n\n");
    }
}

void pedirNombre(ePersona persona[], int index) {
    char buffer[1024];

    printf("Ingrese el nombre: ");
    fflush(stdin);
    gets(buffer);

    strcpy(persona[index].nombrePer, buffer);

    system("cls");
}

int pedirEdad() {
    int edad;

    printf("Ingrese la edad: ");
    scanf("%d", &edad);

    while(!validarEdad(edad)) {
        system("cls");
        printf("Edad invalida, reingrese: ");
        scanf("%d", &edad);
    }

    system("cls");

    return edad;
}

int pedirDNI(ePersona persona[], int len, int altaPersona) {
    int DNI;

    printf("Ingrese el DNI: ");
    scanf("%d", &DNI);

    while (!validarDNI(DNI)) {
        system("cls");
        printf("DNI invalido, reingrese: ");
        scanf("%d", &DNI);
    }

    while (DNIIngresado(persona, len, DNI) && altaPersona) {
        system("cls");
        printf("El DNI ingresado ya se encuentra en nuestras bases de datos, reingrese: ");
        scanf("%d", &DNI);
    }

    system("cls");

    return DNI;
}

int validarEdad(int edad) {
    if (edad < 1 || edad > 150) {
        return 0;
    }

    return 1;
}

int validarDNI(int DNI) {
    if (DNI < 1000000 || DNI > 99999999) {
        return 0;
    }

    return 1;
}

void eliminarPersona(ePersona personas[], int len) {
    int DNI, index;

    DNI = pedirDNI(personas, len, 0);
    index = buscarPorDNI(personas, len, DNI);

    if (index == -1 || personas[index].estadoPer == 0) {
        printf("ERROR: No se encontro ninguna persona asociada al DNI ingresado\n\n");
    }
    else {
        printf("La persona fue dada de baja exitosamente!\n\n");
        personas[index].estadoPer = 0;
    }
}

int DNIIngresado(ePersona persona[], int len, int DNI) {
    int i;

    for (i = 0; i < len; i++)
    {
        if (DNI == persona[i].dniPer && persona[i].estadoPer)
            return 1;
    }

    return 0;
}

void ordenarPersonas(ePersona personas[], int len) {
    int i, j, cantPersonas = 0;
    ePersona auxPersona;

    // Ordena las personas alfabéticamente.
    for (i = 0; i < len-1; i++)
    {
        for (j = i+1; j < len; j++)
        {
            if (strcmp(personas[i].nombrePer, personas[j].nombrePer) > 0) {
                auxPersona = personas[i];
                personas[i] = personas[j];
                personas[j] = auxPersona;
            }
            else if (strcmp(personas[i].nombrePer, personas[j].nombrePer) == 0) {
                auxPersona = personas[i];
                personas[i] = personas[j];
                personas[j] = auxPersona;
            }
        }
    }

    // Muestra las personas.
    printf("-----------------\n");
    printf("Personas cargadas\n");
    printf("-----------------\n\n");

    for (i = 0; i < len; i++)
    {
        if (personas[i].estadoPer == 1) {
            cantPersonas++;

            if (cantPersonas == 1) {
                printf("ID\tNombre\tEdad\tDNI\n");
            }

            printf("%d\t%s\t%d\t%d\n", cantPersonas, personas[i].nombrePer, personas[i].edadPer, personas[i].dniPer);
        }
    }

    if (!cantPersonas) {
        printf("No hay personas cargadas\n");
    }

    printf("\n");
}

void mostrarGrafico(ePersona personas[], int len) {
    int i, cantMenor18 = 0, cant19a35 = 0, cantMayor35 = 0, numeroMayor;

    // Verifica cuántas personas hay de cada tipo.
    for (i = 0; i < len; i++)
    {
        if (personas[i].estadoPer) {
            if (personas[i].edadPer < 18) {
                cantMenor18++;
            }
            else if (personas[i].edadPer > 18 && personas[i].edadPer < 36) {
                cant19a35++;
            }
            else if (personas[i].edadPer > 35) {
                cantMayor35++;
            }
        }
    }

    // Busca el mayor de las tres opciones.
    numeroMayor = calcularMayor(cantMenor18, cant19a35, cantMayor35);

    // Si no hay personas cargadas, no muestra el gráfico.
    if (numeroMayor == 0) {
        printf("ERROR: No hay personas cargadas.\n\n");
    }
    else {
        for (i = 0; i < numeroMayor; i++)
        {
            printf("%d\t\t%s\t\t%s\t\t%s\n", numeroMayor-i, cantMenor18 >= (numeroMayor-i) ? "#" : "", cant19a35 >= (numeroMayor-i) ? "#" : "", cantMayor35 >= (numeroMayor-i) ? "#" : "");
        }

        printf("Cantidad\tMenor a 18\tEntre 19 y 35\tMayor a 35\n\n");
    }
}

int calcularMayor(int num1, int num2, int num3) {

    if (num1 >= num2 && num1 >= num3) {
        return num1;
    }
    else if (num2 >= num3 && num2 >= num1) {
        return num2;
    }

    return num3;
}
