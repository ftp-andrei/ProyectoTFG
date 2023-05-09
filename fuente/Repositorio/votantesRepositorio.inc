<?php

namespace app\EleccionesSindicales\repositorio;

use ConexionBd;

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
    // Guarda los cambios en los votantes
    public function guardarCambiosVotantes(array $arr): bool
    {
        $tamano = sizeof($arr);
        var_dump("Repo Antes de Insertar: " . $arr[1]["Fecha"]);
        $sql = 'UPDATE votantes SET Nombre=:Nombre,Apellido1=:Apellido1,Apellido2=:Apellido2,NIF=:NIF,
        CodCentro=:CodCentro,NombreCentro=:NombreCentro,idMesa=:idMesa,Voto=:Voto,Fecha=:Fecha WHERE IdVotante=:IdVotante';

        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            for ($i = 0; $i < $tamano; $i++) {
                $snt = $con->prepare($sql);
                $snt->bindValue(':IdVotante', $arr[$i]['IdVotante']);
                $snt->bindValue(':Nombre', $arr[$i]['Nombre']);
                $snt->bindValue(':Apellido1', $arr[$i]["Apellido1"]);
                $snt->bindValue(':Apellido2', $arr[$i]["Apellido2"]);
                $snt->bindValue(':NIF', $arr[$i]["NIF"]);
                $snt->bindValue(':CodCentro', $arr[$i]["CodCentro"]);
                $snt->bindValue(':NombreCentro', $arr[$i]["NombreCentro"]);
                $snt->bindValue(':idMesa', $arr[$i]["idMesa"]);
                $snt->bindValue(':Voto', $arr[$i]["Voto"]);
                $snt->bindValue(':Fecha', $arr[$i]["Fecha"]);
                $snt->execute();
            }
            return $snt->execute();
        } catch (\PDOException $th) {
            throw $th;
        } finally {
            if (isset($snt)) {
                unset($snt);
                unset($con);
            }
        }
    }
    // Elimina un votante por IdVotante
    public function borraVotante(int $id): bool
    {
        $sql = 'DELETE FROM votantes WHERE IdVotante=:IdVotante';

        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->bindValue(':IdVotante', $id);
            return $snt->execute();
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
