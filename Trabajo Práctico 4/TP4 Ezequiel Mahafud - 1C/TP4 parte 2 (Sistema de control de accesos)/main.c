#include "ArrayList.h"
#include "funciones.h"

int main() {
    int opcion;
    char flagContinue = 's';
    ArrayList* agentesCargados = al_newArrayList();
    ArrayList* agentesEnEdificio = al_newArrayList();
    ArrayList* agentesFueraEdificio = al_newArrayList();
    ArrayList* registroIngresos = al_newArrayList();
    ArrayList* registroEgresos = al_newArrayList();
    eAgente* pElementAux = (eAgente*) malloc(sizeof(eAgente));
    FILE* archivoAgentes = fopen(RUTA_ARCHIVO_AGENTES, "rb");
    FILE* archivoIngresos = fopen(RUTA_ARCHIVO_INGRESOS, "rb");
    FILE* archivoEgresos = fopen(RUTA_ARCHIVO_EGRESOS, "rb");

    if (agentesCargados == NULL || agentesEnEdificio == NULL || agentesFueraEdificio == NULL || registroIngresos == NULL || registroEgresos == NULL || pElementAux == NULL) {
        printf("ERROR: No se pudo asignar espacio en memoria");
        flagContinue = 'n';
    }
    else if (lecturaCreacionArchivoAg(agentesCargados, agentesEnEdificio, agentesFueraEdificio, archivoAgentes, RUTA_ARCHIVO_AGENTES) == 0 || lecturaCreacionArchivoReg(registroIngresos, agentesCargados, archivoIngresos, RUTA_ARCHIVO_INGRESOS) == 0 ||
             lecturaCreacionArchivoReg(registroEgresos, agentesCargados, archivoEgresos, RUTA_ARCHIVO_EGRESOS) == 0) {
        flagContinue = 'n';
    }

    title();

    while (flagContinue == 's') {

        printf("1. Registrar ingreso\n");
        printf("2. Registrar egreso\n\n");
        printf("3. Cargar agente\n");
        printf("4. Modificar agente\n");
        printf("5. Eliminar agente\n\n");
        printf("6. Visualizar agentes cargados\n");
        printf("7. Visualizar agentes en el edificio\n\n");
        printf("8. Visualizar ultimos 10 ingresos\n");
        printf("9. Visualizar ultimos 10 egresos\n");
        printf("10. Visualizar todos los ingresos\n");
        printf("11. Visualizar todos los egresos\n");
        printf("12. Limpiar registros de ingresos/egresos\n\n");
        printf("13. Salir\n\n");

        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        system("cls");

        switch (opcion)
        {
            case 1:
                if (registrarIngreso(agentesCargados, registroIngresos, agentesEnEdificio, agentesFueraEdificio, pElementAux, archivoIngresos, RUTA_ARCHIVO_INGRESOS, archivoAgentes, RUTA_ARCHIVO_AGENTES) == 0)
                    flagContinue = 'n';
                break;
            case 2:
                if (registrarEgreso(agentesCargados, registroEgresos, agentesEnEdificio, agentesFueraEdificio, pElementAux, archivoEgresos, RUTA_ARCHIVO_EGRESOS, archivoAgentes, RUTA_ARCHIVO_AGENTES) == 0)
                    flagContinue = 'n';
                break;
            case 3:
                if (cargarAgente(agentesCargados, agentesFueraEdificio, pElementAux, archivoAgentes, RUTA_ARCHIVO_AGENTES) == 0)
                    flagContinue = 'n';
                break;
            case 4:
                if (modificarAgente(agentesCargados, agentesEnEdificio, agentesFueraEdificio, pElementAux, archivoAgentes, RUTA_ARCHIVO_AGENTES) == 0)
                    flagContinue = 'n';
                break;
            case 5:
                if (eliminarAgente(agentesCargados, agentesEnEdificio, agentesFueraEdificio, pElementAux, archivoAgentes, RUTA_ARCHIVO_AGENTES) == 0)
                    flagContinue = 'n';
                break;
            case 6:
                mostrarAgentes(agentesCargados, pElementAux, 1);
                break;
            case 7:
                mostrarAgentes(agentesEnEdificio, pElementAux, 0);
                break;
            case 8:
                mostrarRegistros(registroIngresos, pElementAux, 1, 1);
                break;
            case 9:
                mostrarRegistros(registroEgresos, pElementAux, 0, 1);
                break;
            case 10:
                mostrarRegistros(registroIngresos, pElementAux, 1, 0);
                break;
            case 11:
                mostrarRegistros(registroEgresos, pElementAux, 0, 0);
                break;
            case 12:
                limpiarRegistros(registroIngresos, registroEgresos, archivoIngresos, archivoEgresos, RUTA_ARCHIVO_INGRESOS, RUTA_ARCHIVO_EGRESOS);
                break;
            case 13:
                printf("Hasta pronto!\n");
                flagContinue = 'n';
                break;
            default:
                title();
                printf("ERROR: Opcion invalida\n\n");
                break;
        }
    }

    return 0;
}
