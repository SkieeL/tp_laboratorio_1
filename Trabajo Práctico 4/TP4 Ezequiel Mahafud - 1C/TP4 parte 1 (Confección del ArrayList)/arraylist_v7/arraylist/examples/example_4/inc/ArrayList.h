#ifndef __ARRAYLIST
#define __ARRAYLIST

struct ArrayList {
    int size;
    void **pElements;
    int reservedSize;

    int     (*add)();
    int     (*len)();
    int     (*contains)();
    int     (*set)();
    int     (*remove)();
    int     (*clear)();
    int     (*push)();
    int     (*indexOf)();
    int     (*isEmpty)();
    void*   (*get)();
    void*   (*pop)();
    int     (*containsAll)();
    int     (*sort)();
    struct ArrayList* (* clone)();
    struct ArrayList* (*subList)();
    int     (*deleteArrayList)();

} typedef ArrayList;
#endif

/** @brief Reserva espacio en memoria para un nuevo arrayList con AL_INITIAL_VALUE elementos.
 * @param void
 * @return Retorna el puntero del nuevo arrayList, si no consigue espacio en memoria devuelve NULL.
 */
ArrayList* al_newArrayList(void);

/** @brief  Agrega un elemento al arrayList y si es necesario, agranda el array.
 * @param pList: Puntero al arrayList
 * @param pElement: Puntero al elemento.
 * @return int: Retorna 0 si est� todo bien, -1 si pList tiene valor NULL.
 */
int al_add(ArrayList* pList,void* pElement);

/** @brief  Elimina el arrayList.
 * @param pList: Puntero al arrayList.
 * @return int: Retorna 0 si est� todo bien, -1 si pList tiene valor NULL.
 */
int al_deleteArrayList(ArrayList* pList);

/** @brief  Devuelve la cantidad de elementos que posee el arrayList.
 * @param pList: Puntero al arrayList.
 * @return int: Retorna la cantidad de elementos del arrayList, -1 si pList tiene valor NULL.
 */
int al_len(ArrayList* pList);

/** @brief Devuelve el puntero a un elemento mediante un �ndice.
 * @param pList: Puntero al arrayList.
 * @param index: �ndice del elemento.
 * @return void*: Devuelve NULL en caso de error (pList es NULL o el �ndice no existe), sino devuelve el puntero al elemento.
 */
void* al_get(ArrayList* pList , int index);

/** @brief Busca en un arrayList si tiene al menos un elemento igual a pElement.
 * @param pList: Puntero al arrayList.
 * @param pElement: Puntero al elemento.
 * @return int Return (-1) ERROR: pList o pElement tienen valores NULL.
 *                  - ( 0) No se encuentra el elemento en el arrayList.
 *                  - ( 1) Si el arrayList contiene al menos un elemento igual a pElement.
 */
int al_contains(ArrayList* pList, void* pElement);

/** @brief Asigna un elemento en el arrayList en la posici�n indicada.
 * @param pList: Puntero al arrayList.
 * @param index: �ndice donde ubicar el elemento.
 * @param pElement: Puntero al elemento.
 * @return int Return (-1) ERROR: pList o pElement tienen valores NULL o se indic� un �ndice inv�lido.
 *                  - ( 0) Est� todo bien.
 */
int al_set(ArrayList* pList, int index,void* pElement);

/** @brief Elimina un elemento seg�n el �ndice.
 * @param pList: Puntero al arrayList.
 * @param index: �ndice del elemento.
 * @return int Return (-1) ERROR: pList tiene valor NULL o se indic� un �ndice inv�lido.
 *                  - ( 0) Est� todo bien.
 */
int al_remove(ArrayList* pList,int index);

/** @brief Elimina todos los elementos del arrayList.
 * @param pList: Puntero al arrayList.
 * @return int Return (-1) ERROR: pList tiene valor NULL.
 *                  - ( 0) Est� todo bien.
 */
int al_clear(ArrayList* pList);

/** @brief Crea un arrayList id�ntico al ingresado.
 * @param pList: Puntero al arrayList a clonar.
 * @return ArrayList* Return  (NULL) ERROR: pList tiene un valor NULL.
 *                          - (arrayList nuevo) Est� todo bien.
 */
ArrayList* al_clone(ArrayList* pList);

/** @brief Inserta un elemento en el �ndice especificado.
 * @param pList: Puntero al arrayList.
 * @param index: �ndice donde se inserta el elemento.
 * @param pElement: Puntero al elemento.
 * @return int Return (-1) ERROR: pList o pElement tienen un valor NULL o el �ndice es inv�lido.
 *                  - ( 0) Est� todo bien.
 */
