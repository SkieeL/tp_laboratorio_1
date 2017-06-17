#include <stdlib.h>
#include "ArrayList.h"

// Agranda el arrayList en AL_INCREMENT elementos.
int resizeUp(ArrayList* pList);

// Achica el arrayList en Al_INCREMENT elementos.
int resizeDown(ArrayList* pList);

// Mueve todos los elementos para adelante (sirve para hacer un espacio entre los elementos, por ej: push).
int expand(ArrayList* pList, int index);

// Mueve todos los elementos para atrás (sirve para sacar un espacio en blanco entre los elementos.
int contract(ArrayList* pList, int index);

#define AL_INITIAL_VALUE  10
#define AL_INCREMENT      10
#define AL_DECREMENT      10
//___________________

/** @brief Reserva espacio en memoria para un nuevo arrayList con AL_INITIAL_VALUE elementos.
 * @param void
 * @return Retorna el puntero del nuevo arrayList, si no consigue espacio en memoria devuelve NULL.
 */
ArrayList* al_newArrayList(void)
{
    ArrayList* pList;
    ArrayList* returnAux = NULL;
    void* pElementos;
    pList = (ArrayList*) calloc(1, sizeof(ArrayList));

    if(pList != NULL)
    {
        pElementos = calloc(AL_INITIAL_VALUE, sizeof(void*));
        if(pElementos != NULL)
        {
            pList->size = 0;
            pList->pElements = pElementos;
            pList->reservedSize = AL_INITIAL_VALUE;
            pList->add = al_add;
            pList->len = al_len;
            pList->set = al_set;
            pList->remove = al_remove;
            pList->clear = al_clear;
            pList->clone = al_clone;
            pList->get = al_get;
            pList->contains = al_contains;
            pList->push = al_push;
            pList->indexOf = al_indexOf;
            pList->isEmpty = al_isEmpty;
            pList->pop = al_pop;
            pList->subList = al_subList;
            pList->containsAll = al_containsAll;
            pList->deleteArrayList = al_deleteArrayList;
            pList->sort = al_sort;
            returnAux = pList;
        }
        else
        {
            free(pList);
        }
    }

    return returnAux;
}


/** @brief  Agrega un elemento al arrayList y si es necesario, agranda el array.
 * @param pList: Puntero al arrayList
 * @param pElement: Puntero al elemento.
 * @return int: Retorna 0 si está todo bien, -1 si pList tiene valor NULL.
 */
int al_add(ArrayList* pList, void* pElement)
{
    int returnAux = -1, tam, flagError = 0;

    if (pList != NULL && pElement != NULL) {
        if (pList->len(pList) == pList->reservedSize) {
            if (resizeUp(pList) == -1) {
                flagError = 1;
            }
        }

        if (!flagError) {
            tam = pList->len(pList); // tam = al_len(pList);
            pList->pElements[tam] = pElement;
            pList->size++;
            returnAux = 0;
        }
    }

    return returnAux;
}


/** @brief  Elimina el arrayList.
 * @param pList: Puntero al arrayList.
 * @return int: Retorna 0 si está todo bien, -1 si pList tiene valor NULL.
 */
int al_deleteArrayList(ArrayList* pList)
{
    int returnAux = -1;

    if (pList != NULL) {
        free(pList->pElements);
        free(pList);
        returnAux = 0;
    }

    return returnAux;
}


/** @brief  Devuelve la cantidad de elementos que posee el arrayList.
 * @param pList: Puntero al arrayList.
 * @return int: Retorna la cantidad de elementos del arrayList, -1 si pList tiene valor NULL.
 */
int al_len(ArrayList* pList)
{
    int returnAux = -1;

    if (pList != NULL)
        returnAux = pList->size;

    return returnAux;
}


/** @brief Devuelve el puntero a un elemento mediante un índice.
 * @param pList: Puntero al arrayList.
 * @param index: Índice del elemento.
 * @return void*: Devuelve NULL en caso de error (pList es NULL o el índice no existe), sino devuelve el puntero al elemento.
 */
void* al_get(ArrayList* pList, int index)
{
    void* returnAux = NULL;

    if (pList != NULL && index >= 0 && index < pList->len(pList)) {
        returnAux = pList->pElements[index];
    }

    return returnAux;
}


