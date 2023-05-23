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
    // JS
    echo "<script src='web/js/votante.js'></script>" .
        // SweetAlert
        "<script src='https://cdn.jsdelivr.net/npm/sweetalert2@11.0.17/dist/sweetalert2.min.js'></script>" .
        "<link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/sweetalert2@11.0.17/dist/sweetalert2.min.css'>";
    if (!empty($votantes)) {
?>
        <form method="post">
            <div id="scrollFiltros">
                <fieldset id="filtros">
                    <legend>Filtros</legend>
                    <label for="apellidosFiltro">Apellidos: <input type="text" name="apellidosFiltro" id="apellidosFiltro"></label>
                    <label for="nombreFiltro">Nombre: <input type="text" name="nombreFiltro" id="nombreFiltro"></label>
                    <label for="NIFfiltro">NIF: <input type="text" name="NIFfiltro" id="NIFfiltro"></label>
                    <label for="mesaFiltro">Mesa: <select name="mesaFiltro" id="mesaFiltro">
                            <option value="-1" selected="selected">Selecciona una opcion </option>
                            <?php foreach ($mesas as $mesa) { ?>
                                <option value="<?= $mesa['idMesa'] ?>"><?= $mesa['nombre'] ?> </option>
                            <?php
                            } ?>
                        </select></label>
                    <label for="inicioFecha">Inicio fecha: <input type="date" name="inicioFecha" id="inicioFecha"></label>
                    <label for="finFecha">Fin fecha: <input type="date" name="finFecha" id="finFecha"></label>
                    <input type="submit" value="Buscar" name="okFiltro" id="okFiltro">
                </fieldset>
            </div>
            <span id="copiado"></span>
            <br>
            <div id="scrollable">
                <table id="tablaVotantes">
                    <caption>Gestión de votantes</caption>
                    <thead>
                        <tr>
                            <th>Primer Apellido <i class="fa-sharp fa-solid fa-sort" id="apellido1Votante"></i></th>
                            <th>Segundo Apellido <i class="fa-sharp fa-solid fa-sort" id="apellido2Votante"></i></th>
                            <th>Nombre <i class="fa-sharp fa-solid fa-sort" id="nombreVotante"></i></th>
                            <th>NIF <i class="fa-sharp fa-solid fa-sort" id="NIFVotante"></i></th>
                            <th>Codigo Centro <i class="fa-sharp fa-solid fa-sort" id="CodCentroVotante"></i></th>
                            <th>Nombre Centro <i class="fa-sharp fa-solid fa-sort" id="NombreCentroVotante"></i></th>
                            <th>Mesa <i class="fa-sharp fa-solid fa-sort" id="optSelectMesa"></i></th>
                            <th>Voto <i class="fa-sharp fa-solid fa-sort" id="optSelectVoto"></i></th>
                            <th>Fecha <i class="fa-sharp fa-solid fa-sort" id="FechaVotante"></i></th>
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
                                    <button type="button" id="remove_<?= $votante['IdVotante']; ?>" class="eliminar">
                                        <i class="fa fa-trash"></i>
                                    </button>
                                </td>
                            </tr>
                        <?php } ?>
                    </tbody>
                </table>
            </div>
            <input type="submit" name="guardarCambios" value="Guardar cambios" class="boton" id="guardarCambios">
            <input type="submit" name="exportarDatos" value="Descargar en CSV" class="boton" id="exportarDatos">
            <input type="submit" name="resetVotos" value="Resetear votos" class="boton" id="resetVotos">
        </form>

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