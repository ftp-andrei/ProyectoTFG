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
?>
        <form method="post">
            <span id="copiado"></span>
            <br>
            <div id="scrollable">
                <table id="tabla">
                    <caption>Lista de votantes</caption>
                    <thead>
                        <tr>
                            <th>Primer Apellido <i class="fa-sharp fa-solid fa-sort" id="ap1"></i></th>
                            <th>Segundo Apellido <i class="fa-sharp fa-solid fa-sort" id="ap2"></i></th>
                            <th>Nombre <i class="fa-sharp fa-solid fa-sort" id="nombre"></i></th>
                            <th>NIF <i class="fa-sharp fa-solid fa-sort" id="nif"></i></th>
                            <th>Codigo Centro <i class="fa-sharp fa-solid fa-sort" id="codCentro"></i></th>
                            <th>Nombre Centro <i class="fa-sharp fa-solid fa-sort" id="nombreCentro"></i></th>
                            <th>Voto <i class="fa-sharp fa-solid fa-sort" id="voto"></i></th>
                            <th>Fecha <i class="fa-sharp fa-solid fa-sort" id="fecha"></i></th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php foreach ($listaInterventor as $votante) { ?>
                            <tr>
                                <td><input type="text" name="apellido1_<?= $votante['IdVotante']; ?>" value="<?= $votante['Apellido1']; ?>" class="apellido1Votante" disabled></td>
                                <td><input type="text" name="apellido2_<?= $votante['IdVotante']; ?>" value="<?= $votante['Apellido2']; ?>" class="apellido2Votante" disabled></td>
                                <td><input type="text" name="nombre_<?= $votante['IdVotante']; ?>" value="<?= $votante['Nombre']; ?>" class="nombreVotante" disabled minlength="1"></td>
                                <td><input type="text" name="<?= $votante['NIF']; ?>" value="<?= $votante['NIF']; ?>" class="NIFVotante" disabled minlength="9" maxlength="9" required></td>
                                <td><input type="text" name="CodCentro_<?= $votante['IdVotante']; ?>" value="<?= $votante['CodCentro']; ?>" class="CodCentroVotante" disabled></td>
                                <td><input type="text" name="NombreCentro_<?= $votante['IdVotante']; ?>" value="<?= $votante['NombreCentro']; ?>" class="NombreCentroVotante" disabled></td>
                                <td><button type="submit" name="votoSi_<?= $votante['IdVotante']; ?>" id="votoSi" value="1"><i class="fa-solid fa-check"></i></button> | <button type="submit" name="votoNo_<?= $votante['IdVotante']; ?>" id="votoNo" value="0"><i class="fa-solid fa-xmark"></i></button></td>
                                <td><input type="datetime" name="Fecha_<?= $votante['IdVotante']; ?>" class="FechaVotante" value="<?php if ($votante['Fecha'] !== "1900-01-01 00:00:00.000") {
                                                                                                                                        echo substr($votante['Fecha'], 0, -4);
                                                                                                                                    } else {
                                                                                                                                        echo "Sin fecha de voto";
                                                                                                                                    }
                                                                                                                                    ?>" disabled>
                                </td>
                            </tr>
                        <?php } ?>
                    </tbody>
                </table>
            </div>
            <?= isset($guardarVotante) ? "<span>" . $error . "</span>" : "" ?>
        </form>
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