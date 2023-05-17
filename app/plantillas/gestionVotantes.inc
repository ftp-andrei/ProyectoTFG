<?php
/*´ Pagina ver y gestionar votantes admin
*/

// TODO: Error DNI, si no ha votado no sale duplicado
// TODO: Regex DNI
// Solucionado: Orden por ap1,ap2,nombre,nif
// TODO: Filtros arriba. Intentar que sea lo mas comodo posible.
// TODO: Boton exportar a excel
// TODO: Mensaje de confirmacion al eliminar
// TODO: Cambiar orden columnas
// TODO: Filtrar columnas click (th)

ob_start();
if (isset($_SESSION['admin'])) {
    echo "<script src='web/js/votante.js'></script>";
    if (!empty($votantes)) {
?>
        <form method="post">
            <span id="copiado"></span>
            <br>
            <table id="tabla">
                <caption>Gestión de votantes</caption>
                <thead>
                    <tr>
                        <th>Primer Apellido <i class="fa-sharp fa-solid fa-sort" id="ap1"></i></th>
                        <th>Segundo Apellido <i class="fa-sharp fa-solid fa-sort" id="ap2"></i></th>
                        <th>Nombre <i class="fa-sharp fa-solid fa-sort" id="nombre"></i></th>
                        <th>NIF <i class="fa-sharp fa-solid fa-sort" id="nif"></i></th>
                        <th>Codigo Centro <i class="fa-sharp fa-solid fa-sort" id="codCentro"></i></th>
                        <th>Nombre del Centro <i class="fa-sharp fa-solid fa-sort" id="nombreCentro"></i></th>
                        <th>Mesa <i class="fa-sharp fa-solid fa-sort" id="mesa"></i></th>
                        <th>Voto <i class="fa-sharp fa-solid fa-sort" id="voto"></i></th>
                        <th>Fecha <i class="fa-sharp fa-solid fa-sort" id="fecha"></i></th>
                        <th>Editar</th>
                        <th>Eliminar</th>
                    </tr>
                </thead>
                <tbody>
                    <?php foreach ($votantes as $votante) { ?>
                        <tr>
                            <td><input type="text" name="apellido1_<?= $votante['IdVotante']; ?>" value="<?= $votante['Apellido1']; ?>" class="apellido1Votante" disabled></td>
                            <td><input type="text" name="apellido2_<?= $votante['IdVotante']; ?>" value="<?= $votante['Apellido2']; ?>" class="apellido2Votante" disabled></td>
                            <td><input type="text" name="nombre_<?= $votante['IdVotante']; ?>" value="<?= $votante['Nombre']; ?>" class="nombreVotante" disabled minlength="1"></td>
                            <td><input type="text" name="NIF_<?= $votante['IdVotante']; ?>" value="<?= $votante['NIF']; ?>" class="NIFVotante" disabled minlength="9" maxlength="9" required></td>
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
                            <td><input type="datetime" name="Fecha_<?= $votante['IdVotante']; ?>" class="FechaVotante" value="<?php if ($votante['Fecha'] !== "1900-01-01 00:00:00.000") {
                                                                                                                                    echo substr($votante['Fecha'], 0, -4);
                                                                                                                                } else {
                                                                                                                                    echo "Sin fecha de voto";
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
            <?= isset($existe) ? "<span>" . $error . "</span>" : "" ?>
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