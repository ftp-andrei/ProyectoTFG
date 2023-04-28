<?php

namespace app\EleccionesSindicales\repositorio;

use ConexionBd;

class InterventorRepositorio
{
    // Login del interventor
    public function loginInterventor(string $user, string $password): bool
    {
        $sql = 'SELECT usuario,password FROM Admin WHERE usuario = :user AND password = :password';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->bindValue(':user', $user);
            $snt->bindValue(':password', $password);
            $snt->execute();
            //Fetch devuelve un array
            $fila = $snt->fetch(\PDO::FETCH_ASSOC);
            // Devuelve true si existe
            return !(empty($fila));
        } catch (\PDOException $th) {
            throw $th;
        } finally {
            if (isset($snt)) {
                unset($snt);
                unset($con);
            }
        }
    }

    // Metodo que genera interventores al iniciar sesion el admin
    public function generaInterventorAdmin()
    {
        // Coge el numero de interventores
        // $sql = 'SELECT count(usuario) FROM Interventor';
        $sql = 'SELECT count(*) FROM Interventor WHERE "usuario"=(SELECT TOP 1 SUBSTRING("usuario",6,10) FROM Interventor ORDER BY "usuario" desc)';
        // SQL inserta Interventores
        $sql2 = 'INSERT INTO Interventor ("usuario", "password","idMesa") VALUES (:usuario,:password,:idMesa)';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->execute();
            //Fetch devuelve un array con el numero de interventores
            $fila = $snt->fetch(\PDO::FETCH_ASSOC);
            if (!$fila) {
                $fila[''] = 0;
            }

            // Preparamos la siguiente sentencia
            // $snt = $con->prepare($sql2);
            // $snt->bindValue(':usuario', 'interventor' . $fila[''] + 1);
            // $snt->bindValue(':password', $password);
            // $snt->execute();
            //Fetch devuelve un array
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
    // Metodo que borra todos los interventores
    public function borraTodosInterventores()
    {
        $sql = 'DELETE FROM Interventor';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->execute();
            if ($snt->execute()) {
                return true;
            } else {
                return false;
            }
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
