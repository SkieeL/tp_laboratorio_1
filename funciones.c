#include <stdio.h>
#include "funciones.h"

/** \brief Verifica si el float ingresado posee valor decimal para tratarlo como int
 *
 * \param Float a verificar
 * \return Si no posee valor decimal devuelve 0, de lo contrario devuelve 1
 *
 */
int verificarFloat(float numeroFloat) {
    int auxNumero;
    float resultado;

    // Transforma el float a int y lo guarda en una variable auxiliar
    auxNumero = (int)numeroFloat;

    // Resta el n�mero previamente transformado a int con el n�mero formato float
    resultado = (float)auxNumero - numeroFloat;

    // Si el resultado es igual a 0.0, retorna 0 indicando que no es un n�mero con valor decimal
    if (resultado == 0.0) {
        return 0;
    }

    // De lo contrario, retorna 1
    return 1;
}

/** \brief Realiza la suma de dos floats y muestra el resultado en pantalla
 *
 * \param Primer n�mero a sumar
 * \param Segundo n�mero a sumar
 *
 */
void sumarFloat(float numeroA, float numeroB) {
    float resultado;

    // Realiza la suma
    resultado = numeroA + numeroB;

    // Imprime el resultado
    if (verificarFloat(resultado)) {
        printf("El resultado de la suma es: %.4f\n", resultado);
    }
    else {
        printf("El resultado de la suma es: %.0f\n", resultado);
    }
}

/** \brief Realiza la resta de dos floats y muestra el resultado en pantalla
 *
 * \param Minuendo
 * \param Sustraendo
 *
 */
void restarFloat(float numeroA, float numeroB) {
    float resultado;

    // Realiza la resta
    resultado = numeroA - numeroB;

    // Imprime el resultado
    if (verificarFloat(resultado)) {
        printf("El resultado de la resta es: %.4f\n", resultado);
    }
    else {
        printf("El resultado de la resta es: %.0f\n", resultado);
    }
}

/** \brief Realiza la multiplicaci�n de dos floats y muestra el resultado en pantalla
 *
 * \param Primer n�mero a multiplicar
 * \param Segundo n�mero a multiplicar
 *
 */
void multiplicarFloat(float numeroA, float numeroB) {
    float resultado;

    // Realiza la multiplicaci�n
    resultado = numeroA * numeroB;

    // Imprime el resultado
    if (verificarFloat(resultado)) {
        printf("El resultado de la multiplicacion es: %.4f\n", resultado);
    }
    else {
        printf("El resultado de la multiplicacion es: %.0f\n", resultado);
    }
}

/** \brief Realiza la divisi�n de dos floats y muestra el resultado en pantalla
 *
 * \param Dividendo
 * \param Divisor
 *
 */
void dividirFloat(float numeroA, float numeroB) {
    float resultado;

    if (numeroB == 0.0) {
        printf("ERROR: No se puede dividir un numero por 0\n");
        return;
    }

    // Realiza la divisi�n
    resultado = numeroA / numeroB;

    // Imprime el resultado
    if (verificarFloat(resultado)) {
        printf("El resultado de la division es: %.4f\n", resultado);
    }
    else {
        printf("El resultado de la division es: %.0f\n", resultado);
    }
}

/** \brief Calcula el factorial de un n�mero entero y muestra el resultado en pantalla
 *
 * \param Int a calcular
 *
 */
void factorialInt(int numero) {
    int i;
    long long int resultado = 1;

    // Si el n�mero es negativo, tira error
    if (numero < 0) {
        printf("ERROR: No se puede calcular el factorial de un numero negativo\n");
        return;
    }

    /* Si el n�mero es mayor a 20 no permite calcular el factorial,
       ya que el resultado excede el l�mite que abarca una variable long long int */
    if (numero > 20) {
        printf("ERROR: Lo siento, no se puede calcular el factorial de un numero mayor a 20\n");
        return;
    }

    // Calcula el factorial
    for (i = numero; i > 1; i--)
    {
        resultado *= i;
    }

    // Si el n�mero ingresado es 0, el factorial es 1
    if (numero == 0) {
        resultado = 1;
    }

    // Imprime el resultado
    printf("El factorial de %d es: %lld\n", numero, resultado);
}
