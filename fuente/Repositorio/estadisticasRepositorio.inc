<?php

namespace app\EleccionesSindicales\repositorio;

use ConexionBd;

class EstadisticasRepositorio
{
    // Metodo para mostrar las estadísticas totales. Se refrescan en el controller.
    public function estadisticasTotales(): array
    {
        $sql = 'count(idMesa)-1 as "NumMesas" FROM mesas';
        $sql2 = 'SELECT count(Voto) as "VotadoV" FROM votantes WHERE voto=1';
        $sql3 = 'SELECT count(Voto) as "NoVotadoV" FROM votantes WHERE voto=0';
        $sql4 = 'SELECT count(Voto) as "VotadoA" FROM afiliados WHERE voto=1';
        $sql5 = 'SELECT count(Voto) as "NoVotadoA" FROM afiliados WHERE voto=0';
        $sql6 = 'SELECT count(idVotante) as "TotalVotantes" FROM votantes';
        $sql7 = 'SELECT count(idVotante) as "TotalAfiliados" FROM afiliados';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->execute();
            $arr = $snt->fetch(\PDO::FETCH_ASSOC);
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
}
