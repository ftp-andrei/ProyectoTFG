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
    // Funcion que devuelve si existe o no el interventor
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

    // Metodo que genera interventores al iniciar sesion el admin
    public function generaInterventorAdmin(string $password): bool
    {
        // Coge el numero mayor de interventores
        $sql = 'SELECT MAX(CAST(SUBSTRING("usuario", 6, LEN("usuario")) AS INT)) AS mayor_numero_usuario
        FROM Interventor';
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
    // Borra todos los interventores
    public function borraTodosInterventores(): bool
    {
        $sql = 'DELETE FROM Interventor';
        // Crear una nueva tabla para el IdInterventor =0?;
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
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

    // Borra un interventor por id
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
    // Devuelve un array con todos los interventores
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
    // Guarda los cambios realizados por el admin de los interventores
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
    // Devuelve un array con los votantes de una mesa, para el login de los interventores
    public function listaInterventor(string $usuario): array
    {
        $sql = 'SELECT IdVotante,Nombre,Apellido1,Apellido2,NIF,CodCentro,NombreCentro,v.idMesa,Voto,Fecha FROM Votantes v 
        JOIN Interventor i ON i.idMesa=v.idMesa WHERE usuario=:usuario ORDER BY IdVotante asc';
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
}
