<?php
/* Estadísticas - Admin */

ob_start();
if (isset($_SESSION['admin'])) {
    // JS
    echo "<script src='web/js/estadisticas.js'></script>" .
        // Importo la libreria Chart para el grafico
        "<script src='https://cdn.jsdelivr.net/npm/chart.js'></script>" .
        // Paso el array de php a javascript
        "<script> let datos = " . json_encode($estadisticasVotantes) . "</script>";
?>

    <div id="ajuste">
        <div class="enLinea">
            <div id="scrollable">
                <table id="estadisticasVotantes">
                    <caption>Votantes</caption>
                    <thead>
                        <th>Nº mesa</th>
                        <th>Nº votantes</th>
                        <th>Han votado</th>
                        <th>No han votado</th>
                    </thead>
                    <tbody>
                        <?php foreach ($estadisticasVotantes as $mesaVotante) { ?>
                            <tr>
                                <td><input type="text" name="numeroMesa_<?= $mesaVotante['idMesa']; ?>" value="<?= $mesaVotante['idMesa']; ?>" class="numeroMesaV" disabled></td>
                                <td><input type="text" name="numeroVotantesV<?= $mesaVotante['idMesa']; ?>" value="<?= $mesaVotante['TotalVotantes']; ?>" class="numeroVotantesV" disabled></td>
                                <td><input type="text" name="hanvotadoV<?= $mesaVotante['idMesa']; ?>" value="<?= $mesaVotante['VotadoV']; ?>" class="hanvotadoV" disabled></td>
                                <td><input type="text" name="nohanVotadoV<?= $mesaVotante['idMesa']; ?>" value="<?= $mesaVotante['NoVotadoV']; ?>" class="nohanVotadoV" disabled></td>
                            </tr>
                        <?php }
                        foreach ($recuentoTotal as $recuento) { ?>
                            <tr>
                                <td><input type="text" value="Total" class="numeroMesaV" disabled></td>
                                <td><input type="text" name="numeroVotantesV<?= $recuento['TotalVotantes']; ?>" value="<?= $recuento['TotalVotantes']; ?>" class="numeroVotantesV" disabled></td>
                                <td><input type="text" name="hanvotadoV<?= $recuento['VotadoV']; ?>" value="<?= $recuento['VotadoV']; ?>" class="hanvotadoV" disabled></td>
                                <td><input type="text" name="nohanVotadoV<?= $recuento['NoVotadoV']; ?>" value="<?= $recuento['NoVotadoV']; ?>" class="nohanVotadoV" disabled></td>
                            </tr>
                        <?php } ?>
                    </tbody>
                </table>
            </div>
        </div>
        <div class="enLinea">
            <div class="enBloque">
                <table id="estadisticasAfiliados">
                    <caption>Afiliados</caption>
                    <thead>
                        <th>Nº afiliados</th>
                        <th>Han votado</th>
                        <th>No han votado</th>
                    </thead>
                    <tbody>
                        <tr>
                            <td><input type="text" name="numeroVotantesA<?= $estadisticasAfiliados['TotalAfiliados']; ?>" value="<?= $estadisticasAfiliados['TotalAfiliados']; ?>" class="numeroVotantesA" disabled></td>
                            <td><input type="text" name="hanvotadoA<?= $estadisticasAfiliados['VotadoA']; ?>" value="<?= $estadisticasAfiliados['VotadoA']; ?>" class="hanvotadoA" disabled></td>
                            <td><input type="text" name="nohanVotadoA<?= $estadisticasAfiliados['NoVotadoA']; ?>" value="<?= $estadisticasAfiliados['NoVotadoA']; ?>" class="nohanVotadoA" disabled></td>
                        </tr>
                    </tbody>
                </table>
                <canvas id="grafico"></canvas>
            </div>
        </div>
    </div>
<?php
} else { ?>
    <h2 id="errPerms">No tienes los permisos suficientes para acceder a esta página</h2>
<?php
}
$contenido = ob_get_clean();
include 'base.php'; ?>