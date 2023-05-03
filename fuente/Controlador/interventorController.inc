<?php

namespace app\EleccionesSindicales\controlador;

use app\EleccionesSindicales\repositorio\InterventorRepositorio;
// Ejemplo de controlador para página home de la aplicación
class InterventorController
{
    public function inicioInterventor()
    {
        $titulo = (new TitleController())->setTitle('Inicio - ANPE');

        require __DIR__ . '/../../app/plantillas/inicioInterventor.inc';
    }


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
        $longitudTotal = strlen($caracteres) - 1;
        for ($i = 0; $i < 8; $i++) {
            $n = rand(0, $longitudTotal);
            $pass .= $caracteres[$n];
        }
        return $pass;
    }
    // Funcion que muestra los interventores (solo para el admin)
    public function verInterventores()
    {
        $titulo = (new TitleController())->setTitle('Interventores - ANPE');

        $interventores = (new InterventorRepositorio())->getAllInterventores();
        $tamano = sizeof($interventores);
        // Boton de añadir interventor
        if (isset($_POST['anadirInterventor']) || isset($_POST['crearInterventor'])) {
            // Creo una instancia del controlador
            $obj = new InterventorController();
            $pass = $obj->randomPassword();
            // Devuelve true o false.
            $interventor = (new InterventorRepositorio())->generaInterventorAdmin($pass);
            // Hace header hacia la misma pagina para refrescar, y asi evitar que al hacer F5 se creen mas interventores.
            header('Location: index.php?ctl=gestionInterventores');
        }
        // TODO: ELIMINAR INTERVENTORES
        for ($i = 0; $i < $tamano; $i++) {
            if (isset($_POST["remove_{$interventores[$i]['usuario']}"])) {
                var_dump("remove_{$interventores[$i]['usuario']}");
                $eliminar = $interventores[$i]['IdInterventor'];
                $interventor = (new InterventorRepositorio())->borraInterventor($eliminar);
                header('Location: index.php?ctl=gestionInterventores');
            }
        }
        // TODO: GUARDAR CAMBIOS DE LOS INTERVENTORES
        if (isset($_POST["guardarCambios"])) {
            for ($i = 0; $i < count($interventores); $i++) {
                $arrInterventores[$i]['IdInterventor'] = $interventores[$i]['IdInterventor'];
                $arrInterventores[$i]['usuario'] = $interventores[$i]['usuario'];
                $arrInterventores[$i]['password'] = $interventores[$i]['password'];
                $arrInterventores[$i]['idMesa'] = $interventores[$i]['idMesa'];
            }
            foreach ($arrInterventores as $interventor) {
                if ($insertarInterventores = (new InterventorRepositorio())->guardarCambiosInterventores($interventor['usuario'], $interventor['password'], $interventor['idMesa'], $interventor['IdInterventor'])) {
                    continue;
                } else {
                    $error = "Error al guardar los cambios";
                }
            }
        }
        require __DIR__ . '/../../app/plantillas/gestionInterventores.inc';
    }
}
