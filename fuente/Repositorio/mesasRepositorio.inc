<?php

namespace app\EleccionesSindicales\repositorio;

use ConexionBd;

class MesasRepositorio
{
    // Añade una mesa
    public function generaMesa(): bool
    {
        $sql = 'SELECT MAX(idMesa) AS mayor_numero_mesa FROM Mesas';
        $sql2 = 'INSERT INTO Mesas (idMesa,nombre) VALUES (:numMesa,:nombre)';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $con->beginTransaction();
            $snt = $con->prepare($sql);
            if ($snt->execute()) {
                $fila = $snt->fetch(\PDO::FETCH_ASSOC);
                if ($fila["mayor_numero_mesa"] == null) {
                    $fila["mayor_numero_mesa"] = 0;
                    $snt = $con->prepare($sql2);
                    $snt->bindValue(':numMesa', $fila["mayor_numero_mesa"]);
                    $snt->bindValue(':nombre', "Sin Asignar");
                    $snt->execute();
                }
                $snt = $con->prepare($sql2);
                $snt->bindValue(':numMesa', $fila["mayor_numero_mesa"] + 1);
                $snt->bindValue(':nombre', "Sin Nombre");
                if ($snt->execute()) {
                    $con->commit();
                    return true;
                }
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
    // Borra una mesa por id. En caso de que algun votante/interventor tenga asignada la mesa, la asigna a la mesa 0 (Sin Asignar).
    public function borraMesa(int $idMesa)
    {
        $sql = 'DELETE FROM Mesas WHERE idMesa = :idMesa';
        $sql2 = 'UPDATE Votantes SET idMesa = 0 WHERE idMesa= :idMesa';
        $sql3 = 'UPDATE Interventor SET idMesa = 0 WHERE idMesa= :idMesa';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $con->beginTransaction();
            $snt = $con->prepare($sql3);
            $snt->bindValue(':idMesa', $idMesa);
            if ($snt->execute()) {
                $snt = $con->prepare($sql2);
                $snt->bindValue(':idMesa', $idMesa);
                if ($snt->execute()) {
                    $snt = $con->prepare($sql);
                    $snt->bindValue(':idMesa', $idMesa);
                    if ($snt->execute()) {
                        $con->commit();
                        return true;
                    }
                }
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
