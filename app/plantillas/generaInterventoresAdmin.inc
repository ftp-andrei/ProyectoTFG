<?php
/*´ Pagina para generar interventores inicio admin
*/
?>
<?php ob_start(); ?>
<form method="post">
    <fieldset>
        <legend>¿Cuantos interventores desea generar? (Borra los anteriores)</legend>
        <label for="interventores">Numero de Interventores: </label>
        <input type="number" name="numeroInterventores" id="interventores" min="1" required>
        <input type="submit" name="okGenerarInterventores" value="Generar">
    </fieldset>
</form>

<?php $contenido = ob_get_clean();
include 'base.php'; ?>