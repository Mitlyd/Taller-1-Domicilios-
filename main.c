#include <stdio.h>
#include <string.h>

#define MAX_PROD 6
#define MAX_CARRITO 20

// Estructura de producto
typedef struct {
    int id;
    char nombre[30];
    int precio;
} Producto;

// Estructura de item en el carrito
typedef struct {
    Producto prod;
    int cantidad;
} Item;

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
    Producto productos[MAX_PROD] = {
        {1, "SALCHIPAPA", 14000},
        {2, "LASAÑA", 20000},
        {3, "GASEOSA PERSONAL", 3000},
        {4, "ALITAS BBQ", 15700},
        {5, "CHORIPAN", 19000},
        {6, "PIZZA FAMILIAR", 25000}
    };

    Item carrito[MAX_CARRITO];
    int numItems = 0;
    int opcion, i, id, cant;
    int subtotal = 0;
    const int costoDomicilio = 5000;

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Ver menú de productos\n");
        printf("2. Agregar producto al carrito\n");
        printf("3. Ver carrito y total\n");
        printf("4. Confirmar pedido\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        if (scanf("%d", &opcion) != 1) {
            printf("La  Entrada es inválida.\n");
            limpiarBuffer();
            continue;
        }
        limpiarBuffer();

        switch(opcion) {
            case 1: // Mostrar productos
                printf("\n--- MENÚ DE PRODUCTOS ---\n");
                for(i = 0; i < MAX_PROD; i++) {
                    printf("%d. %s - $%d\n", productos[i].id, productos[i].nombre, productos[i].precio);
                }
                break;

            case 2: // Agregar al carrito
                if(numItems >= MAX_CARRITO) {
                    printf(" El carrito está lleno.\n");
                    break;
                }
                printf("\nIngrese id del producto: ");
                if (scanf("%d", &id) != 1) {
                    printf(" Entrada inválida.\n");
                    limpiarBuffer();
                    break;
                }
                limpiarBuffer();

                if(id < 1 || id > MAX_PROD) {
                    printf(" Producto no válido.\n");
                    break;
                }
                printf("Ingrese cantidad: ");
                if (scanf("%d", &cant) != 1 || cant <= 0) {
                    printf(" Cantidad inválida.\n");
                    limpiarBuffer();
                    break;
                }
                limpiarBuffer();

                carrito[numItems].prod = productos[id-1];
                carrito[numItems].cantidad = cant;
                numItems++;
                printf("Producto agregado al carrito.\n");
                break;

            case 3: // Mostrar carrito
                printf("\n--- CARRITO ---\n");
                subtotal = 0;
                if(numItems == 0) {
                    printf("El carrito está vacío.\n");
                } else {
                    for(i = 0; i < numItems; i++) {
                        int valor = carrito[i].prod.precio * carrito[i].cantidad;
                        subtotal += valor;
                        printf("%s x%d -> $%d\n", carrito[i].prod.nombre, carrito[i].cantidad, valor);
                    }
                    printf("Subtotal: $%d\n", subtotal);
                    printf("Domicilio: $%d\n", costoDomicilio);
                    printf("TOTAL: $%d\n", subtotal + costoDomicilio);
                }
                break;

            case 4: // Confirmar pedido
                if(numItems == 0) {
                    printf("No puedes confirmar un pedido vacío.\n");
                } else {
                    FILE *factura = fopen("factura.txt", "w");
                    if(factura == NULL) {
                        printf(" Error al generar la factura.txt.\n");
                        break;
                    }

                    printf("\n--- PEDIDO CONFIRMADO ---\n");
                    fprintf(factura, "=== FACTURA DE COMPRA ===\n");

                    subtotal = 0;
                    for(i = 0; i < numItems; i++) {
                        int valor = carrito[i].prod.precio * carrito[i].cantidad;
                        subtotal += valor;
                        printf("%s x%d -> $%d\n", carrito[i].prod.nombre, carrito[i].cantidad, valor);
                        fprintf(factura, "%s x%d -> $%d\n", carrito[i].prod.nombre, carrito[i].cantidad, valor);
                    }

                    printf("Subtotal: $%d\n", subtotal);
                    printf("Domicilio: $%d\n", costoDomicilio);
                    printf("TOTAL A PAGAR: $%d\n", subtotal + costoDomicilio);

                    fprintf(factura, "------------------------\n");
                    fprintf(factura, "Subtotal: $%d\n", subtotal);
                    fprintf(factura, "Domicilio: $%d\n", costoDomicilio);
                    fprintf(factura, "TOTAL A PAGAR: $%d\n", subtotal + costoDomicilio);
                    fprintf(factura, "¡Gracias por su compra!\n");

                    fclose(factura);

                    printf("\nFactura generada en 'factura.txt'.\n");

                    numItems = 0; // Reiniciar carrito
                }
                break;

            case 5: 
                printf(" Saliendo... !Gracias por visitarnos¡\n");
                break;

            default:
                printf("!upps¡ La Opción no es válida.\n");
        }

    } while(opcion != 5);

    return 0;
}
