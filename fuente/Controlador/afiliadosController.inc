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

        // Descarga los datos en formato csv
        if (isset($_POST['exportarDatos'])) {
            $this->descargarCSV($afiliados);
        }
        // Elimina un afiliado
        foreach ($afiliados as $afiliado) {
            if (isset($_POST["remove_{$afiliado['IdAfiliado']}"])) {
                if ($borraAfiliado = (new AfiliadosRepositorio())->borraAfiliado($afiliado['IdAfiliado'])) {
                    header('Location: index.php?ctl=gestionAfiliados');
                } else {
                    $error = "Error al borrar afiliado";
                }
            }
        }

        if (isset($_POST['resetVotos'])) {
            if ($resetVotos = (new AfiliadosRepositorio())->resetVotos()) {
                header('Location: index.php?ctl=gestionAfiliados');
            } else {
                $error = "Error al resetear los votos";
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
                $email = $afiliados[$i]['Email'];
                $codCentro = $afiliados[$i]['CodCentro'];
                $nombreCentro = $afiliados[$i]['NombreCentro'];
                $voto = $afiliados[$i]['Voto'];
                $fecha = $afiliados[$i]['Fecha'];
                // POST apellido1
                if (isset($_POST["apellido1_{$afiliados[$i]['IdAfiliado']}"])) {
                    $apellido1 = $_POST["apellido1_{$afiliados[$i]['IdAfiliado']}"];
                }
                // POST apellido2
                if (isset($_POST["apellido2_{$afiliados[$i]['IdAfiliado']}"])) {
                    $apellido2 = $_POST["apellido2_{$afiliados[$i]['IdAfiliado']}"];
                }
                // POST nombre
                if (isset($_POST["nombre_{$afiliados[$i]['IdAfiliado']}"])) {
                    $nombre = $_POST["nombre_{$afiliados[$i]['IdAfiliado']}"];
                }
                // POST nif
                if (isset($_POST["NIF_{$afiliados[$i]['IdAfiliado']}"])) {
                    if ($_POST["NIF_{$afiliados[$i]['IdAfiliado']}"] != $nif) {
                        // Comprueba si existe el NIF
                        // Array_search busca si en los post se a introducido varios dnis iguales. Cambia solo el 1ero
                        if ($existe = (new AfiliadosRepositorio())->existeNIF($_POST["NIF_{$afiliados[$i]['IdAfiliado']}"]) && array_search($_POST["NIF_{$afiliados[$i]['IdAfiliado']}"], array_column($arr, 'NIF')) === false) {
                            $nif = $_POST["NIF_{$afiliados[$i]['IdAfiliado']}"];
                        } else {
                            $error = "<br>Error: El NIF ya existe o es duplicado";
                        }
                    }
                }
                // POST Telf centro
                if (isset($_POST["Telefono_{$afiliados[$i]['IdAfiliado']}"])) {
                    $telf = $_POST["Telefono_{$afiliados[$i]['IdAfiliado']}"];
                }
                // POST Direccion centro
                if (isset($_POST["Direccion_{$afiliados[$i]['IdAfiliado']}"])) {
                    $direccion = $_POST["Direccion_{$afiliados[$i]['IdAfiliado']}"];
                }
                // POST Email centro
                if (isset($_POST["Email_{$afiliados[$i]['IdAfiliado']}"])) {
                    $email = $_POST["Email_{$afiliados[$i]['IdAfiliado']}"];
                }
                // POST Cod centro
                if (isset($_POST["CodCentro_{$afiliados[$i]['IdAfiliado']}"])) {
                    $codCentro = $_POST["CodCentro_{$afiliados[$i]['IdAfiliado']}"];
                }
                // POST Nombre centro
                if (isset($_POST["NombreCentro_{$afiliados[$i]['IdAfiliado']}"])) {
                    $nombreCentro = $_POST["NombreCentro_{$afiliados[$i]['IdAfiliado']}"];
                }
                // POST Voto
                if (isset($_POST["optSelectVoto_{$afiliados[$i]['IdAfiliado']}"])) {
                    $voto = $_POST["optSelectVoto_{$afiliados[$i]['IdAfiliado']}"];
                    if (intval($voto) && $fecha == "1900-01-01 00:00:00.000") {
                        $fecha = date("Y-m-d H:i:s");
                    } else {
                        if (!intval($voto)) {
                            $fecha = "";
                        }
                    }
                }
                $arr[$i]["IdAfiliado"] = $afiliados[$i]['IdAfiliado'];
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
            if ($arr != $afiliados && $error == null) {
                if ($guardarVotante = (new AfiliadosRepositorio())->guardarCambiosAfiliados($arr)) {
                    header('Location: index.php?ctl=gestionAfiliados');
                } else {
                    $error = "<br>Error al guardar los cambios";
                }
            }
        }


        require __DIR__ . '/../../app/plantillas/gestionAfiliados.inc';
    }

    public function descargarCSV($votantes)
    {
        // Limpiamos el contenido
        ob_end_clean();
        // Cogemos la hora actual
        $hora_actual = date('Y-m-d_His');
        // Nombre del archivo CSV
        $archivo = 'datosAfiliados_' . $hora_actual . '.csv';

        // Abrir el archivo en modo escritura
        $manejador = fopen($archivo, 'w');
        // Añadimos las cabeceras
        fputcsv($manejador, array('IdAfiliado', 'Nombre', 'Apellido1', 'Apellido2', 'NIF', 'Telefono', 'Direccion', 'Email', 'CodCentro', 'NombreCentro', 'Voto', 'Fecha'));
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
