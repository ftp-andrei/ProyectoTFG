<?php
/*´ Pagina ver y gestionar mesa admin
*/
?>
<?php ob_start(); ?>

<?php
if (isset($_SESSION['admin'])) {
    if (!empty($mesas)) {
        var_dump($mesas); ?>
        <table>
            <caption>Mesas</caption>
            <thead>
                <tr>
                    <td>idMesa</td>
                    <td>Nombre</td>
                    <td>Editar</td>
                    <td>Eliminar</td>
                </tr>
            </thead>
            <tbody>
                <?php foreach ($mesas as $mesa) {
                    if ($mesa['idMesa'] != 0) {
                ?>
                        <tr>
                            <td><input type="text" name="idMesa_<?= $mesa['idMesa']; ?>" value="<?= $mesa['idMesa']; ?>" disabled></td>
                            <td><input type="text" name="nombre_<?= $mesa['nombre']; ?>" value="<?= $mesa['nombre']; ?>" disabled></td>
                            <td class="centrar"> <i class="fas fa-edit"></i></td>
                            <td class="centrar">
                                <button type="submit" name="remove_<?= $mesa['idMesa']; ?>">
                                    <i class="fas fa-trash-alt"></i>
                                </button>
                            </td>
                        </tr>
                <?php }
                } ?>

            </tbody>
        </table>
    <?php } else { ?>
        <form method="post">
            <p>No existen mesas, ¿desea añadirlos?</p>
            <input type="submit" name="crearMesa" value="Crear mesa">
        </form>
    <?php
    }
} else { ?>
    <h1 id="errPerms">No tienes los permisos suficientes para acceder a esta página</h1>
<?php
}
$contenido = ob_get_clean();
include 'base.php'; ?>