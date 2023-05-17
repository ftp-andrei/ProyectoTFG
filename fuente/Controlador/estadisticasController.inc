<?php

namespace app\EleccionesSindicales\controlador;

use app\EleccionesSindicales\repositorio\EstadisticasRepositorio;

class EstadisticasController
{
    // TODO: AÑADIR CAMPO NUMERO INTERVENTORES
    // Le muestra al admin la pagina de afiliados
    public function verEstadisticas()
    {
        // Un array con todos los datos (Numtotal Mesas/Afiliados/Votantes/Votos) que se van a mostrar en la pagina?
        $titulo = (new TitleController())->setTitle('Estadísticas - ANPE');
        $estadisticasVotantes = (new EstadisticasRepositorio())->estadisticasVotantes();
        $estadisticasAfiliados = (new EstadisticasRepositorio())->estadisticasAfiliados();
        require __DIR__ . '/../../app/plantillas/estadisticas.inc';
    }
}
