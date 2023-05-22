<?php

namespace app\EleccionesSindicales\repositorio;

use ConexionBd;

class EstadisticasRepositorio
{
    // Metodo para mostrar las estadísticas de votantes. Se refrescan en el controller.
    public function estadisticasVotantes(): array
    {   //SQL Votantes
        $sql = 'SELECT m.idMesa,COUNT(vt.idVotante) AS TotalVotantes,SUM(CASE WHEN vt.voto = 1 THEN 1 ELSE 0 END) AS VotadoV,
        SUM(CASE WHEN vt.voto = 0 THEN 1 ELSE 0 END) AS NoVotadoV FROM mesas m
       LEFT JOIN votantes vt ON m.idMesa = vt.idMesa WHERE m.idMesa<> 0 GROUP BY m.idMesa';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->execute();
            $arrayEstadisticas = $snt->fetchAll(\PDO::FETCH_ASSOC);
            return $arrayEstadisticas;
        } catch (\PDOException $th) {
            throw $th;
        } finally {
            if (isset($snt)) {
                unset($snt);
                unset($con);
            }
        }
    }
    // Metodo para mostrar las estadísticas de afiliados. Se refrescan en el controller
    public function estadisticasAfiliados(): array
    {
        $sql = 'SELECT (SELECT COUNT(idAfiliado) FROM afiliados) AS TotalAfiliados,
       (SELECT COUNT(Voto) FROM afiliados WHERE Voto = 1) AS VotadoA,
       (SELECT COUNT(Voto) FROM afiliados WHERE Voto = 0) AS NoVotadoA';

        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->execute();
            $arrayEstadisticas = $snt->fetch(\PDO::FETCH_ASSOC);
            return $arrayEstadisticas;
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
