<?php
/* Página de Login */
ob_start();
echo "<script src='web/js/login.js'></script>";
?>

<form method="post" id="loginForm">
  <fieldset>
    <legend>Credenciales de Inicio</legend>
    <label for="user">Usuario: </label>
    <input type="text" name="user" id="user" placeholder="Introduce usuario" class="inputLogin" required>
    <label for="pass">Contraseña: </label>
    <input type="password" name="pass" id="pass" placeholder="Introduce contraseña" class="inputLogin" required>
    <br>
    <input type="submit" value="Entrar" name="okLogin" id="okLogin">
  </fieldset>
  <?= isset($usuario) ? "<span>" . $error . "</span>" : "" ?>
</form>

<?php $contenido = ob_get_clean();
include 'base.php'; ?>