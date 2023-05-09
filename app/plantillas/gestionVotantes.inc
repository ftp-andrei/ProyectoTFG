<?php
/*´ Pagina ver y gestionar votantes admin
*/
// TODO: Solucionar fechas al guardar
// Hecho: Eliminar votantes
// TODO: Revisar posibles errores (Mismo NIF)
echo "<script src='web/js/votante.js'></script>"
?>
<?php ob_start();
if (isset($_SESSION['admin'])) {
    if (!empty($votantes)) {
?>
        <form method="post">
            <span id="copiado"></span>
            <br>
            <table>
                <caption>Gestión de votantes</caption>
                <thead>
                    <tr>
                        <th>Nombre</th>
                        <th>Primer Apellido</th>
                        <th>Segundo Apellido</th>
                        <th>NIF</th>
                        <th>Codigo Centro</th>
                        <th>Nombre del Centro</th>
                        <th>Mesa</th>
                        <th>Voto</th>
                        <th>Fecha</th>
                        <th>Editar</th>
                        <th>Eliminar</th>
                    </tr>
                </thead>
                <tbody>
                    <?php foreach ($votantes as $votante) { ?>
                        <tr>
                            <td><input type="text" name="nombre_<?= $votante['IdVotante']; ?>" value="<?= $votante['Nombre']; ?>" class="nombreVotante" disabled></td>
                            <td><input type="text" name="apellido1_<?= $votante['IdVotante']; ?>" value="<?= $votante['Apellido1']; ?>" class="apellido1Votante" disabled></td>
                            <td><input type="text" name="apellido2_<?= $votante['IdVotante']; ?>" value="<?= $votante['Apellido2']; ?>" class="apellido2Votante" disabled></td>
                            <td><input type="text" name="NIF_<?= $votante['IdVotante']; ?>" value="<?= $votante['NIF']; ?>" class="NIFVotante" disabled></td>
                            <td><input type="text" name="CodCentro_<?= $votante['IdVotante']; ?>" value="<?= $votante['CodCentro']; ?>" class="CodCentroVotante" disabled></td>
                            <td><input type="text" name="NombreCentro_<?= $votante['IdVotante']; ?>" value="<?= $votante['NombreCentro']; ?>" class="NombreCentroVotante" disabled></td>
                            <td><select name="optSelectMesa_<?= $votante['IdVotante']; ?>" class="optSelectMesa" id="optSelectMesa_<?= $votante['IdVotante']; ?>" disabled>
                                    <?php foreach ($mesas as $mesa) {
                                        if ($mesa['idMesa'] == $votante['idMesa']) { ?>
                                            <option value="<?= $mesa['idMesa'] ?>" selected="selected"><?= $mesa['nombre'] ?> </option>
                                        <?php } else { ?>
                                            <option value="<?= $mesa['idMesa'] ?>"><?= $mesa['nombre'] ?> </option>
                                    <?php }
                                    } ?>
                                </select>
                            </td>
                            <td><select name="optSelectVoto_<?= $votante['IdVotante']; ?>" class="optSelectVoto" id="optSelectVoto_<?= $votante['IdVotante']; ?>" disabled>
                                    <?php
                                    if ($votante['Voto']) { ?>
                                        <option value="1" selected="selected">Sí ha votado </option>
                                        <option value="0">No ha votado </option>
                                    <?php } else { ?>
                                        <option value="0" selected="selected">No ha votado </option>
                                        <option value="1">Sí ha votado </option>
                                    <?php  } ?>
                            </td>
                            <td><input type="text" name="Fecha_<?= $votante['IdVotante']; ?>" class="FechaVotante" value="<?php
                                                                                                                            if ($votante['Fecha'] !== "1900-01-01 00:00:00.000") {
                                                                                                                                echo substr($votante['Fecha'], 0, -4);
                                                                                                                            } else {
                                                                                                                                echo "Vacio";
                                                                                                                            }
                                                                                                                            ?>" disabled>
                            </td>
                            <td><i class="fas fa-edit editar" name="editar_<?= $votante['IdVotante']; ?>"></i></td>
                            <td>
                                <button type="submit" name="remove_<?= $votante['IdVotante']; ?>" class="eliminar">
                                    <i class="fa fa-trash"></i>
                                </button>
                            </td>
                        </tr>
                    <?php } ?>
                </tbody>
            </table>
            <input type="submit" name="guardarCambios" value="Guardar cambios" class="boton" id="guardarCambios">
            <?= isset($guardarVotante) ? "<span>" . $error . "</span>" : "" ?>
            <?= isset($borraVotante) ? "<span>" . $error . "</span>" : "" ?>

        </form>

    <?php
    } else { ?>
        <h2>No existen votantes en la base de datos</h2>
    <?php
    }
} else { ?>
    <h2 id="errPerms">No tienes los permisos suficientes para acceder a esta página</h2>
<?php
}
$contenido = ob_get_clean();
include 'base.php'; ?>