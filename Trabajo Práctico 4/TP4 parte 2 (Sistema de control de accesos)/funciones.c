#include "funciones.h"
#include "ArrayList.h"

void title() {
    printf("Sistema de control de accesos\n\n");
}

int cargarAgente(ArrayList* agentesCargados, ArrayList* agentesFueraEdificio, eAgente* pElementAux, FILE* archivo, char ruta[]) {
    eAgente* pElement = (eAgente*) malloc(sizeof(eAgente));

    if (pElement == NULL) {
        printf("ERROR: No se pudo generar espacio en memoria");
        return 0;
    }

    pElement = pedirNombre(pElement, 0);
    pElement = pedirApellido(pElement, 0);
    title();
    pElement->dni = pedirDNI();
    pElement->enEdificio = 0;

    agentesCargados->add(agentesCargados, pElement);
    agentesFueraEdificio->add(agentesFueraEdificio, pElement);

    if (cargaArchivo(agentesCargados, pElementAux, archivo, ruta) == 0) {
        return 0;
    }

    title();
    printf("Agente %s %s cargado exitosamente!\n\n", pElement->nombre, pElement->apellido);

    return 1;
}

int modificarAgente(ArrayList* agentesCargados, ArrayList* agentesEnEdificio, ArrayList* agentesFueraEdificio, eAgente* pElement, FILE* archivo, char ruta[]) {
    if (agentesCargados->isEmpty(agentesCargados) == 0) {
        title();
        listarArrayList(agentesCargados, pElement);
        printf("\n");

        int dni, i, flagFallo = 1;
        dni = pedirDNI();

        for (i = 0; i < agentesCargados->len(agentesCargados); i++) {
            pElement = (eAgente*) agentesCargados->get(agentesCargados, i);

            if (dni == pElement->dni) {
                char auxNombre[50];
                char auxApellido[50];
                int index = agentesCargados->indexOf(agentesCargados, pElement);

                flagFallo = 0;

                strcpy(auxNombre, pElement->nombre);
                strcpy(auxApellido, pElement->apellido);

                pElement = pedirNombre(pElement, 1);
                pElement = pedirApellido(pElement, 1);

                agentesCargados->set(agentesCargados, index, pElement);

                if (agentesFueraEdificio->contains(agentesFueraEdificio, pElement) == 1) {
                    agentesFueraEdificio->set(agentesFueraEdificio, agentesFueraEdificio->indexOf(agentesFueraEdificio, pElement), pElement);
                }
                else {
                    agentesEnEdificio->set(agentesEnEdificio, agentesEnEdificio->indexOf(agentesEnEdificio, pElement), pElement);
                }

                if (cargaArchivo(agentesCargados, pElement, archivo, ruta) == 0)
                    return 0;

                title();
                printf("Agente %d modificado!\n", pElement->dni);
                printf("Nombre: %s -> %s\n", auxNombre, pElement->nombre);
                printf("Apellido: %s -> %s\n\n", auxApellido, pElement->apellido);
            }
        }

        if (flagFallo) {
            system("cls");
            title();
            printf("El agente indicado no se encuentra cargado en el sistema\n\n");
        }
    }
    else {
        system("cls");
        title();
        printf("No hay agentes cargados en el sistema\n\n");
    }

    return 1;
}

