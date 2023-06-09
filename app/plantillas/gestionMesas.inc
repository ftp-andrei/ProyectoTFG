<?php
/* Gestion Mesas - Admin */

ob_start();

if (isset($_SESSION['admin'])) {
    if (sizeof($mesas) != 1) {
        // JS
        echo "<script src='web/js/mesa.js'></script>" .
            // SweetAlert
            "<script src='https://cdn.jsdelivr.net/npm/sweetalert2@11.0.17/dist/sweetalert2.min.js'></script>" .
            "<link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/sweetalert2@11.0.17/dist/sweetalert2.min.css'>";
?>

        <form method="post">
            <span id="copiado"></span>
            <br>
            <div id="scrollable">
                <table>
                    <caption>Gestión de mesas</caption>
                    <thead>
                        <tr>
                            <th>idMesa</th>
                            <th>Nombre</th>
                            <th>Copiar</th>
                            <th>Editar</th>
                            <th>Eliminar</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php foreach ($mesas as $mesa) {
                            if ($mesa['idMesa'] != 0) {
                        ?>
                                <tr>
                                    <td><input type="text" name="idMesa_<?= $mesa['idMesa']; ?>" value="<?= $mesa['idMesa']; ?>" class="idMesa" disabled></td>
                                    <td><input type="text" name="nombre_<?= $mesa['idMesa']; ?>" value="<?= $mesa['nombre']; ?>" class="nombreMesa" disabled required></td>
                                    <td><i class="fa-solid fa-copy copiar" id="copiar_<?= $mesa['nombre']; ?>"></i></td>
                                    <td> <i class="fas fa-edit editar"></i></td>
                                    <td>
                                        <button type="button" id="remove_<?= $mesa['idMesa']; ?>" class="eliminar">
                                            <i class="fa fa-trash"></i>
                                        </button>
                                    </td>
                                </tr>
                        <?php }
                        } ?>

                    </tbody>
                </table>
            </div>
            <input type="submit" name="guardarCambios" value="Guardar cambios" class="boton" id="guardarCambios">
            <input type="submit" name="anadirMesa" value="Añadir mesa" class="boton" id="anadir">
            <?= isset($nuevaMesa) ? "<span>" . $error . "</span>" : "" ?>
            <?= isset($guardaMesa) ? "<span>" . $error . "</span>" : "" ?>
            <?= isset($borraMesa) ? "<span>" . $error . "</span>" : "" ?>

        </form>
        <!-- En caso de que no existan mesas, le saldrá un mensaje y un boton para añadir de 1 en 1 -->

    <?php } else { ?>
        <form method="post">
            <p>No existen mesas, ¿desea añadirlos?</p>
            <input type="submit" name="crearMesa" value="Crear mesa" class="boton">
        </form>
    <?php
    }
} else { ?>
    <h2 id="errPerms">No tienes los permisos suficientes para acceder a esta página</h2>
<?php
}
$contenido = ob_get_clean();
include 'base.php'; ?>