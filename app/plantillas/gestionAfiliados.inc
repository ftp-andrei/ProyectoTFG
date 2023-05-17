<?php
/*´ Pagina ver y gestionar afiliados admin
*/



ob_start();

if (isset($_SESSION['admin'])) {
    echo "<script src='web/js/afiliados.js'></script>";
    if (!empty($afiliados)) {
?>
        <form method="post">
            <span id="copiado"></span>
            <br>
            <table>
                <caption>Gestión de afiliados</caption>
                <thead>
                    <tr>
                        <th>Primer Apellido <i class="fa-sharp fa-solid fa-sort"></th>
                        <th>Segundo Apellido <i class="fa-sharp fa-solid fa-sort"></th>
                        <th>Nombre <i class="fa-sharp fa-solid fa-sort"></th>
                        <th>NIF <i class="fa-sharp fa-solid fa-sort"></th>
                        <th>Teléfono <i class="fa-sharp fa-solid fa-sort"></th>
                        <th>Dirección <i class="fa-sharp fa-solid fa-sort"></th>
                        <th>Email <i class="fa-sharp fa-solid fa-sort"></th>
                        <th>Codigo Centro <i class="fa-sharp fa-solid fa-sort"></th>
                        <th>Nombre del Centro <i class="fa-sharp fa-solid fa-sort"></th>
                        <th>Voto <i class="fa-sharp fa-solid fa-sort"></th>
                        <th>Fecha <i class="fa-sharp fa-solid fa-sort"></th>
                        <th>Editar</th>
                        <th>Eliminar</th>
                    </tr>
                </thead>
                <tbody>
                    <?php foreach ($afiliados as $afiliado) { ?>
                        <tr>
                            <td><input type="text" name="apellido1_<?= $afiliado['IdVotante']; ?>" value="<?= $afiliado['Apellido1']; ?>" class="apellido1Votante" disabled></td>
                            <td><input type="text" name="apellido2_<?= $afiliado['IdVotante']; ?>" value="<?= $afiliado['Apellido2']; ?>" class="apellido2Votante" disabled></td>
                            <td><input type="text" name="nombre_<?= $afiliado['IdVotante']; ?>" value="<?= $afiliado['Nombre']; ?>" class="nombreVotante" disabled></td>
                            <td><input type="text" name="NIF_<?= $afiliado['IdVotante']; ?>" value="<?= $afiliado['NIF']; ?>" class="NIFVotante" disabled minlength="9" maxlength="9"></td>
                            <td><input type="tel" name="Telefono_<?= $afiliado['IdVotante']; ?>" value="<?= $afiliado['Telefono']; ?>" class="TelefonoVotante" disabled minlength="9" maxlength="9"></td>
                            <td><input type="text" name="Direccion_<?= $afiliado['IdVotante']; ?>" value="<?= $afiliado['Direccion']; ?>" class="DireccionVotante" disabled></td>
                            <td><input type="mail" name="Email_<?= $afiliado['IdVotante']; ?>" value="<?= $afiliado['Email']; ?>" class="EmailVotante" disabled></td>
                            <td><input type="text" name="CodCentro_<?= $afiliado['IdVotante']; ?>" value="<?= $afiliado['CodCentro']; ?>" class="CodCentroVotante" disabled></td>
                            <td><input type="text" name="NombreCentro_<?= $afiliado['IdVotante']; ?>" value="<?= $afiliado['NombreCentro']; ?>" class="NombreCentroVotante" disabled></td>
                            <td><select name="optSelectVoto_<?= $afiliado['IdVotante']; ?>" class="optSelectVoto" id="optSelectVoto_<?= $afiliado['IdVotante']; ?>" disabled>
                                    <?php
                                    if ($afiliado['Voto']) { ?>
                                        <option value="1" selected="selected">Sí ha votado </option>
                                        <option value="0">No ha votado </option>
                                    <?php } else { ?>
                                        <option value="0" selected="selected">No ha votado </option>
                                        <option value="1">Sí ha votado </option>
                                    <?php  } ?>
                            </td>
                            <td><input type="datetime" name="Fecha_<?= $afiliado['IdVotante']; ?>" class="FechaVotante" value="<?php
                                                                                                                                if ($afiliado['Fecha'] !== "1900-01-01 00:00:00.000") {
                                                                                                                                    echo substr($afiliado['Fecha'], 0, -4);
                                                                                                                                } else {
                                                                                                                                    echo "Vacio";
                                                                                                                                }
                                                                                                                                ?>" disabled>
                            </td>
                            <td><i class="fas fa-edit editar" name="editar_<?= $afiliado['IdVotante']; ?>"></i></td>
                            <td>
                                <button type="submit" name="remove_<?= $afiliado['IdVotante']; ?>" class="eliminar">
                                    <i class="fa fa-trash"></i>
                                </button>
                            </td>
                        </tr>
                    <?php } ?>
                </tbody>
            </table>
            <input type="submit" name="guardarCambios" value="Guardar cambios" class="boton" id="guardarCambios">
            <?= isset($guardarVotante) ? "<span>" . $error . "</span>" : "" ?>
            <?= isset($borraAfiliado) ? "<span>" . $error . "</span>" : "" ?>

        </form>
    <?php
    } else { ?>
        <h2>No existen afiliados en la base de datos</h2>
    <?php
    }
} else { ?>
    <h2 id="errPerms">No tienes los permisos suficientes para acceder a esta página</h2>
<?php
}
$contenido = ob_get_clean();
include 'base.php'; ?>