/** @brief Busca en un arrayList si tiene al menos un elemento igual a pElement.
 * @param pList: Puntero al arrayList.
 * @param pElement: Puntero al elemento.
 * @return int Return (-1) ERROR: pList o pElement tienen valores NULL.
 *                  - ( 0) No se encuentra el elemento en el arrayList.
 *                  - ( 1) Si el arrayList contiene al menos un elemento igual a pElement.
 */
int al_contains(ArrayList* pList, void* pElement)
{
    int returnAux = -1;

    if (pList != NULL && pElement != NULL) {
        int i;
        returnAux = 0;

        for (i = 0; i < pList->len(pList); i++) {
            if (pList->pElements[i] == pElement) {
                returnAux = 1;
                break;
            }
        }
    }

    return returnAux;
}

/** @brief Asigna un elemento en el arrayList en la posición indicada.
 * @param pList: Puntero al arrayList.
 * @param index: Índice donde ubicar el elemento.
 * @param pElement: Puntero al elemento.
 * @return int Return (-1) ERROR: pList o pElement tienen valores NULL o se indicó un índice inválido.
 *                  - ( 0) Está todo bien.
 */
int al_set(ArrayList* pList, int index, void* pElement)
{
    int returnAux = -1;

    if (pList != NULL && pElement != NULL && index >= 0 && index <= pList->len(pList)) {
        if (index == pList->len(pList))
            pList->add(pList, pElement);
        else
            pList->pElements[index] = pElement;

        returnAux = 0;
    }

    return returnAux;
}


/** @brief Elimina un elemento según el índice.
 * @param pList: Puntero al arrayList.
 * @param index: Índice del elemento.
 * @return int Return (-1) ERROR: pList tiene valor NULL o se indicó un índice inválido.
 *                  - ( 0) Está todo bien.
 */
int al_remove(ArrayList* pList, int index)
{
    int returnAux = -1;

    if (pList != NULL && index >= 0 && index < pList->len(pList)) {
        contract(pList, index);

        returnAux = 0;
    }

    return returnAux;
}


/** @brief Elimina todos los elementos del arrayList.
 * @param pList: Puntero al arrayList.
 * @return int Return (-1) ERROR: pList tiene valor NULL.
 *                  - ( 0) Está todo bien.
 */
int al_clear(ArrayList* pList)
{
    int returnAux = -1;

    if (pList != NULL) {
        pList->size = 0;
        resizeDown(pList);
        returnAux = 0;
    }

    return returnAux;
}


/** @brief Crea un arrayList idéntico al ingresado.
 * @param pList: Puntero al arrayList a clonar.
 * @return ArrayList* Return  (NULL) ERROR: pList tiene un valor NULL.
 *                          - (arrayList nuevo) Está todo bien.
 */
ArrayList* al_clone(ArrayList* pList)
{
    ArrayList* returnAux = NULL;

    if (pList != NULL) {
        int i;

        returnAux = al_newArrayList();

        for (i = 0; i < pList->len(pList); i++) {
            returnAux->add(returnAux, pList->get(pList, i));
        }
    }

    return returnAux;
}


/** @brief Inserta un elemento en el índice especificado.
 * @param pList: Puntero al arrayList.
 * @param index: Índice donde se inserta el elemento.
 * @param pElement: Puntero al elemento.
 * @return int Return (-1) ERROR: pList o pElement tienen un valor NULL o el índice es inválido.
 *                  - ( 0) Está todo bien.
 */
int al_push(ArrayList* pList, int index, void* pElement)
{
    int returnAux = -1;

    if (pList != NULL && pElement != NULL && index >= 0 && index <= pList->len(pList)) {
        if (index == pList->len(pList)) {
            pList->add(pList, pElement);
            returnAux = 0;
        }
        else {
            if (expand(pList, index) == 0) {
                pList->set(pList, index, pElement);
                pList->size++;

                returnAux = 0;
            }
        }
    }

    return returnAux;
}


/** @brief Retorna el índice del primer elemento que se corresponda al elemento indicado.
 * @param pList: Puntero al arrayList.
 * @param pElement Puntero al elemento.
 * @return int Return (-1) ERROR: pList o pElement tienen un valor NULL o no se encontró el elemento.
 *                  - (Índice del elemento) Está todo bien.
 */
