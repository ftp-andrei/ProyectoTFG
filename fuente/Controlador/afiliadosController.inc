<?php

namespace app\EleccionesSindicales\controlador;

use app\EleccionesSindicales\repositorio\AfiliadosRepositorio;
// Ejemplo de controlador para página home de la aplicación
class AfiliadosController
{

    // Le muestra al admin la pagina de votantes
    public function verAfiliados()
    {
        $titulo = (new TitleController())->setTitle('Afiliados - ANPE');

        require __DIR__ . '/../../app/plantillas/gestionAfiliados.inc';
    }
}
