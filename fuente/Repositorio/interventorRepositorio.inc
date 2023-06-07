<?php

namespace app\EleccionesSindicales\repositorio;

use ConexionBd;

class InterventorRepositorio
{
    // Login del interventor
    public function loginInterventor(string $user, string $password): bool
    {
        $sql = 'SELECT usuario,password FROM Interventor WHERE usuario = :user AND password = :password';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->bindValue(':user', $user);
            $snt->bindValue(':password', $password);
            $snt->execute();
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
    // Comprueba si existe o no el interventor - Admin
    public function existeInterventor(string $user): bool
    {
        // SQL para comprobar si existe el interventor
        $sql = 'SELECT count(usuario) as "usuarios" FROM Interventor WHERE usuario = :usuario';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->bindValue(':usuario', $user);
            $snt->execute();
            $fila = $snt->fetch(\PDO::FETCH_ASSOC);
            return empty($fila['usuarios']);
        } catch (\PDOException $th) {
            throw $th;
        } finally {
            if (isset($snt)) {
                unset($snt);
                unset($con);
            }
        }
    }

    // Genera interventor - Admin 
    public function generaInterventorAdmin(string $password): bool
    {
        // Coge el numero mayor de interventores
        $sql = 'SELECT MAX(CAST(SUBSTRING("usuario", 6, LEN("usuario")) AS INT)) AS mayor_numero_usuario
        FROM Interventor';
        // SQL inserta interventor
        $sql2 = 'INSERT INTO Interventor ("usuario", "password","idMesa") VALUES (:usuario,:password,0)';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->execute();
            $fila = $snt->fetch(\PDO::FETCH_ASSOC);

            $snt = $con->prepare($sql2);
            $snt->bindValue(':usuario', 'inter' . $fila['mayor_numero_usuario'] + 1);
            $snt->bindValue(':password', $password);
            // No pongo la mesa ya que por default es 0.
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

    // Borra un interventor por id - Admin
    public function borraInterventor(int $idInterventor): bool
    {
        $sql = 'DELETE FROM Interventor WHERE IdInterventor = :idInterventor';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->bindValue(':idInterventor', $idInterventor);
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
    // Devuelve un array con todos los interventores - Admin
    public function getAllInterventores(): array
    {
        $sql = 'SELECT IdInterventor,usuario,password,i.idMesa FROM Interventor i JOIN Mesas m ON i.idMesa = m.IdMesa ORDER BY IdInterventor asc';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->execute();

            $arrInterventores = $snt->fetchAll(\PDO::FETCH_ASSOC);
            return $arrInterventores;
        } catch (\PDOException $th) {
            throw $th;
        } finally {
            if (isset($snt)) {
                unset($snt);
                unset($con);
            }
        }
    }
    // Guarda los cambios realizados por el admin de gestion interventores
    public function guardarCambiosInterventores(array $arr): bool
    {
        $sql = 'UPDATE Interventor SET usuario = :usuario, password = :password, idMesa = :idMesa WHERE IdInterventor = :IdInterventor';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $con->beginTransaction();
            foreach ($arr as $interventor) {
                $snt = $con->prepare($sql);
                $snt->bindValue(':IdInterventor', $interventor['IdInterventor']);
                $snt->bindValue(':usuario', $interventor['usuario']);
                $snt->bindValue(':password', $interventor['password']);
                $snt->bindValue(':idMesa', $interventor['idMesa']);
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
    // Devuelve un array con los votantes de una mesa - Inicio Interventor
    public function listaInterventor(string $usuario): array
    {
        $sql = 'SELECT IdVotante,Nombre,Apellido1,Apellido2,NIF,CodCentro,NombreCentro,v.idMesa,Voto,Fecha FROM Votantes v 
        JOIN Interventor i ON i.idMesa=v.idMesa WHERE usuario=:usuario ORDER BY Apellido1,Apellido2,Nombre';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->bindValue(':usuario', $usuario);
            $snt->execute();
            $arrVotantes = $snt->fetchAll(\PDO::FETCH_ASSOC);
            return $arrVotantes;
        } catch (\PDOException $th) {
            throw $th;
        } finally {
            if (isset($snt)) {
                unset($snt);
                unset($con);
            }
        }
    }
    // Cambia el voto de un votante - Interventor
    public function guardaVotoSi(string $nif): bool
    {
        $sql = 'UPDATE Votantes SET Voto = 1, Fecha = getdate() WHERE NIF = :nif';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->bindValue(':nif', $nif);
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
    // Cambia el voto de un votante - Interventor
    public function guardaVotoNo(string $nif): bool
    {
        $sql = 'UPDATE Votantes SET Voto = 0, Fecha = 0 WHERE NIF = :nif';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->bindValue(':nif', $nif);
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

    // Si coincide el nif cambia el voto. FIX votantes/afiliados
    public function coincideNIF(): bool
    {
        $sql = 'SELECT v.nif, v.voto, v.fecha
        FROM votantes v
        INNER JOIN afiliados a ON v.nif = a.nif';
        $sql2 = 'UPDATE afiliados SET voto = :voto, fecha=:fecha WHERE nif = :nif';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->execute();
            while ($fila = $snt->fetch(\PDO::FETCH_ASSOC)) {
                var_dump($fila);
                $snt2 = $con->prepare($sql2);
                $snt2->bindValue(':voto', $fila['voto']);
                $snt2->bindValue(':fecha', $fila['fecha']);
                $snt2->bindValue(':nif', $fila['nif']);
                $snt2->execute();
            }
            return true;
        } catch (\PDOException $th) {
            throw $th;
        } finally {
            if (isset($snt)) {
                unset($snt);
            }
            if (isset($snt2)) {
                unset($snt2);
            }
            if (isset($con)) {
                unset($con);
            }
        }
    }
}
