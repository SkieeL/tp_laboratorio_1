#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#define REGISTROS_INICIALES 10
#define RUTA_ARCHIVO_BIN "peliculas.dat"
#define RUTA_ARCHIVO_HTM "index.html"

typedef struct {
    int idPelicula;
    char titulo[20];
    char genero[20];
    int duracion;
    char descripcion[500];
    int puntaje;
    char linkImagen[300];
    int estado;

} eMovie;

/**
 * Lee la información del archivo y en caso de que no exista, lo crea.
 * @param Puntero al contenedor de películas.
 * @param Tamaño actual del array.
 * @param Archivo binario a leer o crear.
 * @return Retorna 1 o 0 dependiendo si pudo leer y/o crear el archivo o no.
 */
int lecturaCreacionArchivo(eMovie* peliculas, int maxRegistros, FILE* archivo);

/**
 * Agrega una película al archivo binario.
 * @param Puntero al contenedor de películas.
 * @param Tamaño actual del array.
 * @param Archivo binario a escribir.
 * @return Retorna 1 o 0 dependiendo si pudo agregar o no la pelicula.
 */
int agregarPelicula(eMovie* pelicula, int maxRegistros, FILE* archivo);

/**
 * Obtiene el primer índice libre del array, si no hay espacio, aumenta el tamaño en 5.
 * @param Puntero al array a buscar espacio libre.
 * @param Tamaño actual del array.
 * @return Retorna el primer índice disponible.
 */
int obtenerEspacioLibre(eMovie* pelicula, int maxRegistros);

/**
 * Solicita el ingreso del título de la pelicula.
 * @param Puntero al contenedor de películas.
 * @param Índice donde se guarda el título ingresado.
 */
void pedirTitulo(eMovie* pelicula, int indexLibre);

/**
 * Solicita el ingreso del genero de la pelicula.
 * @param Puntero al contenedor de películas.
 * @param Índice donde se guarda el genero ingresado.
 */
void pedirGenero(eMovie* pelicula, int indexLibre);

/**
 * Solicita el ingreso de la duración de la pelicula.
 * @param Puntero al contenedor de películas.
 * @param Índice donde se guarda la duración ingresada.
 */
void pedirDuracion(eMovie* pelicula, int indexLibre);

/**
 * Valida la duración ingresada.
 * @param Duración a validar.
 * @return Si el dato ingresado es correcto devuelve 1, sino 0.
 */
int validarDuracion(int num);

/**
 * Solicita el ingreso de la descripción de la pelicula.
 * @param Puntero al contenedor de películas.
 * @param Índice donde se guarda la descripción ingresada.
 */
void pedirDescripcion(eMovie* pelicula, int indexLibre);

/**
 * Solicita el ingreso del puntaje de la pelicula.
 * @param Puntero al contenedor de películas.
 * @param Índice donde se guarda el puntaje ingresado.
 */
void pedirPuntaje(eMovie* pelicula, int indexLibre);

/**
 * Valida el puntaje ingresado.
 * @param Puntaje a validar.
 * @return Si el dato ingresado es correcto devuelve 1, sino 0.
 */
int validarPuntaje(int num);

/**
 * Solicita el ingreso del link a la imagen de portada de la pelicula.
 * @param Puntero al contenedor de películas.
 * @param Índice donde se guarda el link a la imagen de portada ingresado.
 */
void pedirLink(eMovie* pelicula, int indexLibre);

/**
 * Elimina una pelicula del archivo binario.
 * @param Puntero al contenedor de películas.
 * @param Tamaño actual del array.
 * @param Archivo binario a escribir.
 * @return Retorna 1 o 0 dependiendo si pudo borrar o no la pelicula.
 */
int borrarPelicula(eMovie* pelicula, int maxRegistros, FILE* archivo);

/**
 * Modifica una pelicula del archivo binario.
 * @param Puntero al contenedor de películas.
 * @param Tamaño actual del array.
 * @param Archivo binario a escribir.
 * @return Retorna 1 o 0 dependiendo si pudo modificar o no la pelicula.
 */
int modificarPelicula(eMovie* pelicula, int maxRegistros, FILE* archivo);

/**
 * Genera un archivo html a partir de las peliculas cargadas en el archivo binario.
 * @param Puntero al contenedor de películas.
 * @param Tamaño actual del array.
 * @param Nombre del archivo a generar.
 * @return Retorna 1 o 0 dependiendo si pudo generar o no el archivo.
 */
int generarPagina(eMovie* pelicula, int maxRegistros, char nombre_file[]);

#endif // FUNCIONES_H_INCLUDED
