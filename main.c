#include <stdio.h>
#include <stdlib.h>
#include "Envio.h"

int main()
{
    printf("Hello world!\n");

    // TEST
    Envio prueba;
    Envio_init(&prueba);

    printf("%s\n%u\n%s\n%s\n%u\n%s\n%s\n%s\n\n",
           Envio_get_codigo_envio(&prueba),
           Envio_get_dni_receptor(&prueba),
           Envio_get_nombre_apellido_receptor(&prueba),
           Envio_get_domicilio_receptor(&prueba),
           Envio_get_dni_remitente(&prueba),
           Envio_get_nombre_apellido_remitente(&prueba),
           Envio_get_fecha_envio(&prueba),
           Envio_get_fecha_recepcion(&prueba)
           );

    return 0;
}

//memorizacion previa

/*int memorizacion_previa(Lista *lista, int *cant_repetidos, int *cargados, int tipo_orden){
    FILE *fichero;
    int resultado_alta = 1, repetidos = 0, indice = 0;
    Envio nuevo;
    fichero = fopen("Vendedores.txt","r");
    if (fichero == NULL)
        return -1;
    else {
        while(!feof(fichero)){
            fscanf(fichero,"%d",&nuevo.dni);
            fscanf(fichero," %[^\n]",nuevo.nombre);
            fscanf(fichero," %[^\n]",nuevo.telefono);
            fscanf(fichero,"%f",&nuevo.monto_vendido);
            fscanf(fichero,"%d",&nuevo.cant_vendido);
            fscanf(fichero," %[^\n]",nuevo.canal_venta);
            a_mayuscula(nuevo.nombre);
            /*
            if(tipo_orden == 1)
                resultado_alta = alta_lso(lista, nuevo);
            else
                resultado_alta = alta_lsobb(lista, nuevo);
            if (resultado_alta == -1){
                fclose(fichero);
                break;
            }
            if (resultado_alta == 0){
                repetidos ++;
            }
            indice ++;
        }
    }

    *cargados = indice;
    *cant_repetidos = repetidos;
    fclose(fichero);

    if(resultado_alta == -1){
        return 0;
    }
    return 1;
}*/