int eliminarAgente(ArrayList* agentesCargados, ArrayList* agentesEnEdificio, ArrayList* agentesFueraEdificio, eAgente* pElement, FILE* archivo, char ruta[]) {
    if (agentesCargados->isEmpty(agentesCargados) == 0) {
        title();
        listarArrayList(agentesCargados, pElement);
        printf("\n");

        int dni, i, flagFallo = 1;
        dni = pedirDNI();

        for (i = 0; i < agentesCargados->len(agentesCargados); i++) {
            pElement = (eAgente*) agentesCargados->get(agentesCargados, i);

            if (dni == pElement->dni) {
                int index = agentesCargados->indexOf(agentesCargados, pElement);

                flagFallo = 0;

                pElement = agentesCargados->pop(agentesCargados, index);

                if (agentesFueraEdificio->contains(agentesFueraEdificio, pElement) == 1) {
                    pElement = agentesFueraEdificio->pop(agentesFueraEdificio, agentesFueraEdificio->indexOf(agentesFueraEdificio, pElement));
                }
                else {
                    pElement = agentesEnEdificio->pop(agentesEnEdificio, agentesEnEdificio->indexOf(agentesEnEdificio, pElement));
                }

                if (cargaArchivo(agentesCargados, pElement, archivo, ruta) == 0)
                    return 0;

                title();
                printf("Agente %s %s eliminado!\n\n", pElement->nombre, pElement->apellido);
            }
        }

        if (flagFallo) {
            system("cls");
            title();
            printf("El agente indicado no se encuentra cargado en el sistema\n\n");
        }
    }
    else {
        system("cls");
        title();
        printf("No hay agentes cargados en el sistema\n\n");
    }

    return 1;
}

int listarArrayList(ArrayList* pList, eAgente* pElement) {
    int i;

    for (i = 0; i < pList->len(pList); i++) {
        pElement = (eAgente*) pList->get(pList, i);
        printf("%d. %d\t%s %s\n", i+1, pElement->dni, pElement->nombre, pElement->apellido);
    }

    if (pList->len(pList) > 0)
        return 1;

    return 0;
}

eAgente* pedirNombre(eAgente* pElement, int nuevo) {
    char buffer[1024];

    title();
    printf("Ingrese el %snombre del agente: ", nuevo ? "nuevo " : "");
    fflush(stdin);
    gets(buffer);

    while (!validarString(buffer)) {
        system("cls");
        title();
        printf("Nombre invalido, reingrese: ");
        fflush(stdin);
        gets(buffer);
    }

    strcpy(pElement->nombre, buffer);

    system("cls");

    return pElement;
}

eAgente* pedirApellido(eAgente* pElement, int nuevo) {
    char buffer[1024];

    title();
    printf("Ingrese el %sapellido del agente: ", nuevo ? "nuevo " : "");
    fflush(stdin);
    gets(buffer);

    while (!validarString(buffer)) {
        system("cls");
        title();
        printf("Apellido invalido, reingrese: ");
        fflush(stdin);
        gets(buffer);
    }

    strcpy(pElement->apellido, buffer);

    system("cls");

    return pElement;
}

int validarString(char string[]) {
    if (strcmp(string, "") == 0)
        return 0;

    int len, i;
    len = strlen(string);

    for (i = 0; i < len; i++) {
        if (string[i] != ' ')
            return 1;
    }

    return 0;
}

int pedirDNI() {
    char buffer[1024];
    int num;

    printf("Ingrese el DNI del agente: ");
    fflush(stdin);
    gets(buffer);
    num = atoi(buffer);

    while (!validarRangoEntero(num, 1000000, 100000000) || !validarInt(buffer)) {
        system("cls");
        title();
        printf("DNI invalido, reingrese: ");
        fflush(stdin);
        gets(buffer);
        num = atoi(buffer);
    }

    system("cls");

    return num;
}

int validarRangoEntero(int num, int min, int max) {
    if (num < min || num > max)
        return 0;

    return 1;
}

int validarInt(char numero[]) {
    int len, i;
    len = strlen(numero);

    for (i = 0; i < len; i++) {
        if (!isdigit(numero[i]))
            return 0;
    }

    return 1;
}

