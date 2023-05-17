<?php
/*´ Pagina de inicio del interventor
*/
// Solucionado: Errores con las rutas Y Permisos de acceso
// TODO: Menu Sticky
// TODO: Boton hacia arriba
// TODO: Cambiar el titulo de la pagina
ob_start();
if (isset($_SESSION['interventor'])) {
    echo "<script src='web/js/interventorMesa.js'></script>";
    if (!empty($listaInterventor)) {
        var_dump($listaInterventor);
?>



    <?php

    } else { ?>
        <h2 id="errPerms">No existen votantes registrados en esta mesa</h2>
    <?php
    }
} else { ?>
    <h2 id="errPerms">No tienes los permisos suficientes para acceder a esta página o estás intentando acceder como admin</h2>
<?php
}
$contenido = ob_get_clean();
include 'base.php'; ?>