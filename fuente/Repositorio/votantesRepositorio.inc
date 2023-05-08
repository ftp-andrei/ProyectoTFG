<?php

namespace app\EleccionesSindicales\repositorio;

use ConexionBd;
use DateTime;

class VotantesRepositorio
{
    // Devuelve todos los votantes
    public function getVotantes(): array
    {
        $sql = 'SELECT IdVotante,Nombre,Apellido1,Apellido2,NIF,CodCentro,NombreCentro,idMesa,Voto,Fecha FROM votantes ORDER BY IdVotante asc';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->execute();
            //Fetch devuelve un array
            $fila = $snt->fetchAll(\PDO::FETCH_ASSOC);
            return $fila;
        } catch (\PDOException $th) {
            throw $th;
        } finally {
            if (isset($snt)) {
                unset($snt);
                unset($con);
            }
        }
    }

    public function guardarCambiosVotantes(int $IdVotante, string $Nombre, string $Apellido1, string $Apellido2, string $NIF, string $CodCentro, string $NombreCentro, int $idMesa, string $Voto, DateTime $Fecha)
    {
        // $sql = 'SELECT IdVotante,Nombre,Apellido1,Apellido2,NIF,CodCentro,NombreCentro,idMesa,Voto,Fecha FROM votantes ORDER BY IdVotante asc';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->execute();
            //Fetch devuelve un array
            $fila = $snt->fetchAll(\PDO::FETCH_ASSOC);
            return $fila;
        } catch (\PDOException $th) {
            throw $th;
        } finally {
            if (isset($snt)) {
                unset($snt);
                unset($con);
            }
        }
    }
}
