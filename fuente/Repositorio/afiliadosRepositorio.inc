<?php

namespace app\EleccionesSindicales\repositorio;

use ConexionBd;

class AfiliadosRepositorio
{
    public function getAfiliados(): array
    {
        $sql = 'SELECT IdVotante,Nombre,Apellido1,Apellido2,NIF,Telefono,Direccion,Email,CodCentro,NombreCentro,Voto,Fecha FROM Afiliados ORDER BY IdVotante asc';
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
}
