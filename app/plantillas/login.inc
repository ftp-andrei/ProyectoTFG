<?php
/*´ Página de Login
*/
?>
<?php ob_start(); ?>

<form method="post">
  <fieldset>
    <legend>Credenciales de Inicio</legend>
    <label for="user">Usuario: </label>
    <input type="text" name="user" id="user" placeholder="Introduce usuario" required>
    <label for="pass">Contraseña: </label>
    <input type="password" name="pass" id="pass" placeholder="Introduce contraseña" required>
    <br>
    <input type="submit" value="Entrar" name="okLogin">
  </fieldset>
  <?= isset($usuario) ? "<span style='color:red'>" . $error . "</span>" : "" ?>
</form>

<?php $contenido = ob_get_clean();
include 'base.php'; ?>