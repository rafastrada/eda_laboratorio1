#include "Envio.h"
#include <string.h>

// Funciones

void Envio_init(Envio *envio) {
    // Inicializa los campos de la estructura ENVIO
    strcpy(envio->codigo_envio,"");
    envio->dni_receptor = ENVIO_DNI_MINIMO;
    envio->dni_remitente = ENVIO_DNI_MINIMO;
    strcpy(envio->domicilio_receptor,"");
    strcpy(envio->fecha_envio,ENVIO_FECHA_MINIMA);
    strcpy(envio->fecha_recepcion,ENVIO_FECHA_MINIMA);
    strcpy(envio->nombre_apellido_receptor,"");
    strcpy(envio->nombre_apellido_remitente,"");
}

