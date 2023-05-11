<?php
/*´ Página al iniciar sesion el admin. Le pregunta si desea generar interventores.
*/
ob_start();
if (isset($_SESSION['admin'])) {
?>
    <form method="post" id="desea">
        <fieldset>
            <legend>¿Desea generar interventores?</legend>
            <input type="submit" name="Si" value="Si" id="si">
            <input type="submit" name="No" value="No" id="no">
        </fieldset>
    </form>

<?php
} else { ?>
    <h1 id="errPerms">No tienes los permisos suficientes para acceder a esta página</h1>
<?php
}
$contenido = ob_get_clean();
include 'base.php'; ?>