int registrarIngreso(ArrayList* agentesCargados, ArrayList* registroIngresos, ArrayList* agentesEnEdificio, ArrayList* agentesFueraEdificio, eAgente* pElement, FILE* archivo, char ruta[], FILE* archivo2, char ruta2[]) {
    int dni, i, flagFallo = 1;
    title();
    dni = pedirDNI();

    if (agentesCargados->isEmpty(agentesCargados) == 0) {
        for (i = 0; i < agentesCargados->len(agentesCargados); i++) {
             pElement = (eAgente*) agentesCargados->get(agentesCargados, i);

            if (dni == pElement->dni) {
                flagFallo = 0;

                if (agentesEnEdificio->contains(agentesEnEdificio, pElement) == 0) {
                    pElement->enEdificio = 1;
                    agentesCargados->set(agentesCargados, i, pElement);
                    registroIngresos->add(registroIngresos, pElement);
                    agentesEnEdificio->push(agentesEnEdificio, 0, agentesFueraEdificio->pop(agentesFueraEdificio, i));
                    system("cls");
                    title();

                    if (cargaArchivo(registroIngresos, pElement, archivo, ruta) == 0)
                        return 0;

                    if (cargaArchivo(agentesCargados, pElement, archivo2, ruta2) == 0)
                        return 0;

                    printf("Se registro el ingreso de %s %s\n\n", pElement->nombre, pElement->apellido);
                    break;
                }
                else {
                    system("cls");
                    title();
                    printf("El agente indicado ya se encuentra dentro del edificio, verifique el DNI\n\n");
                    break;
                }
            }
        }
    }

    if (flagFallo) {
        system("cls");
        title();
        printf("El agente indicado no se encuentra cargado en el sistema\n\n");
    }

    return 1;
}

int registrarEgreso(ArrayList* agentesCargados, ArrayList* registroEgresos, ArrayList* agentesEnEdificio, ArrayList* agentesFueraEdificio, eAgente* pElement, FILE* archivo, char ruta[], FILE* archivo2, char ruta2[]) {
    int dni, i, flagFallo = 1;
    title();
    dni = pedirDNI();

    if (agentesCargados->isEmpty(agentesCargados) == 0) {
        for (i = 0; i < agentesCargados->len(agentesCargados); i++) {
            pElement = (eAgente*) agentesCargados->get(agentesCargados, i);

            if (dni == pElement->dni) {
                flagFallo = 0;

                if (agentesFueraEdificio->contains(agentesFueraEdificio, pElement) == 0) {
                    pElement->enEdificio = 0;
                    agentesCargados->set(agentesCargados, i, pElement);
                    registroEgresos->add(registroEgresos, pElement);
                    agentesFueraEdificio->push(agentesFueraEdificio, 0, agentesEnEdificio->pop(agentesEnEdificio, i));
                    system("cls");
                    title();

                    if (cargaArchivo(registroEgresos, pElement, archivo, ruta) == 0)
                        return 0;

                    if (cargaArchivo(agentesCargados, pElement, archivo2, ruta2) == 0)
                        return 0;

                    printf("Se registro el egreso de %s %s\n\n", pElement->nombre, pElement->apellido);
                    break;
                }
                else {
                    system("cls");
                    title();
                    printf("El agente indicado no se encuentra dentro del edificio, verifique el DNI\n\n");
                    break;
                }
            }
        }
    }

    if (flagFallo) {
        system("cls");
        title();
        printf("El agente indicado no se encuentra cargado en el sistema\n\n");
    }

    return 1;
}

int comparaAgenteNoAp(eAgente* Agente1, eAgente* Agente2) {
    if (strcmp(Agente1->nombre, Agente2->nombre) > 0)
        return 1;
    else if (strcmp(Agente1->nombre, Agente2->nombre) < 0)
        return -1;
    else {
        if (strcmp(Agente1->apellido, Agente2->apellido) > 0)
            return 1;
        else if (strcmp(Agente1->apellido, Agente2->apellido) < 0)
            return -1;
    }

    return 0;
}

void mostrarAgentes(ArrayList* pList, eAgente* pElement, int tipoDeMuestreo) {
    title();
    printf("AGENTES %s\n\n", tipoDeMuestreo ? "CARGADOS" : "EN EL EDIFICIO");

    if (pList->isEmpty(pList) == 0) {
        ArrayList* pListAux = pList->clone(pList);
        pListAux->sort(pListAux, comparaAgenteNoAp, 1);
        listarArrayList(pListAux, pElement);
        pListAux->deleteArrayList(pListAux);
        printf("\n");
    }
    else
        printf("No hay agentes %s\n\n", tipoDeMuestreo ? "cargados" : "en el edificio");
}

