<?php
/*´ Página al iniciar sesion el admin. Le pregunta si desea generar mesas
*/
?>
<?php ob_start(); ?>
<form method="post">
    <fieldset>
        <legend>¿Desea generar mesas?</legend>
        <input type="submit" name="Si" value="Si">
        <input type="submit" name="No" value="No">
    </fieldset>
</form>

<?php $contenido = ob_get_clean();
include 'base.php'; ?>