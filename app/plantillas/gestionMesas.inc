<?php
/*´ Pagina ver y gestionar mesa admin
*/
?>
<?php ob_start(); ?>

<?php
if (isset($_SESSION['admin'])) {
    if (sizeof($mesas) != 1) {  ?>
        <form method="post">
            <span id="copiado"></span>
            <br>
            <table>
                <caption>Gestión de mesas</caption>
                <thead>
                    <tr>
                        <td>idMesa</td>
                        <td>Nombre</td>
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
                                <td><input type="text" name="idMesa_<?= $mesa['idMesa']; ?>" value="<?= $mesa['idMesa']; ?>" class="idMesa" id="<?= $mesa['idMesa']; ?>" disabled></td>
                                <td><input type="text" name="nombre_<?= $mesa['idMesa']; ?>" value="<?= $mesa['nombre']; ?>" class="nombreMesa" id="<?= $mesa['idMesa']; ?>" disabled></td>
                                <td><i class="fa-solid fa-copy copiar" id="copiar_<?= $mesa['nombre']; ?>"></i></td>
                                <td> <i class="fas fa-edit editar"></i></td>
                                <td>
                                    <button type="submit" name="remove_<?= $mesa['idMesa']; ?>" class="eliminar">
                                        <i class="fa fa-trash"></i>
                                    </button>
                                </td>
                            </tr>
                    <?php }
                    } ?>
                </tbody>
            </table>
            <br>
            <input type="submit" name="guardarCambios" value="Guardar cambios" class="boton" id="guardarCambios">
            <input type="submit" name="anadirMesa" value="Añadir mesa" class="boton">
            <?= isset($nuevaMesa) ? "<span style='color:red'>" . $error . "</span>" : "" ?>
            <?= isset($guardaMesa) ? "<span style='color:red'>" . $error . "</span>" : "" ?>
            <?= isset($borraMesa) ? "<span style='color:red'>" . $error . "</span>" : "" ?>

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
    <h1 id="errPerms">No tienes los permisos suficientes para acceder a esta página</h1>
<?php
}
$contenido = ob_get_clean();
include 'base.php'; ?>