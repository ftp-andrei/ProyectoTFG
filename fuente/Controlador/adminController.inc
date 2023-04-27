<?php

namespace app\EleccionesSindicales\controlador;

use app\EleccionesSindicales\repositorio\AdminRepositorio;
// Ejemplo de controlador para página home de la aplicación
class AdminController
{
    // Al iniciar sesion, le preguntará si desea generar mesas
    public function deseaMesas()
    {
        $titulo = (new TitleController())->setTitle('Mesas - ANPE');

        if (isset($_POST['Si'])) {
            header('Location: index.php?ctl=generaMesas');
        }
        if (isset($_POST['No'])) {
            header('Location: index.php?ctl=deseaInterventor');
        }
        require __DIR__ . '/../../app/plantillas/deseaMesasAdmin.inc';
    }
    // Despues de preguntarle si desea generar mesas, le pregunta si desea generar interventores
    public function deseaInterventores()
    {
        $titulo = (new TitleController())->setTitle('Interventores - ANPE');

        if (isset($_POST['Si'])) {
            header('Location: index.php?ctl=generaInterventores');
        }
        if (isset($_POST['No'])) {
            header('Location: index.php?ctl=votantesAdmin');
        }
        require __DIR__ . '/../../app/plantillas/deseaInterventoresAdmin.inc';
    }
    // Le muestra al admin la pagina de votantes
    public function votantesAdmin()
    {
        $titulo = (new TitleController())->setTitle('Votantes - ANPE');

        require __DIR__ . '/../../app/plantillas/votantesAdmin.inc';
    }
}
