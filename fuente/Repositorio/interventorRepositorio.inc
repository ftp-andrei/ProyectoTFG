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

    // Metodo que genera interventores al iniciar sesion el admin
    public function generaInterventorAdmin(string $password): bool
    {
        // Coge el numero mayor de interventores
        $sql = 'SELECT MAX(CAST(SUBSTRING("usuario", 6, LEN("usuario")) AS INT)) AS mayor_numero_usuario
        FROM Interventor';
        // SQL inserta Interventores
        $sql2 = 'INSERT INTO Interventor ("usuario", "password","idMesa") VALUES (:usuario,:password,0)';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->execute();
            //Fetch devuelve un array con el numero maximo del interventor
            $fila = $snt->fetch(\PDO::FETCH_ASSOC);
            if ($fila['mayor_numero_usuario'] == null) {
                $fila['mayor_numero_usuario'] = 0;
            }

            // Preparamos la siguiente sentencia
            $snt = $con->prepare($sql2);
            $snt->bindValue(':usuario', 'inter' . $fila['mayor_numero_usuario'] + 1);
            $snt->bindValue(':password', $password);
            // No pongo la mesa ya que por default es 0.

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
    // Metodo que borra todos los interventores
    public function borraTodosInterventores(): bool
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

    // Metodo que borra todos los interventores
    public function borraInterventor(int $idInterventor): bool
    {
        $sql = 'DELETE FROM Interventor WHERE IdInterventor = :idInterventor';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->bindValue(':idInterventor', $idInterventor);
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
    // Devuelve un array con todos los interventores
    public function getAllInterventores(): array
    {
        $sql = 'SELECT IdInterventor,usuario,password,i.idMesa,nombre FROM Interventor i JOIN Mesas m ON i.idMesa = m.IdMesa ORDER BY IdInterventor asc';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->execute();
            //Fetch devuelve un array
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
    public function guardarCambiosInterventores(string $usuario, string $password, int $idMesa, int $idInterventor): bool
    {
        $sql = 'UPDATE Interventor SET usuario = :usuario, password = :password, idMesa = :idMesa WHERE IdInterventor = :IdInterventor';
        require_once __DIR__ . '/../../core/conexionBd.inc';
        try {
            $con = (new ConexionBd())->getConexion();
            $snt = $con->prepare($sql);
            $snt->bindValue(':IdInterventor', $idInterventor);
            $snt->bindValue(':usuario', $usuario);
            $snt->bindValue(':password', $password);
            $snt->bindValue(':idMesa', $idMesa);
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
