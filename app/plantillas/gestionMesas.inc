<?php
/*´ Pagina ver y gestionar mesa admin
*/
?>
<?php ob_start(); ?>

<?php if (!empty($mesas)) {
    var_dump($mesas); ?>
    <table>
        <caption>Mesas</caption>
        <thead>
            <tr>
                <td>idMesa</td>
                <td>Nombre</td>
                <td>Editar</td>
            </tr>
        </thead>
        <tbody>
            <?php foreach ($mesas as $mesa) { ?>
                <tr>
                    <td><?php echo $mesa['idMesa']; ?></td>
                    <td class="nombreMesa" name="nombreMesa_<?php echo $mesa['nombre']; ?>"><?php echo $mesa['nombre']; ?></td>
                    <td name="editar<?php echo $mesa['nombre']; ?>"> <i class="fas fa-edit"></i></td>
                </tr>
            <?php } ?>

        </tbody>
    </table>
<?php } else { ?>
    <form method="post">
        <p>No existen mesaes, ¿desea añadirlos?</p>
        <input type="submit" name="crearmesa" value="Crear mesa">
    </form>
<?php
}
$contenido = ob_get_clean();
include 'base.php'; ?>