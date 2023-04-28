<?php

namespace app\EleccionesSindicales\repositorio;

use ConexionBd;

class MesasRepositorio
{
    public function generaMesasAdmin(int $mesas, $nombre)
    {
        // SQL inserta nombres
        $sql = 'INSERT INTO Mesas (idMesa,nombre) VALUES (:mesas,:nombre)';
        // SQL borra todos los registros de mesas
        $sql2 = 'DELETE FROM Mesas';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql2);
            if ($snt->execute()) {
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
