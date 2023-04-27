<?php

namespace app\EleccionesSindicales\controlador;

use app\EleccionesSindicales\repositorio\InterventorRepositorio;
// Ejemplo de controlador para página home de la aplicación
class InterventorController
{
    public function generaInterventores()
    {
        $titulo = (new TitleController())->setTitle('Mesas - ANPE');

        // Header hacia deseaInterventor
        require __DIR__ . '/../../app/plantillas/generaInterventoresAdmin.inc';
    }
}
