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
