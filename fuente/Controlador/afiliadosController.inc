<?php

namespace app\EleccionesSindicales\controlador;

use app\EleccionesSindicales\repositorio\AfiliadosRepositorio;

class AfiliadosController
{

    // Le muestra al admin la pagina de afiliados
    public function verAfiliados()
    {
        $titulo = (new TitleController())->setTitle('Afiliados - ANPE');
        $votantes = (new AfiliadosRepositorio())->getAfiliados();

        require __DIR__ . '/../../app/plantillas/gestionAfiliados.inc';
    }
}
