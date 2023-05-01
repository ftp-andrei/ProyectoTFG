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
                // Cojo el numero de interventores a crear
                $numeroInterventores = $_POST['numeroInterventores'];
                for ($i = 0; $i < $numeroInterventores; $i++) {
                    // Creo una instancia del controlador
                    $obj = new InterventorController();
                    $pass = $obj->randomPassword();
                    // Devuelve true o false.
                    $interventor = (new InterventorRepositorio())->generaInterventorAdmin($pass);
                }
                // ::Pagina Se han creado con exito, time 5s, header votantesAdmin
                // header('Refresh: 5; url=index.php?ctl=gestionVotantes');
                // Al generar te lleva a la pagina de votantes del admin (¿Quizás hacer una pagina de inicio?)
                header('Location: index.php?ctl=gestionVotantes');
            } else {
                $error = "Error al borrar los interventores";
            }
        }

        require __DIR__ . '/../../app/plantillas/generaInterventoresAdmin.inc';
    }

    // Funcion que genera una contraseña aleatoria para los interventores
    public function randomPassword()
    {
        $caracteres = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890&@#$*!^';
        $pass = "";
        $longitudTotal = strlen($caracteres);
        for ($i = 0; $i < 8; $i++) {
            $n = rand(0, $longitudTotal) - 1;
            $pass .= $caracteres[$n];
        }
        return $pass;
    }
}
