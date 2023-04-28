<?php

namespace app\EleccionesSindicales\controlador;

use app\EleccionesSindicales\repositorio\InterventorRepositorio;
// Ejemplo de controlador para página home de la aplicación
class InterventorController
{
    // Metodo de generar interventores al iniciar sesion el admin
    public function generaInterventores()
    {
        $titulo = (new TitleController())->setTitle('Interventores - ANPE');


        if (isset($_POST['okGenerarInterventores'])) {
            if ($borra = (new InterventorRepositorio())->borraTodosInterventores()) {
                $interventor = (new InterventorRepositorio())->generaInterventorAdmin();
                var_dump($interventor);
                // Al generar te lleva a la pagina de votantes del admin (¿Quizás hacer una pagina de inicio?)
                // header('Location: index.php?ctl=votantesAdmin');
            } else {
                $error = "Error al borrar los interventores";
            }
        }

        require __DIR__ . '/../../app/plantillas/generaInterventoresAdmin.inc';
    }
}
