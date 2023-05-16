<?php

namespace app\EleccionesSindicales\controlador;

use app\EleccionesSindicales\repositorio\EstadisticasRepositorio;

class EstadisticasController
{

    // Le muestra al admin la pagina de afiliados
    public function verEstadisticas()
    {
        // Un array con todos los datos (Numtotal Mesas/Afiliados/Votantes/Votos) que se van a mostrar en la pagina?
        $titulo = (new TitleController())->setTitle('Estadísticas - ANPE');
        $totalInterventores = (new EstadisticasRepositorio())->estadisticasTotales();
        require __DIR__ . '/../../app/plantillas/estadisticas.inc';
    }
}
