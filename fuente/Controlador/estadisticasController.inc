<?php

namespace app\EleccionesSindicales\controlador;

use app\EleccionesSindicales\repositorio\EstadisticasRepositorio;

class EstadisticasController
{
    // Pagina estadisticas - Admin
    public function verEstadisticas()
    {
        $titulo = (new TitleController())->setTitle('Estadísticas - ANPE');
        // Estadísticas apartado votantes
        $estadisticasVotantes = (new EstadisticasRepositorio())->estadisticasVotantes();
        // Estadísticas apartado afiliados
        $estadisticasAfiliados = (new EstadisticasRepositorio())->estadisticasAfiliados();
        // Recuento total votantes/votos
        $recuentoTotal = (new EstadisticasRepositorio())->totalVotantes();
        require __DIR__ . '/../../app/plantillas/estadisticas.inc';
    }
}
