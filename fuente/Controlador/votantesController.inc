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

        // Descarga los datos en formato csv
        if (isset($_POST['exportarDatos'])) {
            $this->descargarCSV($votantes);
        }

        // Elimina un votante
        foreach ($votantes as $votante) {
            if (isset($_POST["remove_{$votante['IdVotante']}"])) {
                if ($borraVotante = (new VotantesRepositorio())->borraVotante($votante['IdVotante'])) {
                    header('Location: index.php?ctl=gestionVotantes');
                } else {
                    $error = "Error al borrar votante";
                }
            }
        }
        if (isset($_POST['resetVotos'])) {
            if ($resetVotos = (new VotantesRepositorio())->resetVotos()) {
                header('Location: index.php?ctl=gestionVotantes');
            } else {
                $error = "Error al resetear los votos";
            }
        }

        // Guardar cambios
        if (isset($_POST["guardarCambios"])) {
            $arr = [];
            $tamano = sizeof($votantes);
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
                    if ($_POST["NIF_{$votantes[$i]['IdVotante']}"] != $nif) {
                        // Comprueba si existe el NIF
                        // Array_search busca si en los post se a introducido varios dnis iguales. Cambia solo el 1ero
                        if ($existe = (new VotantesRepositorio())->existeNIF($_POST["NIF_{$votantes[$i]['IdVotante']}"]) && array_search($_POST["NIF_{$votantes[$i]['IdVotante']}"], array_column($arr, 'NIF')) === false) {
                            $nif = $_POST["NIF_{$votantes[$i]['IdVotante']}"];
                        } else {
                            $error = "<br>Error: El NIF ya existe o es duplicado";
                        }
                    }
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
                    if (intval($voto) && $fecha == "1900-01-01 00:00:00.000") {
                        $fecha = date("Y-m-d H:i:s");
                    } else {
                        if (!intval($voto)) {
                            $fecha = "";
                        }
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
            // Guarda cambios si es distinto
            if ($arr != $votantes && $error == null) {
                if ($guardarVotante = (new VotantesRepositorio())->guardarCambiosVotantes($arr)) {
                    header('Location: index.php?ctl=gestionVotantes');
                } else {
                    $error = "<br>Error al guardar los cambios";
                }
            }
        }

        require __DIR__ . '/../../app/plantillas/gestionVotantes.inc';
    }

    public function descargarCSV($votantes)
    {
        // Limpiamos el contenido
        ob_end_clean();
        // Cogemos la hora actual
        $hora_actual = date('Y-m-d_His');
        // Nombre del archivo CSV
        $archivo = 'datosVotantes_' . $hora_actual . '.csv';

        // Abrir el archivo en modo escritura
        $manejador = fopen($archivo, 'w');
        // Añadimos las cabeceras
        fputcsv($manejador, array('IdVotante', 'Nombre', 'Apellido1', 'Apellido2', 'NIF', 'CodCentro', 'NombreCentro', 'idMesa', 'Voto', 'Fecha'));
        // Escribir los datos en el archivo
        foreach ($votantes as $fila) {
            fputcsv($manejador, $fila);
        }

        // Cerrar el archivo
        fclose($manejador);
        // Descargar el archivo CSV
        header("Content-Disposition: attachment; filename=\"$archivo\"");
        header("Content-Type: application/csv;charset=utf-8");
        readfile($archivo);
        // Salimos para evitar que nos cargue el html
        exit;
    }
}
