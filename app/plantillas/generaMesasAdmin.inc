<?php
/*´ Pagina para generar mesas inicio admin
*/
?>
<?php ob_start(); ?>
<form method="post">
    <fieldset>
        <legend>¿Cuantas mesas desea generar? (Borra las anteriores)</legend>
        <label for="mesas">Numero de Mesas: </label>
        <input type="number" name="numeroMesas" id="mesas" min="1" required>
        <input type="submit" name="okGenerarMesas" value="Generar">
    </fieldset>
</form>

<?php $contenido = ob_get_clean();
include 'base.php'; ?>