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
    // Funcion que devuelve si existe o no el nif
    public function existeNIF(string $nif): bool
    {
        // SQL para comprobar si existe el NIF
        $sql = 'SELECT count(NIF) as "nif" FROM Votantes WHERE NIF = :nif';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->bindValue(':nif', $nif);
            $snt->execute();
            $fila = $snt->fetch(\PDO::FETCH_ASSOC);
            return empty($fila['nif']);
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
        // 120 -> indica que el valor a convertir está en el formato 'YYYY-MM-DD'.
        $sql = 'UPDATE votantes SET Nombre=:Nombre,Apellido1=:Apellido1,Apellido2=:Apellido2,NIF=:NIF,
        CodCentro=:CodCentro,NombreCentro=:NombreCentro,idMesa=:idMesa,Voto=:Voto,Fecha=Convert(datetime,:Fecha,120) WHERE IdVotante=:IdVotante';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $con->beginTransaction();
            foreach ($arr as $votante) {
                $snt = $con->prepare($sql);
                $snt->bindValue(':IdVotante', $votante['IdVotante']);
                $snt->bindValue(':Nombre', $votante['Nombre']);
                $snt->bindValue(':Apellido1', $votante["Apellido1"]);
                $snt->bindValue(':Apellido2', $votante["Apellido2"]);
                $snt->bindValue(':NIF', $votante["NIF"]);
                $snt->bindValue(':CodCentro', $votante["CodCentro"]);
                $snt->bindValue(':NombreCentro', $votante["NombreCentro"]);
                $snt->bindValue(':idMesa', $votante["idMesa"]);
                $snt->bindValue(':Voto', $votante["Voto"]);
                $snt->bindValue(':Fecha', $votante["Fecha"]);
                $snt->execute();
            }
            if ($snt->execute()) {
                $con->commit();
                return true;
            }
            $con->rollBack();
            return false;
        } catch (\PDOException $th) {
            $con->rollBack();
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