int al_push(ArrayList* pList, int index, void* pElement);

/** @brief Retorna el �ndice del primer elemento que se corresponda al elemento indicado.
 * @param pList: Puntero al arrayList.
 * @param pElement Puntero al elemento.
 * @return int Return (-1) ERROR: pList o pElement tienen un valor NULL o no se encontr� el elemento.
 *                  - (�ndice del elemento) Est� todo bien.
 */
int al_indexOf(ArrayList* pList, void* pElement);

/** @brief Retorna true si el arrayList no contiene elementos.
 * @param pList: Puntero al arrayList.
 * @return int Return (-1) ERROR: pList tiene valor NULL.
 *                  - (0) Si el arrayList NO est� vac�o.
 *                  - (1) Si el arrayList SI est� vac�o.
 */
int al_isEmpty(ArrayList* pList);

/** @brief Elimina un �tem del arrayList y retorna el puntero al elemento.
 * @param pList: Puntero al arrayList.
 * @param index: �ndice del elemento.
 * @return int Return (NULL) ERROR: pList tiene un valor NULL o se especific� un �ndice inv�lido.
 *                  - (Puntero al elemento) Si est� todo bien.
 */
void* al_pop(ArrayList* pList,int index);

/** @brief Retorna un nuevo arrayList con una porci�n del arrayList
 *         entre el �ndice FROM (inclusive) y el �ndice TO (exclusive).
 * @param pList: Puntero al arrayList.
 * @param from: �ndice del elemento inicial (inclusive).
 * @param to: �ndice del elemento final (exclusive).
 * @return int Return (NULL) ERROR: pList tiene un valor NULL o 'from' o 'to' son �ndices inv�lidos.
 *                  - (Puntero al nuevo arrayList) Est� todo bien.
 */
ArrayList* al_subList(ArrayList* pList,int from,int to);

/** @brief Retorna true si pList contiene todos los elementos de pList2.
 * @param pList: Puntero al arrayList a revisar.
 * @param pList2: Puntero al arrayList que contiene los elementos a comparar.
 * @return int Return (-1) ERROR: pList o pList2 tienen valores NULL.
 *                  - (0) Si NO contiene todos los elementos.
 *                  - (1) Si contiene todos los elementos.
 */
int al_containsAll(ArrayList* pList,ArrayList* pList2);

/** @brief Ordena los elementos de un arrayList, usa compare pFunc.
 * @param pList: Puntero al arrayList.
 * @param pFunc (*pFunc): Puntero a la funci�n que compara los elementos.
 * @param order: [1] orden ascendente - [0] orden descendente.
 * @return int Return (-1) ERROR: pList o pFunc tienen valores NULL.
 *                  - (0) Est� todo bien.
 */
int al_sort(ArrayList* pList, int (*pFunc)(void* ,void*), int order);

/** @brief Incrementa la cantidad de elementos del arrayList en AL_INCREMENT elementos.
 * @param pList: Puntero al arrayList.
 * @return int Return (-1) ERROR: pList es NULL o no hay espacio en memoria disponible.
 *                  - (0) Est� todo bien.
 */
int resizeUp(ArrayList* pList);

/** @brief Decrementa la cantidad de elementos del arrayList en AL_DECREMENT elementos si
 *         la diferencia entre el size y el reservedSize es mayor o igual a AL_INCREMENT * 2.
 * @param pList: Puntero al arrayList.
 * @return int Return (-1) ERROR: pList es NULL o no hay espacio en memoria disponible.
 *                  - (0) Decrement� exitosamente.
 *                  - (1) No era necesario decrementar.
 */
 int resizeDown(ArrayList* pList);

 /** @brief Mueve todos los elementos del arrayList hacia la derecha (dejando un espacio en la arrayList),
 *         si es necesario redimensiona el arrayList.
 * @param pList: Puntero al arrayList.
 * @param index: �ndice del elemento a partir del cual se mueven los elementos.
 * @return int Return (-1) ERROR: pList tiene un valor NULL o el �ndice es inv�lido.
 *                  - ( 0) Est� todo bien.
 */
int expand(ArrayList* pList,int index);

/** @brief Mueve todos los elementos del arrayList hacia la izquierda (sacando un espacio en la arrayList).
 * @param pList: Puntero al arrayList.
 * @param index: �ndice del elemento a partir del cual se mueven los elementos.
 * @return int Return (-1) ERROR: pList tiene un valor NULL o el �ndice es inv�lido.
 *                  - ( 0) Est� todo bien.
 */
int contract(ArrayList* pList,int index);
