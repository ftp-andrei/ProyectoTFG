<?php
/*´ Pagina de inicio del interventor
*/
?>
<?php ob_start();
if (isset($_SESSION['interventor'])) { ?>
    <h1>Inicio Interventor</h1>

<?php
}
$contenido = ob_get_clean();
include 'base.php'; ?>