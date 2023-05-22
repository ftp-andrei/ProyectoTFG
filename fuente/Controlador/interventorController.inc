<?php

namespace app\EleccionesSindicales\controlador;

use app\EleccionesSindicales\repositorio\InterventorRepositorio;

class InterventorController
{
    // Login interventores - Lista de votantes de su mesa
    public function inicioInterventor()
    {
        $titulo = (new TitleController())->setTitle('Inicio - ANPE');
        if ($_SESSION) {
            if (isset($_SESSION['interventor'])) {
                $listaInterventor = (new InterventorRepositorio())->listaInterventor($_SESSION['usuInterventor']);

                foreach ($listaInterventor as $votante) {
                    if (isset($_POST["votoSi_{$votante['IdVotante']}"])) {
                        // Devuelve true o false.
                        // Si ya tiene marcado el voto a 1, no lo hace.
                        if (intval($votante['Voto']) != 1) {
                            if ($votoSi = (new InterventorRepositorio())->guardaVotoSi($votante['NIF'])) {
                                header('Location: index.php?ctl=inicioInterventor');
                            } else {
                                $error = "<br>Error al modificar el voto del votante";
                            }
                        }
                    }
                    if (isset($_POST["votoNo_{$votante['IdVotante']}"])) {
                        // Devuelve true o false.
                        // Si ya tiene marcado el voto a 0, no lo hace.
                        if (intval($votante['Voto']) != 0) {
                            if ($votoNo = (new InterventorRepositorio())->guardaVotoNo($votante['NIF'])) {
                                header('Location: index.php?ctl=inicioInterventor');
                            } else {
                                $error = "<br>Error al modificar el voto del votante";
                            }
                        }
                    }
                }
            }
        }
        require __DIR__ . '/../../app/plantillas/inicioInterventor.inc';
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
                            $error = "<br>Error: El nombre de usuario ya existe o es duplicado";
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
            // Guarda cambios si es distinto
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
