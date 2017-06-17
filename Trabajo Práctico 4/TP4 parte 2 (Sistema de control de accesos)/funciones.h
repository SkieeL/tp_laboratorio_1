#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ArrayList.h"

#define RUTA_ARCHIVO_AGENTES "agentes.dat"
#define RUTA_ARCHIVO_INGRESOS "ingresos.dat"
#define RUTA_ARCHIVO_EGRESOS "egresos.dat"

struct {
    char nombre[50];
    char apellido[50];
    int dni;
    int enEdificio;
} typedef eAgente;

/**
 * Muestra el título del programa.
 */
void title();

/**
 * Carga un agente en el sistema.
 * @param ArrayList de agentes cargados.
 * @param ArrayList de agentes que se encuentran fuera del edificio.
 * @param Puntero auxiliar a estructura de agentes.
 * @param Archivo contenedor de agentes cargados.
 * @param Ruta del archivo contenedor de agentes cargados.
 * @return Retorna 1 en caso de exito, 0 en caso de error.
 */
int cargarAgente(ArrayList* agentesCargados, ArrayList* agentesFueraEdificio, eAgente* pElementAux, FILE* archivo, char ruta[]);

/**
 * Modifica el nombre y apellido de un agente en el sistema.
 * @param ArrayList de agentes cargados.
 * @param ArrayList de agentes que se encuentran en el edificio.
 * @param ArrayList de agentes que se encuentran fuera del edificio.
 * @param Puntero auxiliar a estructura de agentes.
 * @param Archivo contenedor de agentes cargados.
 * @param Ruta del archivo contenedor de agentes cargados.
 * @return Retorna 1 en caso de exito, 0 en caso de error.
 */
int modificarAgente(ArrayList* agentesCargados, ArrayList* agentesEnEdificio, ArrayList* agentesFueraEdificio, eAgente* pElement, FILE* archivo, char ruta[]);

/**
 * Elimina un agente del sistema.
 * @param ArrayList de agentes cargados.
 * @param ArrayList de agentes que se encuentran en el edificio.
 * @param ArrayList de agentes que se encuentran fuera del edificio.
 * @param Puntero auxiliar a estructura de agentes.
 * @param Archivo contenedor de agentes cargados.
 * @param Ruta del archivo contenedor de agentes cargados.
 * @return Retorna 1 en caso de exito, 0 en caso de error.
 */
int eliminarAgente(ArrayList* agentesCargados, ArrayList* agentesEnEdificio, ArrayList* agentesFueraEdificio, eAgente* pElement, FILE* archivo, char ruta[]);

/**
 * Muestra el contenido de un ArrayList de agentes.
 * @param ArrayList a mostrar.
 * @param Puntero auxiliar a estructura de agentes.
 * @return Retorna 1 en caso de exito, 0 en caso de que el ArrayList se encuentre vacío.
 */
int listarArrayList(ArrayList* pList, eAgente* pElement);

/**
 * Solicita el ingreso del nombre del agente.
 * @param Puntero al elemento donde se cargará el nombre.
 * @param Flag: Si llega en 1 agrega la palabra "nuevo" a la leyenda que solicita el ingreso del nombre.
 * @return Retorna el puntero del agente con el nombre cargado.
 */
eAgente* pedirNombre(eAgente* pElement, int nuevo);

/**
 * Solicita el ingreso del apellido del agente.
 * @param Puntero al elemento donde se cargará el apellido.
 * @param Flag: Si llega en 1 agrega la palabra "nuevo" a la leyenda que solicita el ingreso del apellido.
 * @return Retorna el puntero del agente con el apellido cargado.
 */
eAgente* pedirApellido(eAgente* pElement, int nuevo);

/**
 * Valida si un string llega vacío o sólo contiene espacios.
 * @param String a validar.
 * @return Retorna 1 en caso de éxito, 0 en caso de error.
 */
int validarString(char string[]);

/**
 * Solicita el ingreso de un DNI y valida que se ingresen sólo números en un rango de entre 1.000.000 y 100.000.000.
 * @return Retorna el DNI validado.
 */
int pedirDNI();

/**
 * Valida que un número Int se encuentre entre determinado rango de números.
 * @param Número a validar.
 * @param Número mínimo.
 * @param Número máximo.
 * @return Retorna el número validado.
 */
int validarRangoEntero(int num, int min, int max);

/**
 * Valida que una cadena contenga sólo números.
 * @param Cadena a validar.
 * @return Retorna 1 en caso de éxito, 0 en caso de error.
 */
int validarInt(char numero[]);

/**
 * Registra el ingreso de un agente al edificio.
 * @param ArrayList de agentes cargados.
 * @param ArrayList de registro de ingresos.
 * @param ArrayList de agentes que se encuentran en el edificio.
 * @param ArrayList de agentes que se encuentran fuera del edificio.
 * @param Puntero auxiliar a estructura de agentes.
 * @param Archivo contenedor de registros de ingreso.
 * @param Ruta del archivo contenedor de registros de ingreso.
 * @param Archivo contenedor de agentes cargados.
 * @param Ruta del archivo contenedor de agentes cargados.
 * @return Retorna 1 en caso de exito, 0 en caso de error.
 */
