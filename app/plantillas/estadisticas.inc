<?php
/*´ Página de estadísticas del admin
*/
?>
<?php ob_start();
if (isset($_SESSION['admin'])) {
?>

    <h1>Estadísticas</h1>

<?php
} else { ?>
    <h1 id="errPerms">No tienes los permisos suficientes para acceder a esta página</h1>
<?php
}
$contenido = ob_get_clean();
include 'base.php'; ?>