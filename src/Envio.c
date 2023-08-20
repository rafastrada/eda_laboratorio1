#include "Envio.h"

// Funciones

void Envio_init(Envio *envio) {
    // Inicializa los campos de la estructura ENVIO
    envio->codigo_envio = "";
    envio->dni_receptor = ENVIO_DNI_MINIMO;
    envio->dni_remitente = ENVIO_DNI_MINIMO;
    envio->domicilio_receptor = "";
    envio->fecha_envio = ENVIO_FECHA_MINIMA;
    envio->fecha_recepcion = ENVIO_FECHA_MINIMA;
    envio->nombre_apellido_receptor = "";
    envio->nombre_apellido_remitente = "";
}