int registrarIngreso(ArrayList* agentesCargados, ArrayList* registroIngresos, ArrayList* agentesEnEdificio, ArrayList* agentesFueraEdificio, eAgente* pElement, FILE* archivo, char ruta[], FILE* archivo2, char ruta2[]);

/**
 * Registra el egreso de un agente del edificio.
 * @param ArrayList de agentes cargados.
 * @param ArrayList de registro de egresos.
 * @param ArrayList de agentes que se encuentran en el edificio.
 * @param ArrayList de agentes que se encuentran fuera del edificio.
 * @param Puntero auxiliar a estructura de agentes.
 * @param Archivo contenedor de registros de egreso.
 * @param Ruta del archivo contenedor de registros de egreso.
 * @param Archivo contenedor de agentes cargados.
 * @param Ruta del archivo contenedor de agentes cargados.
 * @return Retorna 1 en caso de exito, 0 en caso de error.
 */
int registrarEgreso(ArrayList* agentesCargados, ArrayList* registroEgresos, ArrayList* agentesEnEdificio, ArrayList* agentesFueraEdificio, eAgente* pElement, FILE* archivo, char ruta[], FILE* archivo2, char ruta2[]);

/**
 * Compara el nombre de dos agentes, en caso de ser iguales, compara los apellidos.
 * @param Puntero a la estructura del primer agente a comparar.
 * @param Puntero a la estructura del segundo agente a comparar.
 * @return Retorna 1 en caso de que el primer agente tenga un nombre mayor que el segundo, -1 si es menor y 0 si poseen el mismo nombre y apellido.
 */
int comparaAgenteNoAp(eAgente* Agente1, eAgente* Agente2);

/**
 * Muestra el contenido de un ArrayList de agentes ordenados por nombre y apellido.
 * @param ArrayList a mostrar.
 * @param Puntero auxiliar a estructura de agentes.
 * @param Flag: Modifica el título de la lista entre "AGENTES CARGADOS" (1) y "AGENTES EN EL EDIFICIO" (0).
 */
void mostrarAgentes(ArrayList* pList, eAgente* pElement, int tipoDeMuestreo);

/**
 * Muestra el contenido de un ArrayList de agentes ordenados por posición en la que fueron cargados.
 * @param ArrayList a mostrar.
 * @param Puntero auxiliar a estructura de agentes.
 * @param Flag: Modifica parte del título de la lista entre "INGRESOS" (1) y "EGRESOS" (0).
 * @param Flag: Modifica parte del título de la lista entre "ULTIMOS 10" (1) y "TODOS LOS" (0).
 *              También modifica la cantidad de registros que se muestran, en caso de ser 1 sólo muestra los últimos 10 registros.
 */
void mostrarRegistros(ArrayList* pList, eAgente* pElement, int tipoDeMuestreo, int ultimos10);

/**
 * Limpia los registros de ingreso y egreso del edificio.
 * @param ArrayList de registro de ingresos.
 * @param ArrayList de registro de egresos.
 * @param Archivo contenedor de registros de ingreso.
 * @param Archivo contenedor de registros de egreso.
 * @param Ruta del archivo contenedor de registros de ingreso.
 * @param Ruta del archivo contenedor de registros de egreso.
 */
void limpiarRegistros(ArrayList* registroIngresos, ArrayList* registroEgresos, FILE* archivo1, FILE* archivo2, char ruta1[], char ruta2[]);

/**
 * Lee la información del archivo de agentes, en caso de que dicho archivo no exista, lo crea.
 * @param ArrayList de agentes cargados.
 * @param ArrayList de agentes que se encuentran en el edificio.
 * @param ArrayList de agentes que se encuentran fuera del edificio.
 * @param Archivo contenedor de agentes cargados.
 * @param Ruta del archivo contenedor de agentes cargados.
 * @return Retorna 1 en caso de exito, 0 en caso de error.
 */
int lecturaCreacionArchivoAg(ArrayList* agentesCargados, ArrayList* agentesEnEdificio, ArrayList* agentesFueraEdificio, FILE* archivo, char ruta[]);

/**
 * Lee la información de un archivo binario, en caso de que dicho archivo no exista, lo crea.
 * @param ArrayList donde se va a guardar la información leída.
 * @param ArrayList de agentes cargados.
 * @param Archivo a leer.
 * @param Ruta del archivo a leer.
 * @return Retorna 1 en caso de exito, 0 en caso de error.
 */
int lecturaCreacionArchivoReg(ArrayList* pList, ArrayList* agentesCargados, FILE* archivo, char ruta[]);

/**
 * Carga información en un archivo binario.
 * @param ArrayList de donde se va a extraer la información a guardar.
 * @param Puntero auxiliar a estructura de agentes.
 * @param Archivo a cargar información.
 * @param Ruta del archivo donde se va a cargar la información.
 * @return Retorna 1 en caso de exito, 0 en caso de error.
 */
int cargaArchivo(ArrayList* pList, eAgente* pElement, FILE* archivo, char ruta[]);
