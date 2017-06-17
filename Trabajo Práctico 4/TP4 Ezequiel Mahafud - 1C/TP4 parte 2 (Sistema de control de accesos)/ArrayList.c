#include <stdlib.h>
#include "ArrayList.h"

#define AL_INITIAL_VALUE  10
#define AL_INCREMENT      10
#define AL_DECREMENT      10

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
            tam = pList->len(pList);
            pList->pElements[tam] = pElement;
            pList->size++;
            returnAux = 0;
        }
    }

    return returnAux;
}

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

int al_len(ArrayList* pList)
{
    int returnAux = -1;

    if (pList != NULL)
        returnAux = pList->size;

    return returnAux;
}

void* al_get(ArrayList* pList, int index)
{
    void* returnAux = NULL;

    if (pList != NULL && index >= 0 && index < pList->len(pList)) {
        returnAux = pList->pElements[index];
    }

    return returnAux;
}

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

int al_remove(ArrayList* pList, int index)
{
    int returnAux = -1;

    if (pList != NULL && index >= 0 && index < pList->len(pList)) {
        contract(pList, index);

        returnAux = 0;
    }

    return returnAux;
}

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

void* al_pop(ArrayList* pList, int index)
{
    void* returnAux = NULL;

    if (pList != NULL && index >= 0 && index < pList->len(pList)) {
        returnAux = pList->pElements[index];
        pList->remove(pList, index);
    }

    return returnAux;
}

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