void mostrarRegistros(ArrayList* pList, eAgente* pElement, int tipoDeMuestreo, int ultimos10) {
    title();
    printf("%s %s\n\n", ultimos10 ? "ULTIMOS 10" : "TODOS LOS", tipoDeMuestreo ? "INGRESOS" : "EGRESOS");

    if (pList->isEmpty(pList) == 0) {
        if (pList->len(pList) <= 10 || !ultimos10)
            listarArrayList(pList, pElement);
        else {
            ArrayList* pListAux = pList->subList(pList, pList->len(pList)-10, pList->len(pList));
            listarArrayList(pListAux, pElement);
            pListAux->deleteArrayList(pListAux);
        }

        printf("\n");
    }
    else
        printf("No hay %s registrados\n\n", tipoDeMuestreo ? "ingresos" : "egresos");
}

void limpiarRegistros(ArrayList* registroIngresos, ArrayList* registroEgresos, FILE* archivo1, FILE* archivo2, char ruta1[], char ruta2[]) {
    title();
    if (registroIngresos->isEmpty(registroIngresos) == 0 || registroEgresos->isEmpty(registroEgresos) == 0) {
        registroIngresos->clear(registroIngresos);
        registroEgresos->clear(registroEgresos);

        archivo1 = fopen(ruta1, "wb");
        archivo2 = fopen(ruta2, "wb");

        fclose(archivo1);
        fclose(archivo2);

        printf("Los registros de ingresos y egresos fueron eliminados!\n\n");
    }
    else
        printf("No hay registros de ingresos ni egresos\n\n");
}

int lecturaCreacionArchivoAg(ArrayList* agentesCargados, ArrayList* agentesEnEdificio, ArrayList* agentesFueraEdificio, FILE* archivo, char ruta[]) {
    if (archivo == NULL) {
        archivo = fopen(ruta, "wb");

        if (archivo == NULL) {
            printf("ERROR: No se pudo crear el archivo binario\n");
            return 0;
        }
    }
    else {
        rewind(archivo);

        while (!feof(archivo)) {
            eAgente* pElement = (eAgente*) malloc(sizeof(eAgente));

            if (pElement == NULL) {
                printf("ERROR: No se pudo asignar espacio en memoria\n");
                return 0;
            }

            fread(pElement, sizeof(eAgente), 1, archivo);

            // Bugfix, evita que traiga basura.
            if (pElement->dni >= 1000000 && pElement->dni <= 100000000) {
                agentesCargados->add(agentesCargados, pElement);

                if (pElement->enEdificio)
                    agentesEnEdificio->add(agentesEnEdificio, pElement);
                else
                    agentesFueraEdificio->add(agentesFueraEdificio, pElement);
            }
        }
    }

    fclose(archivo);

    return 1;
}

int lecturaCreacionArchivoReg(ArrayList* pList, ArrayList* agentesCargados, FILE* archivo, char ruta[]) {
    if (archivo == NULL) {
        archivo = fopen(ruta, "wb");

        if (archivo == NULL) {
            printf("ERROR: No se pudo crear el archivo binario\n");
            return 0;
        }
    }
    else {
        rewind(archivo);

        while (!feof(archivo)) {
            eAgente* pElement = (eAgente*) malloc(sizeof(eAgente));

            if (pElement == NULL) {
                printf("ERROR: No se pudo asignar espacio en memoria\n");
                return 0;
            }

            fread(pElement, sizeof(eAgente), 1, archivo);

            // Bugfix, evita que traiga basura.
            if (agentesCargados->contains(agentesCargados, pElement))
                pList->add(pList, pElement);
        }
    }

    fclose(archivo);

    return 1;
}

int cargaArchivo(ArrayList* pList, eAgente* pElement, FILE* archivo, char ruta[]) {
    FILE* auxArchivo = fopen(ruta, "wb");

    if (auxArchivo == NULL) {
        printf("ERROR: No se pudo abrir el archivo binario\n");
        return 0;
    }

    archivo = auxArchivo;
    int i;

    for (i = 0; i < pList->len(pList); i++) {
        pElement = (eAgente*) pList->get(pList, i);
        fwrite(pElement, sizeof(eAgente), 1, archivo);
    }

    fclose(archivo);

    return 1;
}
