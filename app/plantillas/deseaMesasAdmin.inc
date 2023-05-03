<?php
/*´ Página al iniciar sesion el admin. Le pregunta si desea generar mesas
*/
?>
<?php ob_start();
if (isset($_SESSION['admin'])) {
?>
    <form method="post">
        <fieldset>
            <legend>¿Desea generar mesas?</legend>
            <input type="submit" name="Si" value="Si">
            <input type="submit" name="No" value="No">
        </fieldset>
    </form>

<?php
} else { ?>
    <h1 id="errPerms">No tienes los permisos suficientes para acceder a esta página</h1>
<?php
}
$contenido = ob_get_clean();
include 'base.php'; ?>