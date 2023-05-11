<?php

namespace app\EleccionesSindicales\controlador;

use app\EleccionesSindicales\repositorio\InterventorRepositorio;

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
                $numeroInterventores = $_POST['numeroInterventores'];
                for ($i = 0; $i < $numeroInterventores; $i++) {
                    // Creo una instancia del controlador
                    $obj = new InterventorController();
                    $pass = $obj->randomPassword();
                    // Devuelve true o false.
                    if ($genInterventor = (new InterventorRepositorio())->generaInterventorAdmin($pass)) {
                        continue;
                    } else {
                        $error = "Error al generar los interventores";
                    }
                }
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
        // Mesas para el select
        $mesas = (new MesasController())->getAllMesas();
        $interventores = (new InterventorRepositorio())->getAllInterventores();
        // Añadir interventores
        if (isset($_POST['anadirInterventor']) || isset($_POST['crearInterventor'])) {
            // Creo una instancia del controlador
            $obj = new InterventorController();
            $pass = $obj->randomPassword();

            // Hashear password, para introducirlo en la bbdd
            // $hashed_password = password_hash($pass, PASSWORD_DEFAULT);

            // Verificar que es la misma password
            // if (password_verify($pass, $hashed_password)) {
            //     echo "La contraseña es válida.";
            // } else {
            //     echo "La contraseña no es válida.";
            // }


            // // Devuelve true o false.
            if ($nuevoInterventor = (new InterventorRepositorio())->generaInterventorAdmin($pass)) {
                header('Location: index.php?ctl=gestionInterventores');
            } else {
                $error = "<br>Error al crear el interventor";
            }
        }
        // Elimina interventores
        foreach ($interventores as $interventor) {
            if (isset($_POST["remove_{$interventor['usuario']}"])) {
                // Devuelve true o false.
                if ($borraInterventor = (new InterventorRepositorio())->borraInterventor($interventor['IdInterventor'])) {
                    header('Location: index.php?ctl=gestionInterventores');
                } else {
                    $error = "<br>Error al borrar el interventor";
                }
            }
        }
        // Guardar los cambios
        if (isset($_POST["guardarCambios"])) {
            $arr = [];
            $tamano = sizeof($interventores);
            for ($i = 0; $i < $tamano; $i++) {
                $user = $interventores[$i]['usuario'];
                $contrasena = $interventores[$i]['password'];
                $mesa = $interventores[$i]['idMesa'];
                // POST user
                if (isset($_POST["user_{$interventores[$i]['usuario']}"])) {
                    if ($_POST["user_{$interventores[$i]['usuario']}"] !=  $user) {
                        if ($existe = (new InterventorRepositorio())->existeInterventor($_POST["user_{$interventores[$i]['usuario']}"])) {
                            $user = $_POST["user_{$interventores[$i]['usuario']}"];
                        } else {
                            $error = "<br>Ha habido errores en el nombre de usuario: El nombre de usuario ya existe o es duplicado";
                        }
                    }
                }
                // POST contrasena
                if (isset($_POST["password_{$interventores[$i]['usuario']}"])) {
                    $contrasena = $_POST["password_{$interventores[$i]['usuario']}"];
                }
                // POST Mesa
                if (isset($_POST["optSelect_{$interventores[$i]['usuario']}"])) {
                    $mesa = $_POST["optSelect_{$interventores[$i]['usuario']}"];
                }
                $arr[$i]['IdInterventor'] = $interventores[$i]['IdInterventor'];
                $arr[$i]['usuario'] = $user;
                $arr[$i]['password'] = $contrasena;
                $arr[$i]['idMesa'] = $mesa;
            }
            // Guarda los cambios y redirige a la pagina de gestion de interventores
            if ($arr != $interventores) {
                if ($guardaInterventor = (new InterventorRepositorio())->guardarCambiosInterventores($arr)) {
                    header('Location: index.php?ctl=gestionInterventores');
                } else {
                    $error = "<br>Error al guardar los cambios";
                }
            }
        }

        require __DIR__ . '/../../app/plantillas/gestionInterventores.inc';
    }
}
