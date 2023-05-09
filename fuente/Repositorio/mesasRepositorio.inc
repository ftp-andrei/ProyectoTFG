<?php

namespace app\EleccionesSindicales\repositorio;

use ConexionBd;

class MesasRepositorio
{
    // Genera mesas al iniciar sesion el admin, borrando el resto
    public function generaMesasAdmin(int $numMesa)
    {
        // SQL inserta nombres
        $sql = 'INSERT INTO Mesas (idMesa,nombre) VALUES (:numMesa,:nombre)';
        // SQL borra todos los registros de mesas
        $sql2 = 'DELETE FROM Mesas';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql2);
            if ($snt->execute()) {
                for ($i = 0; $i <= $numMesa; $i++) {
                    $snt = $con->prepare($sql);
                    $snt->bindValue(':numMesa', $i);
                    if ($i == 0) {
                        $snt->bindValue(':nombre', "Sin Asignar");
                    } else {
                        $snt->bindValue(':nombre', "Sin Nombre");
                    }
                    $snt->execute();
                }
                return true;
            }
            return false;
        } catch (\PDOException $th) {
            throw $th;
        } finally {
            if (isset($snt)) {
                unset($snt);
                unset($con);
            }
        }
    }
    // Añade una mesa
    public function generaMesa(): bool
    {
        $sql = 'SELECT MAX(idMesa) AS mayor_numero_mesa
        FROM Mesas';
        $sql2 = 'INSERT INTO Mesas (idMesa,nombre) VALUES (:numMesa,:nombre)';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            if ($snt->execute()) {
                $fila = $snt->fetch(\PDO::FETCH_ASSOC);
                $snt = $con->prepare($sql2);
                $snt->bindValue(':numMesa', $fila["mayor_numero_mesa"] + 1);
                $snt->bindValue(':nombre', "Sin Nombre");
                if ($snt->execute()) {
                    return true;
                }
                return false;
            }
            return false;
        } catch (\PDOException $th) {
            throw $th;
        } finally {
            if (isset($snt)) {
                unset($snt);
                unset($con);
            }
        }
    }
    // Devuelve un array con todas las mesas
    public function getAllMesas()
    {
        $sql = 'SELECT idMesa,nombre FROM Mesas';
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
    // Borra una mesa por id
    public function borraMesa(int $idMesa)
    {
        $sql = 'DELETE FROM Mesas WHERE idMesa = :idMesa';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->bindValue(':idMesa', $idMesa);
            if ($snt->execute()) {
                return true;
            }
            return false;
        } catch (\PDOException $th) {
            throw $th;
        } finally {
            if (isset($snt)) {
                unset($snt);
                unset($con);
            }
        }
    }

    public function guardarCambiosMesa(string $nombre, int $idMesa)
    {
        $sql = 'UPDATE Mesas SET nombre = :nombre WHERE idMesa = :idMesa';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->bindValue(':nombre', $nombre);
            $snt->bindValue(':idMesa', $idMesa);
            if ($snt->execute()) {
                return true;
            }
            return false;
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