int al_indexOf(ArrayList* pList, void* pElement)
{
    int returnAux = -1;

    if (pList != NULL && pElement != NULL) {
        int i;

        for (i = 0; i < pList->len(pList); i++) {
            if (pList->pElements[i] == pElement) {
                returnAux = i;
                break;
            }
        }
    }

    return returnAux;
}


/** @brief Retorna true si el arrayList no contiene elementos.
 * @param pList: Puntero al arrayList.
 * @return int Return (-1) ERROR: pList tiene valor NULL.
 *                  - (0) Si el arrayList NO está vacío.
 *                  - (1) Si el arrayList SI está vacío.
 */
int al_isEmpty(ArrayList* pList)
{
    int returnAux = -1;

    if (pList != NULL) {
        if (pList->len(pList) == 0)
            returnAux = 1;
        else
            returnAux = 0;
    }

    return returnAux;
}


/** @brief Elimina un ítem del arrayList y retorna el puntero al elemento.
 * @param pList: Puntero al arrayList.
 * @param index: Índice del elemento.
 * @return int Return (NULL) ERROR: pList tiene un valor NULL o se especificó un índice inválido.
 *                  - (Puntero al elemento) Si está todo bien.
 */
void* al_pop(ArrayList* pList, int index)
{
    void* returnAux = NULL;

    if (pList != NULL && index >= 0 && index < pList->len(pList)) {
        returnAux = pList->pElements[index];
        pList->remove(pList, index);
    }

    return returnAux;
}


/** @brief Retorna un nuevo arrayList con una porción del arrayList
 *         entre el índice FROM (inclusive) y el índice TO (exclusive).
 * @param pList: Puntero al arrayList.
 * @param from: Índice del elemento inicial (inclusive).
 * @param to: Índice del elemento final (exclusive).
 * @return int Return (NULL) ERROR: pList tiene un valor NULL o 'from' o 'to' son índices inválidos.
 *                  - (Puntero al nuevo arrayList) Está todo bien.
 */
ArrayList* al_subList(ArrayList* pList, int from, int to)
{
    ArrayList* returnAux = NULL;

    if (pList != NULL && from >= 0 && from < pList->len(pList) && to > 0 && to <= pList->len(pList) && from < to) {
        returnAux = al_newArrayList();

        if (returnAux != NULL) {
            int i;

            for (i = from; i < to; i++) {
                returnAux->add(returnAux, pList->get(pList, i));
            }
        }
    }

    return returnAux;
}


/** @brief Retorna true si pList contiene todos los elementos de pList2.
 * @param pList: Puntero al arrayList a revisar.
 * @param pList2: Puntero al arrayList que contiene los elementos a comparar.
 * @return int Return (-1) ERROR: pList o pList2 tienen valores NULL.
 *                  - (0) Si NO contiene todos los elementos.
 *                  - (1) Si contiene todos los elementos.
 */
int al_containsAll(ArrayList* pList, ArrayList* pList2)
{
    int returnAux = -1;

    if (pList != NULL && pList2 != NULL) {
        returnAux = 0;

        if (pList->len(pList) >= pList2->len(pList2)) {
            int i, j, flagFoundElement = 1, containsTrue = 1;

            for (i = 0; i < pList2->len(pList2); i++) {
                if (flagFoundElement == 0) {
                    containsTrue = 0;
                    break;
                }

                flagFoundElement = 0;

                for (j = 0; j < pList->len(pList); j++) {
                    if (pList2->pElements[i] == pList->pElements[j]) {
                        flagFoundElement = 1;
                        break;
                    }
                }
            }

            if (containsTrue)
                returnAux = 1;
        }
    }

    return returnAux;
}


/** @brief Ordena los elementos de un arrayList, usa compare pFunc.
 * @param pList: Puntero al arrayList.
 * @param pFunc (*pFunc): Puntero a la función que compara los elementos.
 * @param order: [1] orden ascendente - [0] orden descendente.
 * @return int Return (-1) ERROR: pList o pFunc tienen valores NULL.
 *                  - (0) Está todo bien.
 */
