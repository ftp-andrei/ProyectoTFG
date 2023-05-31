<?php
/* Gestion Votantes - Admin */

// Hecho: Error DNI, si no ha votado no sale duplicado
// Hecho: Regex DNI
// TODO: Intentar que el editar vuelva a su posicion original y guarde bien
// Hecho: Orden por ap1,ap2,nombre,nif
// Hecho: Filtros arriba. Intentar que sea lo mas comodo posible.
// Hecho: Boton exportar a excel
// Hecho: Mensaje de confirmacion al eliminar
// Hecho: Cambiar orden columnas
// Hecho: Filtrar columnas click (th)
// Hecho: Darle a la X al buscar, la tabla queda vacia/o con los elementos de antes

ob_start();
if (isset($_SESSION['admin'])) {
    if (!empty($votantes)) {
        // JS
        echo "<script src='web/js/votante.js'></script>" .
            // SweetAlert
            "<script src='https://cdn.jsdelivr.net/npm/sweetalert2@11.0.17/dist/sweetalert2.min.js'></script>" .
            "<link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/sweetalert2@11.0.17/dist/sweetalert2.min.css'>";
?>
        <form method="post">
            <span id="copiado"></span>
            <br>
            <label for="search" id="searchLabel">Filtro: <input type="search" id="search" placeholder="Buscar..." class="filtro"></label>
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
                            <th>Mesa</th>
                            <th>Voto</th>
                            <th>Fecha <i class="fa-sharp fa-solid fa-sort" id="FechaVotante"></i></th>
                            <th>Editar</th>
                            <th>Eliminar</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php foreach ($votantes as $votante) { ?>
                            <tr class="votante">
                                <td><input type="text" name="apellido1_<?= $votante['IdVotante']; ?>" value="<?= $votante['Apellido1']; ?>" class="apellido1Votante" disabled></td>
                                <td><input type="text" name="apellido2_<?= $votante['IdVotante']; ?>" value="<?= $votante['Apellido2']; ?>" class="apellido2Votante" disabled></td>
                                <td><input type="text" name="nombre_<?= $votante['IdVotante']; ?>" value="<?= $votante['Nombre']; ?>" class="nombreVotante" disabled minlength="1"></td>
                                <td><input type="text" name="NIF_<?= $votante['IdVotante']; ?>" value="<?= $votante['NIF']; ?>" pattern="^[XYZ]?\d{7,8}[A-Z]$" class="NIFVotante" disabled minlength="9" maxlength="9" required></td>
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
                                    </select>
                                </td>
                                <?php
                                if ($votante['Fecha'] !== "1900-01-01 00:00:00.000") {
                                    $fecha = substr($votante['Fecha'], 0, -4);
                                } else {
                                    $fecha = "Sin fecha de voto";
                                }
                                ?>
                                <td><input type="text" name="Fecha_<?= $votante['IdVotante']; ?>" class="FechaVotante" value="<?= $fecha ?>" disabled>
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
            <input type="button" value="Resetear votos" class="boton" id="resetVotos">

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