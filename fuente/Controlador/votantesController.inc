<?php

namespace app\EleccionesSindicales\controlador;

use app\EleccionesSindicales\repositorio\VotantesRepositorio;
// Ejemplo de controlador para página home de la aplicación
class VotantesController
{

    // Le muestra al admin la pagina de votantes
    public function verVotantes()
    {
        $titulo = (new TitleController())->setTitle('Votantes - ANPE');

        require __DIR__ . '/../../app/plantillas/gestionVotantes.inc';
    }
}
