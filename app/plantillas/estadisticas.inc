<?php
/*´ Página de estadísticas del admin
*/
ob_start();
if (isset($_SESSION['admin'])) {
?>
    <div id="estadisticas">
        <h2>Estadísticas</h2>
        <form method="post">
            <p>Total interventores: <?= sizeof($totalInterventores); ?></p>
            <p>Total mesas: <?= sizeof($totalMesas) - 1; ?></p>
            <p>Total votantes: <?= $totalVotantes; ?></p>
            <p>Total afiliados <?= $totalAfiliados; ?></p>
            <p>Recuento votantes:</p>
            <label>Si han votado: <?= $totalVotosSi; ?></label> <input type="submit" value="Ver" name="verVotosSi">
            <label>No han votado: <?= $totalVotosNo; ?></label> <input type="submit" value="Ver" name="verVotosSi">
        </form>
    </div>
<?php
} else { ?>
    <h2 id="errPerms">No tienes los permisos suficientes para acceder a esta página</h2>
<?php
}
$contenido = ob_get_clean();
include 'base.php'; ?>