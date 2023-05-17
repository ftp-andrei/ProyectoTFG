<?php

namespace app\EleccionesSindicales\repositorio;

use ConexionBd;

class AfiliadosRepositorio
{
    public function getAfiliados(): array
    {
        $sql = 'SELECT IdVotante,Nombre,Apellido1,Apellido2,NIF,Telefono,Direccion,Email,CodCentro,NombreCentro,Voto,Fecha FROM Afiliados ORDER BY Apellido1,Apellido2,Nombre,NIF';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->execute();

            $arr = $snt->fetchAll(\PDO::FETCH_ASSOC);
            return $arr;
        } catch (\PDOException $th) {
            throw $th;
        } finally {
            if (isset($snt)) {
                unset($snt);
                unset($con);
            }
        }
    }

    // Elimina un afiliado por IdVotante
    public function borraAfiliado(int $id): bool
    {
        $sql = 'DELETE FROM afiliados WHERE IdVotante=:IdVotante';

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

    // Funcion que devuelve si existe o no el nif
    public function existeNIF(string $nif): bool
    {
        // SQL para comprobar si existe el NIF
        $sql = 'SELECT count(NIF) as "nif" FROM Afiliados WHERE NIF = :nif';
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

    // Guarda los cambios en los afiliados
    public function guardarCambiosAfiliados(array $arr): bool
    {
        // 120 -> indica que el valor a convertir está en el formato 'YYYY-MM-DD'.
        $sql = 'UPDATE afiliados SET Nombre=:Nombre,Apellido1=:Apellido1,Apellido2=:Apellido2,NIF=:NIF,Telefono=:telf,Direccion=:direccion,Email=:email,
        CodCentro=:CodCentro,NombreCentro=:NombreCentro,Voto=:Voto,Fecha=Convert(datetime,:Fecha,120) WHERE IdVotante=:IdVotante';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $con->beginTransaction();
            foreach ($arr as $afiliado) {
                $snt = $con->prepare($sql);
                $snt->bindValue(':IdVotante', $afiliado['IdVotante']);
                $snt->bindValue(':Nombre', $afiliado['Nombre']);
                $snt->bindValue(':Apellido1', $afiliado["Apellido1"]);
                $snt->bindValue(':Apellido2', $afiliado["Apellido2"]);
                $snt->bindValue(':NIF', $afiliado["NIF"]);
                $snt->bindValue(':telf', $afiliado["Telefono"]);
                $snt->bindValue(':direccion', $afiliado["Direccion"]);
                $snt->bindValue(':email', $afiliado["Email"]);
                $snt->bindValue(':CodCentro', $afiliado["CodCentro"]);
                $snt->bindValue(':NombreCentro', $afiliado["NombreCentro"]);
                $snt->bindValue(':Voto', $afiliado["Voto"]);
                $snt->bindValue(':Fecha', $afiliado["Fecha"]);
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
}
