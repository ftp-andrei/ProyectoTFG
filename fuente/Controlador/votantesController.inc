<?php

namespace app\EleccionesSindicales\controlador;

use app\EleccionesSindicales\repositorio\VotantesRepositorio;

class VotantesController
{

    // Le muestra al admin la pagina de votantes
    public function verVotantes()
    {
        $titulo = (new TitleController())->setTitle('Votantes - ANPE');
        $votantes = (new VotantesRepositorio())->getVotantes();
        $mesas = (new MesasController())->getAllMesas();
        var_dump(date_default_timezone_get());
        // Guardar cambios

        if (isset($_POST["guardarCambios"])) {
            $arr = [];
            $tamano = sizeof($votantes);
            var_dump("Antes de For: " . $votantes[0]['Fecha']);
            for ($i = 0; $i < $tamano; $i++) {
                $nombre = $votantes[$i]['Nombre'];
                $apellido1 = $votantes[$i]['Apellido1'];
                $apellido2 = $votantes[$i]['Apellido2'];
                $nif = $votantes[$i]['NIF'];
                $codCentro = $votantes[$i]['CodCentro'];
                $nombreCentro = $votantes[$i]['NombreCentro'];
                $mesa = $votantes[$i]['idMesa'];
                $voto = $votantes[$i]['Voto'];
                $fecha = $votantes[$i]['Fecha'];
                // POST nombre
                if (isset($_POST["nombre_{$votantes[$i]['IdVotante']}"])) {
                    $nombre = $_POST["nombre_{$votantes[$i]['IdVotante']}"];
                }
                // POST apellido1
                if (isset($_POST["apellido1_{$votantes[$i]['IdVotante']}"])) {
                    $apellido1 = $_POST["apellido1_{$votantes[$i]['IdVotante']}"];
                }
                // POST apellido2
                if (isset($_POST["apellido2_{$votantes[$i]['IdVotante']}"])) {
                    $apellido2 = $_POST["apellido2_{$votantes[$i]['IdVotante']}"];
                }
                // POST nif
                if (isset($_POST["NIF_{$votantes[$i]['IdVotante']}"])) {
                    $nif = $_POST["NIF_{$votantes[$i]['IdVotante']}"];
                }
                // POST Cod centro
                if (isset($_POST["CodCentro_{$votantes[$i]['IdVotante']}"])) {
                    $codCentro = $_POST["CodCentro_{$votantes[$i]['IdVotante']}"];
                }
                // POST Nombre centro
                if (isset($_POST["NombreCentro_{$votantes[$i]['IdVotante']}"])) {
                    $nombreCentro = $_POST["NombreCentro_{$votantes[$i]['IdVotante']}"];
                }
                // POST Mesa
                if (isset($_POST["optSelectMesa_{$votantes[$i]['IdVotante']}"])) {
                    $mesa = $_POST["optSelectMesa_{$votantes[$i]['IdVotante']}"];
                }
                // POST Voto

                if (isset($_POST["optSelectVoto_{$votantes[$i]['IdVotante']}"])) {
                    $voto = $_POST["optSelectVoto_{$votantes[$i]['IdVotante']}"];
                    if (intval($voto)) {
                        var_dump("Antes de formateo: " . $fecha);
                        $fecha = date("Y-m-d H:i:s");
                        var_dump("Despues de formateo: " . $fecha);
                    } else {
                        $fecha = "";
                    }
                }
                $arr[$i]["IdVotante"] = $votantes[$i]['IdVotante'];
                $arr[$i]["Nombre"] = $nombre;
                $arr[$i]["Apellido1"] = $apellido1;
                $arr[$i]["Apellido2"] = $apellido2;
                $arr[$i]["NIF"] = $nif;
                $arr[$i]["CodCentro"] = $codCentro;
                $arr[$i]["NombreCentro"] = $nombreCentro;
                $arr[$i]["idMesa"] = $mesa;
                $arr[$i]["Voto"] = $voto;
                $arr[$i]["Fecha"] = $fecha;
            }
            // Si es igual no va a guardar nada. PONERLO EN != CUANDO SE SOLUCIONE
            if ($arr == $votantes) {
                var_dump($arr[0]['Fecha']);
                var_dump($votantes[0]['Fecha']);
                if ($guardarVotante = (new VotantesRepositorio())->guardarCambiosVotantes($arr)) {
                    // header('Location: index.php?ctl=gestionVotantes');
                } else {
                    $error = "<br>Error al guardar los cambios";
                }
            }
        }

        // Elimina un votante
        foreach ($votantes as $votante) {
            if (isset($_POST["remove_{$votante['IdVotante']}"])) {
                if ($borraVotante = (new VotantesRepositorio())->borraVotante($votante['IdVotante'])) {
                    // header('Location: index.php?ctl=gestionVotantes');
                } else {
                    $error = "Error al borrar votante";
                }
            }
        }

        require __DIR__ . '/../../app/plantillas/gestionVotantes.inc';
    }
}
