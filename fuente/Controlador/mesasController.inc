<?php

namespace app\EleccionesSindicales\controlador;

use app\EleccionesSindicales\repositorio\MesasRepositorio;
// Ejemplo de controlador para página home de la aplicación
class MesasController
{
    // Metodo de generar mesas al iniciar sesion el admin
    public function generaMesas()
    {
        $titulo = (new TitleController())->setTitle('Mesas - ANPE');

        if (isset($_POST['okGenerarMesas'])) {

            // Te lleva a la página que pregunta si desea interventores al iniciar el admin
            header('Location: index.php?ctl=deseaInterventor');
        }
        require __DIR__ . '/../../app/plantillas/generaMesasAdmin.inc';
    }
}
