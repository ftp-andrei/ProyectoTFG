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
    // Funcion que muestra los interventores (solo para el admin). 
    // Contiene los metodos de añadir, borrar y modificar interventores.
    public function verInterventores()
    {
        $titulo = (new TitleController())->setTitle('Interventores - ANPE');
        $mesas = (new MesasController())->getAllMesas();
        $interventores = (new InterventorRepositorio())->getAllInterventores();
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
        foreach ($interventores as $interventor) {
            // Elimina interventores
            if (isset($_POST["remove_{$interventor['usuario']}"])) {
                $interventor = (new InterventorRepositorio())->borraInterventor($interventor['IdInterventor']);
                header('Location: index.php?ctl=gestionInterventores');
            }
            // Modifica interventores
        }
        // TODO: GUARDAR CAMBIOS DE LOS INTERVENTORES
        if (isset($_POST["guardarCambios"])) {
            foreach ($interventores as $interventor) {
                $user = $user = $interventor['usuario'];
                $contrasena = $interventor['password'];
                $mesa = $interventor['idMesa'];;
                // POST user
                if (isset($_POST["user_{$interventor['usuario']}"])) {
                    $user = $_POST["user_{$interventor['usuario']}"];
                }
                // POST contrasena
                if (isset($_POST["password_{$interventor['usuario']}"])) {
                    $contrasena = $_POST["password_{$interventor['usuario']}"];
                }
                // POST Mesa
                if (isset($_POST["optSelect_{$interventor['usuario']}"])) {
                    $mesa = $_POST["optSelect_{$interventor['usuario']}"];
                }
                var_dump($user);
                var_dump($contrasena);
                var_dump($mesa);


                if ($insertarInterventores = (new InterventorRepositorio())->guardarCambiosInterventores($user, $contrasena, $mesa, $interventor['IdInterventor'])) {
                    continue;
                } else {
                    $error = "Error al guardar los cambios";
                }
            }
            header('Location: index.php?ctl=gestionInterventores');
        }
        require __DIR__ . '/../../app/plantillas/gestionInterventores.inc';
    }
}
