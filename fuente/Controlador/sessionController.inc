<?php

namespace app\EleccionesSindicales\controlador;

use app\EleccionesSindicales\repositorio\AdminRepositorio;
use app\EleccionesSindicales\repositorio\InterventorRepositorio;
// Ejemplo de controlador para página home de la aplicación
class SessionController
{
  public function login()
  {
    // Si accede a login desde la ruta limpiamos la session para quitar el nav, además el logout redirige aqui
    if (isset($_SESSION['admin']) || isset($_SESSION['interventor'])) {
      unset($_SESSION['admin']);
      unset($_SESSION['interventor']);
    }
    // Si se ha pulsado el botón de login
    if (isset($_POST['okLogin'])) {
      // Comprueba que exista usuario admin
      if ($usuario = (new AdminRepositorio())->loginAdmin($_POST['user'], $_POST['pass'])) {
        $_SESSION['admin'] = true;
        header('Location: index.php?ctl=deseaMesas');
      } else {
        // Comprueba que exista usuario interventor
        if ($usuario = (new InterventorRepositorio())->loginInterventor($_POST['user'], $_POST['pass'])) {
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

  public function logout()
  {
    header('Location: index.php?ctl=login');
  }
}
