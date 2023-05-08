<?php

namespace app\EleccionesSindicales\controlador;

use app\EleccionesSindicales\repositorio\VotantesRepositorio;
// Ejemplo de controlador para página home de la aplicación
class VotantesController
{

    // Le muestra al admin la pagina de votantes
    public function verVotantes()
    {
        $titulo = (new TitleController())->setTitle('Votantes - ANPE');
        $votantes = (new VotantesRepositorio())->getVotantes();
        $mesas = (new MesasController())->getAllMesas();
        // Guardar cambios
        if (isset($_POST["guardarCambios"])) {
            foreach ($votantes as $votante) {
                $nombre = $votante['Nombre'];
                $apellido1 = $votante['Apellido1'];
                $apellido2 = $votante['Apellido2'];
                $nif = $votante['NIF'];
                $codCentro = $votante['CodCentro'];
                $nombreCentro = $votante['NombreCentro'];
                $mesa = $votante['idMesa'];
                $voto = $votante['Voto'];
                // POST nombre
                if (isset($_POST["nombre_{$votante['IdVotante']}"])) {
                    $nombre = $_POST["nombre_{$votante['IdVotante']}"];
                }
                // POST apellido1
                if (isset($_POST["apellido1_{$votante['IdVotante']}"])) {
                    $apellido1 = $_POST["apellido1_{$votante['IdVotante']}"];
                }
                // POST apellido2
                if (isset($_POST["apellido2_{$votante['IdVotante']}"])) {
                    $apellido2 = $_POST["apellido2_{$votante['IdVotante']}"];
                }
                // POST nif
                if (isset($_POST["NIF_{$votante['IdVotante']}"])) {
                    $nif = $_POST["NIF_{$votante['IdVotante']}"];
                }
                // POST Cod centro
                if (isset($_POST["CodCentro_{$votante['IdVotante']}"])) {
                    $codCentro = $_POST["CodCentro_{$votante['IdVotante']}"];
                }
                // POST Nombre centro
                if (isset($_POST["NombreCentro_{$votante['IdVotante']}"])) {
                    $nombreCentro = $_POST["NombreCentro_{$votante['IdVotante']}"];
                }
                // POST Mesa
                if (isset($_POST["optSelectMesa_{$votante['IdVotante']}"])) {
                    $mesa = $_POST["optSelectMesa_{$votante['IdVotante']}"];
                }
                // POST Voto
                if (isset($_POST["optSelectVoto_{$votante['IdVotante']}"])) {
                    $voto = $_POST["optSelectVoto_{$votante['IdVotante']}"];
                }


                // if ($guardarVotante = (new VotanteRepositorio())->guardarCambiosVotantes($user, $contrasena, $mesa, $votante['IdVotante'],$votante['Fecha'])) {
                //     continue;
                // } else {
                //     $error = "<br>Error al guardar los cambios";
                // }
            }
            // header('Location: index.php?ctl=gestionVotantes');
        }
        require __DIR__ . '/../../app/plantillas/gestionVotantes.inc';
    }
}
