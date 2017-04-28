#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#define MAX_REGISTROS 20

typedef struct {
    char nombrePer[50];
    int edadPer;
    int dniPer;
    int estadoPer;

} ePersona;

ePersona contenedorPersonas[MAX_REGISTROS];

/**
 * Obtiene el primer índice libre del array.
 * @param Array a buscar espacio libre.
 * @param Tamaño del array.
 * @return El primer indice disponible, si no encuentra retorna -1.
 */
int obtenerEspacioLibre(ePersona[], int);

/**
 * Obtiene el índice que coincide con el DNI pasado por parametro.
 * @param Array en donde busca el DNI.
 * @param Tamaño del array.
 * @param DNI a ser buscado en el array.
 * @return El indice en donde se encuentra el elemento que coincide con el parametro DNI, si no lo encuentra retorna -1.
 */
int buscarPorDNI(ePersona[], int, int);

/**
 * Agrega una persona a la lista.
 * @param Array de personas.
 * @param Tamaño del array.
 */
void agregarPersona(ePersona[], int);

/**
 * Solicita el ingreso del nombre de la persona.
 * @param Array de personas.
 * @param Índice donde se guarda el nombre ingresado.
 */
void pedirNombre(ePersona[], int);

/**
 * Solicita el ingreso de la edad de la persona.
 * @return Devuelve la edad ingresada.
 */
int pedirEdad();

/**
 * Solicita el ingreso del DNI de la persona.
 * @param Array de personas.
 * @param Tamaño del array.
 * @param Flag, si se solicita el DNI para hacer un alta setear en 1, para búsqueda por DNI setear en 0.
 * @return Devuelve el DNI ingresado.
 */
int pedirDNI(ePersona[], int, int);

/**
 * Valida la edad ingresada.
 * @param Edad a validar.
 * @return Si el dato ingresado es correcto devuelve 1, sino 0.
 */
int validarEdad(int);

/**
 * Valida el DNI ingresado.
 * @param DNI a validar.
 * @return Si el dato ingresado es correcto devuelve 1, sino 0.
 */
int validarDNI(int);

/**
 * Elimina una persona de la lista
 * @param Array de personas.
 * @param Tamaño del array.
 */
void eliminarPersona(ePersona[], int);

/**
 * Verifica si el DNI ingresado ya se encuentra cargado.
 * @param Array de personas.
 * @param Tamaño del array.
 * @param DNI a verificar.
 * @return DNI no ingresado = 0, DNI ya ingresado = 1.
 */
int DNIIngresado(ePersona[], int, int);

/**
 * Muestra la lista de personas ordenadas alfabéticamente.
 * @param Array de personas.
 * @param Tamaño del array.
 */
void ordenarPersonas(ePersona[], int);

/**
 * Muestra un gráfico de cantidad de personas separado por rangos de edad.
 * @param Array de personas.
 * @param Tamaño del array.
 */
void mostrarGrafico(ePersona[], int);

/**
 * Devuelve el número más alto.
 * @param Primer número a comparar.
 * @param Segundo número a comparar.
 * @param Tercer número a comparar.
 * @return Número mayor.
 */
int calcularMayor(int, int, int);

#endif // FUNCIONES_H_INCLUDED
