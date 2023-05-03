<?php
/*´ Pagina para generar mesas al iniciar sesion el admin
*/
?>
<?php ob_start();
if (isset($_SESSION['admin'])) {
?>
    <form method="post">
        <fieldset>
            <legend>¿Cuantas mesas desea generar? (Borra las anteriores)</legend>
            <label for="mesas">Numero de Mesas: </label>
            <input type="number" name="numeroMesas" id="mesas" min="1" required>
            <input type="submit" name="okGenerarMesas" value="Generar">
        </fieldset>
    </form>
<?php
} else { ?>
    <h1 id="errPerms">No tienes los permisos suficientes para acceder a esta página</h1>
<?php
}
$contenido = ob_get_clean();
include 'base.php'; ?>