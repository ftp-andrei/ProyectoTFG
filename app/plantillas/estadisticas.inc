<?php
/*´ Página de estadísticas del admin
*/
ob_start();
if (isset($_SESSION['admin'])) {
?>

    <h2>Estadísticas</h2>

<?php
} else { ?>
    <h2 id="errPerms">No tienes los permisos suficientes para acceder a esta página</h2>
<?php
}
$contenido = ob_get_clean();
include 'base.php'; ?>