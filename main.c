#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main()
{
    // Declaración de variables
    char flagContinue = 's';
    char ingresoA = 'n';
    char ingresoB = 'n';
    int opcion = 0;
    float numeroA = 0.0;
    float numeroB = 0.0;

    // Mensaje de bienvenida y color personalizado
    printf("Bienvenido/a!\n");
    system("COLOR 0F");

    // Estructura del menú
    while(flagContinue == 's')
    {
        // Visualización del menú
        if (verificarFloat(numeroA)) {
            printf("\n1. Ingresar 1er operando (A = %.4f)\n", numeroA);
        }
        else {
            printf("\n1. Ingresar 1er operando (A = %.0f)\n", numeroA);
        }

        if (verificarFloat(numeroB)) {
            printf("2. Ingresar 2do operando (B = %.4f)\n", numeroB);
        }
        else {
            printf("2. Ingresar 2do operando (B = %.0f)\n", numeroB);
        }

        printf("3. Calcular la suma (A + B)\n");
        printf("4. Calcular la resta (A - B)\n");
        printf("5. Calcular la division (A / B)\n");
        printf("6. Calcular la multiplicacion (A * B)\n");
        printf("7. Calcular el factorial (A!)\n");
        printf("8. Calcular todas las operaciones\n");
        printf("9. Salir\n");

        // Guarda la opción seleccionada
        printf("\nSeleccione la opcion deseada: ");
        scanf("%d", &opcion);

        // Si no se ingresaron los operandos necesarios para operar, muestra error
        if (((ingresoA == 'n' || ingresoB == 'n') && opcion > 2 && opcion < 7) || (opcion == 8 && (ingresoA == 'n' || ingresoB == 'n'))) {
            opcion = 0;
            system("cls");
            printf("ERROR: No se han ingresado los operandos necesarios para realizar esta operacion\n");
            continue;
        }
        else if (opcion == 7 && ingresoA == 'n') {
            opcion = 0;
            system("cls");
            printf("ERROR: No se ha ingresado el operando necesario para realizar esta operacion\n");
            continue;
        }

        // Limpia la consola
        system("cls");

        // Estructura funcional del menú
        switch(opcion)
        {
            case 1:
                printf("Ingrese 1er operando: ");
                scanf("%f", &numeroA);
                ingresoA = 's';
                system("cls");
                printf("Primer operando ingresado exitosamente!\n");
                break;
            case 2:
                printf("Ingrese 2do operando: ");
                scanf("%f", &numeroB);
                ingresoB = 's';
                system("cls");
                printf("Segundo operando ingresado exitosamente!\n");
                break;
            case 3:
                sumarFloat(numeroA, numeroB);
                break;
            case 4:
                restarFloat(numeroA, numeroB);
                break;
            case 5:
                dividirFloat(numeroA, numeroB);
                break;
            case 6:
                multiplicarFloat(numeroA, numeroB);
                break;
            case 7:
                // Verifica que el numero A no sea un float
                if (verificarFloat(numeroA)) {
                    printf("ERROR: No se puede calcular el factorial de un numero con decimales\n");
                }
                else {
                    factorialInt((int)numeroA);
                }

                break;
            case 8:
                sumarFloat(numeroA, numeroB);
                restarFloat(numeroA, numeroB);
                dividirFloat(numeroA, numeroB);
                multiplicarFloat(numeroA, numeroB);

                // Verifica que el numero A no sea un float para calcular el factorial
                if (verificarFloat(numeroA)) {
                    printf("No se pudo calcular el factorial de %.2f por tratarse de un numero con decimales\n", numeroA);
                }
                else {
                    factorialInt((int)numeroA);
                }

                break;
            case 9:
                flagContinue = 'n';
                printf("Hasta pronto!\n");
                break;
            default:
                printf("ERROR: Opcion invalida\n");
        }
    }

    return 0;
}