int al_sort(ArrayList* pList, int (*pFunc)(void*, void*), int order)
{
    int returnAux = -1;

    if (pList != NULL && pFunc != NULL && (order == 0 || order == 1)) {
        int i, j, tam;
        void* pAux;
        tam = pList->len(pList);

        if (order) {
            for (i = 0; i < tam-1; i++) {
                for (j = i+1; j < tam; j++) {
                    if (pFunc(pList->pElements[i], pList->pElements[j]) >= 0) {
                        pAux = pList->pElements[i];
                        pList->pElements[i] = pList->pElements[j];
                        pList->pElements[j] = pAux;
                    }
                }

            }
        }
        else {
            for (i = 0; i < tam-1; i++) {
                for (j = i+1; j < tam; j++) {
                    if (pFunc(pList->pElements[i], pList->pElements[j]) <= 0) {
                        pAux = pList->pElements[i];
                        pList->pElements[i] = pList->pElements[j];
                        pList->pElements[j] = pAux;
                    }
                }

            }
        }

        returnAux = 0;
    }

    return returnAux;
}


/** @brief Incrementa la cantidad de elementos del arrayList en AL_INCREMENT elementos.
 * @param pList: Puntero al arrayList.
 * @return int Return (-1) ERROR: pList es NULL o no hay espacio en memoria disponible.
 *                  - (0) Está todo bien.
 */
int resizeUp(ArrayList* pList)
{
    int returnAux = -1;
    void* pAux;

    if (pList != NULL) {
        pAux = (void*) realloc(pList->pElements, sizeof(void*) * (pList->reservedSize + AL_INCREMENT));

        if (pAux != NULL) {
            pList->pElements = pAux;
            pList->reservedSize += AL_INCREMENT;
            returnAux = 0;
        }
    }

    return returnAux;

}

/** @brief Decrementa la cantidad de elementos del arrayList en AL_DECREMENT elementos si
 *         la diferencia entre el size y el reservedSize es mayor o igual a AL_INCREMENT * 2.
 * @param pList: Puntero al arrayList.
 * @return int Return (-1) ERROR: pList es NULL o no hay espacio en memoria disponible.
 *                  - (0) Decrementó exitosamente.
 *                  - (1) No era necesario decrementar.
 */
int resizeDown(ArrayList* pList)
{
    int returnAux = -1;
    void* pAux;

    if (pList != NULL) {
        if ((pList->reservedSize - pList->len(pList)) >= (AL_INCREMENT * 2)) {
            pAux = (void*) realloc(pList->pElements, sizeof(void*) * (pList->reservedSize - AL_DECREMENT));

            if (pAux != NULL) {
                pList->pElements = pAux;
                pList->reservedSize -= AL_DECREMENT;
                returnAux = 0;
            }
        }
        else
            returnAux = 1;
    }

    return returnAux;

}

/** @brief Mueve todos los elementos del arrayList hacia la derecha (dejando un espacio en la arrayList),
 *         si es necesario redimensiona el arrayList.
 * @param pList: Puntero al arrayList.
 * @param index: Índice del elemento a partir del cual se mueven los elementos.
 * @return int Return (-1) ERROR: pList tiene un valor NULL o el índice es inválido.
 *                  - ( 0) Está todo bien.
 */
int expand(ArrayList* pList, int index)
{
    int returnAux = -1, flagError = 0, i;

    if (pList != NULL && index >= 0 && index < pList->len(pList)) {
        if (pList->len(pList) == pList->reservedSize) {
             if (resizeUp(pList) == -1) {
                flagError = 1;
             }
        }

        if (!flagError) {
            for (i = pList->len(pList)-1; i >= index; i--) {
                pList->pElements[i+1] = pList->pElements[i];
            }

            returnAux = 0;
        }
    }

    return returnAux;
}


/** @brief Mueve todos los elementos del arrayList hacia la izquierda (sacando un espacio en la arrayList).
 * @param pList: Puntero al arrayList.
 * @param index: Índice del elemento a partir del cual se mueven los elementos.
 * @return int Return (-1) ERROR: pList tiene un valor NULL o el índice es inválido.
 *                  - ( 0) Está todo bien.
 */
int contract(ArrayList* pList, int index)
{
    int returnAux = -1, i;

    if (pList != NULL && index >= 0 && index < pList->len(pList)) {
        for (i = index+1; i < pList->len(pList); i++) {
            pList->pElements[i-1] = pList->pElements[i];
        }

        pList->size--;
        resizeDown(pList);
        returnAux = 0;
    }

    return returnAux;
}
