#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#define REGISTROS_INICIALES 10
#define RUTA_ARCHIVO_BIN "peliculas.dat"
#define RUTA_ARCHIVO_HTM "index.html"

typedef struct {
    char titulo[20];
    char genero[20];
    int duracion;
    char descripcion[500];
    int puntaje;
    char linkImagen[300];
    int estado;

} eMovie;

/**
 * Lee la informaci�n del archivo y en caso de que no exista, lo crea.
 * @param Puntero de punteros que apunta al puntero del contenedor de pel�culas.
 * @param Puntero que apunta al tama�o actual del array.
 * @param Puntero de punteros que apunta al puntero del archivo binario a leer o crear.
 * @return Retorna 1 o 0 dependiendo si pudo leer y/o crear el archivo o no.
 */
int lecturaCreacionArchivo(eMovie** peliculas, int* pMaxRegistros, FILE** archivo);

/**
 * Agrega una pel�cula al archivo binario.
 * @param Puntero de punteros que apunta al puntero del contenedor de pel�culas.
 * @param Puntero que apunta al tama�o actual del array.
 * @param Puntero de punteros que apunta al puntero del archivo binario a escribir.
 * @return Retorna 1 o 0 dependiendo si pudo agregar o no la pelicula.
 */
int agregarPelicula(eMovie** pelicula, int* pMaxRegistros, FILE** archivo);

/**
 * Obtiene el primer �ndice libre del array, si no hay espacio, aumenta el tama�o del mismo en 5.
 * @param Puntero de punteros que apunta al puntero a buscar espacio.
 * @param Puntero que apunta al tama�o actual del array.
 * @return Retorna el primer �ndice disponible.
 */
int obtenerEspacioLibre(eMovie** pelicula, int* pMaxRegistros);

/**
 * Solicita el ingreso del t�tulo de la pelicula.
 * @param Puntero de punteros que apunta al puntero del contenedor de pel�culas.
 * @param �ndice donde se guarda el t�tulo ingresado.
 * @param Si el valor no es 0 agrega la palabra "nuevo" a la solicitud del ingreso de datos.
 */
void pedirTitulo(eMovie** pelicula, int indexLibre, int modificar);

/**
 * Valida si el string est� vac�o o si contiene s�lo espacios.
 * @param String a validar.
 * @return Si no est� vac�o ni contiene s�lo espacios retorna 1, de lo contrario 0.
 */
int validarString(char cadena[]);

/**
 * Solicita el ingreso del genero de la pelicula.
 * @param Puntero de punteros que apunta al puntero del contenedor de pel�culas.
 * @param �ndice donde se guarda el genero ingresado.
 * @param Si el valor no es 0 agrega la palabra "nuevo" a la solicitud del ingreso de datos.
 */
void pedirGenero(eMovie** pelicula, int indexLibre, int modificar);

/**
 * Solicita el ingreso de la duraci�n de la pelicula.
 * @param Puntero de punteros que apunta al puntero del contenedor de pel�culas.
 * @param �ndice donde se guarda la duraci�n ingresada.
 * @param Si el valor no es 0 agrega la palabra "nueva" a la solicitud del ingreso de datos.
 */
void pedirDuracion(eMovie** pelicula, int indexLibre, int modificar);

/**
 * Valida la duraci�n ingresada.
 * @param Duraci�n a validar.
 * @return Si el dato ingresado es correcto devuelve 1, sino 0.
 */
int validarDuracion(int num);

/**
 * Valida si es un n�mero entero.
 * @param N�mero a validar.
 * @return Si es un n�mero devuelve 1, sino 0.
 */
int validarInt(char numero[]);

/**
 * Solicita el ingreso de la descripci�n de la pelicula.
 * @param Puntero de punteros que apunta al puntero del contenedor de pel�culas.
 * @param �ndice donde se guarda la descripci�n ingresada.
 * @param Si el valor no es 0 agrega la palabra "nueva" a la solicitud del ingreso de datos.
 */
void pedirDescripcion(eMovie** pelicula, int indexLibre, int modificar);

/**
 * Solicita el ingreso del puntaje de la pelicula.
 * @param Puntero de punteros que apunta al puntero del contenedor de pel�culas.
 * @param �ndice donde se guarda el puntaje ingresado.
 * @param Si el valor no es 0 agrega la palabra "nuevo" a la solicitud del ingreso de datos.
 */
void pedirPuntaje(eMovie** pelicula, int indexLibre, int modificar);

/**
 * Valida el puntaje ingresado.
 * @param Puntaje a validar.
 * @return Si el dato ingresado es correcto devuelve 1, sino 0.
 */
int validarPuntaje(int num);

/**
 * Solicita el ingreso del link a la imagen de portada de la pelicula.
 * @param Puntero de punteros que apunta al puntero del contenedor de pel�culas.
 * @param �ndice donde se guarda el link a la imagen de portada ingresado.
 * @param Si el valor no es 0 agrega la palabra "nuevo" a la solicitud del ingreso de datos.
 */
void pedirLink(eMovie** pelicula, int indexLibre, int modificar);

/**
 * Elimina una pelicula del archivo binario.
 * @param Puntero de punteros que apunta al puntero del contenedor de pel�culas.
 * @param Tama�o actual del array.
 * @param Puntero de punteros que apunta al puntero del archivo binario a escribir.
 * @return Retorna 1 o 0 dependiendo si pudo eliminar o no la pelicula.
 */
int eliminarPelicula(eMovie** pelicula, int maxRegistros, FILE** archivo);

/**
 * Modifica una pelicula del archivo binario.
 * @param Puntero de punteros que apunta al puntero del contenedor de pel�culas.
 * @param Tama�o actual del array.
 * @param Puntero de punteros que apunta al puntero del archivo binario a escribir.
 * @return Retorna 1 o 0 dependiendo si pudo modificar o no la pelicula.
 */
int modificarPelicula(eMovie** pelicula, int maxRegistros, FILE** archivo);

/**
 * Genera un archivo html a partir de las peliculas cargadas en el archivo binario.
 * @param Puntero de punteros que apunta al puntero del contenedor de pel�culas.
 * @param Tama�o actual del array.
 * @param Nombre del archivo a generar.
 * @return Retorna 1 o 0 dependiendo si pudo generar o no el archivo.
 */
int generarPagina(eMovie** pelicula, int maxRegistros, char nombre_file[]);

#endif
