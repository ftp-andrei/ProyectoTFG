<?php

namespace app\EleccionesSindicales\controlador;

use app\EleccionesSindicales\repositorio\AdminRepositorio;
use app\EleccionesSindicales\repositorio\InterventorRepositorio;

class SessionController
{
  public function login()
  {
    // Si accede a login desde la ruta limpiamos la session para quitar el nav, además el logout redirige aqui
    if (isset($_SESSION['admin']) || isset($_SESSION['interventor'])) {
      unset($_SESSION['admin']);
      unset($_SESSION['interventor']);
      unset($_SESSION['usuInterventor']);
    }
    // Si se ha pulsado el botón de login
    if (isset($_POST['okLogin'])) {
      // Comprueba que exista usuario admin
      if ($usuario = (new AdminRepositorio())->loginAdmin($_POST['user'], $_POST['pass'])) {
        $_SESSION['admin'] = true;
        // Si el usuario es admin redirige a la página donde le pregunta si desea generar  mesas
        header('Location: index.php?ctl=deseaMesas');
      } else {
        // Comprueba que exista usuario interventor
        if ($usuario = (new InterventorRepositorio())->loginInterventor($_POST['user'], $_POST['pass'])) {
          // Guardo el nombre de usuario del interventor en _SESSION para luego consultar la lista de votantes
          $_SESSION['usuInterventor'] = $_POST['user'];
          $_SESSION['interventor'] = true;
          header('Location: index.php?ctl=inicioInterventor');
        } else {
          // Sino devuelve error
          $error = "<br>Error: Usuario o contraseña incorrectos.";
        }
      }
    }
    require __DIR__ . '/../../app/plantillas/login.inc';
  }
  // Devuelve al login, y este hace el unset de los sessions
  public function logout()
  {
    header('Location: index.php?ctl=login');
  }
}
