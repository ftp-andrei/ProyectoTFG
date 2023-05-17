<?php
/*´ Página de estadísticas del admin
*/
// Solucionado: Refresh
// TODO: TH filtros?


ob_start();
if (isset($_SESSION['admin'])) {
    echo "<script src='web/js/estadisticas.js'></script>";
?>

    <div class="enLinea">
        <table>
            <caption>Votantes</caption>
            <thead>
                <th>Nº mesa <i class="fa-sharp fa-solid fa-sort"></i></th>
                <th>Nº votantes <i class="fa-sharp fa-solid fa-sort"></i></th>
                <th>Han votado <i class="fa-sharp fa-solid fa-sort"></i></th>
                <th>No han votado <i class="fa-sharp fa-solid fa-sort"></i></th>
            </thead>
            <tbody>
                <?php foreach ($estadisticasVotantes as $mesaVotante) { ?>
                    <tr>
                        <td><input type="text" name="numeroMesa_<?= $mesaVotante['idMesa']; ?>" value="<?= $mesaVotante['idMesa']; ?>" class="numeroMesaV" disabled></td>
                        <td><input type="text" name="numeroVotantesV<?= $mesaVotante['idMesa']; ?>" value="<?= $mesaVotante['TotalVotantes']; ?>" class="numeroVotantesV" disabled></td>
                        <td><input type="text" name="hanvotadoV<?= $mesaVotante['idMesa']; ?>" value="<?= $mesaVotante['VotadoV']; ?>" class="hanvotadoV" disabled></td>
                        <td><input type="text" name="nohanVotadoV<?= $mesaVotante['idMesa']; ?>" value="<?= $mesaVotante['NoVotadoV']; ?>" class="nohanVotadoV" disabled></td>
                    </tr>
                <?php } ?>
            </tbody>
        </table>
    </div>
    <div class=" enLinea">
        <table>
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
    </div>
<?php
} else { ?>
    <h2 id="errPerms">No tienes los permisos suficientes para acceder a esta página</h2>
<?php
}
$contenido = ob_get_clean();
include 'base.php'; ?>