<?php
/*´ Pagina para generar interventores al iniciar sesion el admin
*/

ob_start();
if (isset($_SESSION['admin'])) {
?>
    <form method="post">
        <fieldset>
            <legend>¿Cuantos interventores desea generar?</legend>
            <label for="interventores">Numero de Interventores: </label>
            <input type="number" name="numeroInterventores" id="interventores" min="1" required>
            <input type="submit" name="okGenerarInterventores" value="Generar" id="okGenerar">
        </fieldset>
    </form>
    <?= isset($borra) ? "<span>" . $error . "</span>" : "" ?>
    <?= isset($genInterventor) ? "<span>" . $error . "</span>" : "" ?>

<?php
} else { ?>
    <h2 id="errPerms">No tienes los permisos suficientes para acceder a esta página</h2>
<?php
}
$contenido = ob_get_clean();
include 'base.php'; ?>