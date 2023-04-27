<?php

namespace app\EleccionesSindicales\controlador;

use app\EleccionesSindicales\repositorio\MesasRepositorio;
// Ejemplo de controlador para página home de la aplicación
class MesasController
{
    public function generaMesas()
    {
        $titulo = (new TitleController())->setTitle('Mesas - ANPE');

        // Header hacia deseaInterventor
        require __DIR__ . '/../../app/plantillas/generaMesasAdmin.inc';
    }
}
