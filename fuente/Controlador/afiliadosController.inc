<?php

namespace app\EleccionesSindicales\controlador;

use app\EleccionesSindicales\repositorio\AfiliadosRepositorio;

class AfiliadosController
{

    // Le muestra al admin la pagina de afiliados
    public function verAfiliados()
    {
        $titulo = (new TitleController())->setTitle('Afiliados - ANPE');
        $afiliados = (new AfiliadosRepositorio())->getAfiliados();
        // Elimina un afiliado
        foreach ($afiliados as $afiliado) {
            if (isset($_POST["remove_{$afiliado['IdVotante']}"])) {
                if ($borraAfiliado = (new AfiliadosRepositorio())->borraAfiliado($afiliado['IdVotante'])) {
                    header('Location: index.php?ctl=gestionAfiliados');
                } else {
                    $error = "Error al borrar afiliado";
                }
            }
        }

        // Guardar cambios
        if (isset($_POST["guardarCambios"])) {
            $arr = [];
            $tamano = sizeof($afiliados);
            for ($i = 0; $i < $tamano; $i++) {
                $apellido1 = $afiliados[$i]['Apellido1'];
                $apellido2 = $afiliados[$i]['Apellido2'];
                $nombre = $afiliados[$i]['Nombre'];
                $nif = $afiliados[$i]['NIF'];
                $telf = $afiliados[$i]['Telefono'];
                $direccion = $afiliados[$i]['Direccion'];
                $email = $afiliados[$i]['Direccion'];
                $codCentro = $afiliados[$i]['CodCentro'];
                $nombreCentro = $afiliados[$i]['NombreCentro'];
                $voto = $afiliados[$i]['Voto'];
                $fecha = $afiliados[$i]['Fecha'];
                // POST apellido1
                if (isset($_POST["apellido1_{$afiliados[$i]['IdVotante']}"])) {
                    $apellido1 = $_POST["apellido1_{$afiliados[$i]['IdVotante']}"];
                }
                // POST apellido2
                if (isset($_POST["apellido2_{$afiliados[$i]['IdVotante']}"])) {
                    $apellido2 = $_POST["apellido2_{$afiliados[$i]['IdVotante']}"];
                }
                // POST nombre
                if (isset($_POST["nombre_{$afiliados[$i]['IdVotante']}"])) {
                    $nombre = $_POST["nombre_{$afiliados[$i]['IdVotante']}"];
                }
                // POST nif
                if (isset($_POST["NIF_{$afiliados[$i]['IdVotante']}"])) {
                    if ($_POST["NIF_{$afiliados[$i]['IdVotante']}"] != $nif) {
                        // Comprueba si existe el NIF
                        // Array_search busca si en los post se a introducido varios dnis iguales. Cambia solo el 1ero
                        if ($existe = (new AfiliadosRepositorio())->existeNIF($_POST["NIF_{$afiliados[$i]['IdVotante']}"]) && array_search($_POST["NIF_{$afiliados[$i]['IdVotante']}"], array_column($arr, 'NIF')) === false) {
                            $nif = $_POST["NIF_{$afiliados[$i]['IdVotante']}"];
                        } else {
                            $error = "<br>Error: El NIF ya existe o es duplicado";
                        }
                    }
                }
                // POST Telf centro
                if (isset($_POST["Telefono_{$afiliados[$i]['IdVotante']}"])) {
                    $telf = $_POST["Telefono_{$afiliados[$i]['IdVotante']}"];
                }
                // POST Direccion centro
                if (isset($_POST["Direccion_{$afiliados[$i]['IdVotante']}"])) {
                    $direccion = $_POST["Direccion_{$afiliados[$i]['IdVotante']}"];
                }
                // POST Email centro
                if (isset($_POST["Email_{$afiliados[$i]['IdVotante']}"])) {
                    $email = $_POST["Email_{$afiliados[$i]['IdVotante']}"];
                }
                // POST Cod centro
                if (isset($_POST["CodCentro_{$afiliados[$i]['IdVotante']}"])) {
                    $codCentro = $_POST["CodCentro_{$afiliados[$i]['IdVotante']}"];
                }
                // POST Nombre centro
                if (isset($_POST["NombreCentro_{$afiliados[$i]['IdVotante']}"])) {
                    $nombreCentro = $_POST["NombreCentro_{$afiliados[$i]['IdVotante']}"];
                }
                // POST Voto
                if (isset($_POST["optSelectVoto_{$afiliados[$i]['IdVotante']}"])) {
                    $voto = $_POST["optSelectVoto_{$afiliados[$i]['IdVotante']}"];
                    if (intval($voto) && $fecha == "1900-01-01 00:00:00.000") {
                        $fecha = date("Y-m-d H:i:s");
                    } else {
                        if (!intval($voto)) {
                            $fecha = "";
                        }
                    }
                }
                $arr[$i]["IdVotante"] = $afiliados[$i]['IdVotante'];
                $arr[$i]["Nombre"] = $nombre;
                $arr[$i]["Apellido1"] = $apellido1;
                $arr[$i]["Apellido2"] = $apellido2;
                $arr[$i]["NIF"] = $nif;
                $arr[$i]["Telefono"] = $telf;
                $arr[$i]["Direccion"] = $direccion;
                $arr[$i]["Email"] = $email;
                $arr[$i]["CodCentro"] = $codCentro;
                $arr[$i]["NombreCentro"] = $nombreCentro;
                $arr[$i]["Voto"] = $voto;
                $arr[$i]["Fecha"] = $fecha;
            }
            // Guarda cambios si es distinto
            if ($arr != $afiliados) {
                if ($guardarVotante = (new AfiliadosRepositorio())->guardarCambiosAfiliados($arr)) {
                    header('Location: index.php?ctl=gestionAfiliados');
                } else {
                    $error = "<br>Error al guardar los cambios";
                }
            }
        }


        require __DIR__ . '/../../app/plantillas/gestionAfiliados.inc';
    }
}
