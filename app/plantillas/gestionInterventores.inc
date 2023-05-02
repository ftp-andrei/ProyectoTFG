<?php
/*´ Pagina ver y gestionar interventores admin
*/

// TODO: Al darle a guardar cambios, se debe actualizar la base de datos, y mostrar un mensaje de Guardado con éxito.
// TODO: Añadir campo select con las opciones de las mesas.
// TODO: Eliminar los interventores
// TODO: Editar los interventores (pass + mesa)
// TODO: Interventor puede acceder por URL a las paginas del admin. Averiguar como quitarlo.
?>
<?php ob_start(); ?>

<?php if (!empty($interventores)) { ?>
    <form method="post">
        <table>
            <caption>Interventores</caption>
            <thead>
                <tr>
                    <th>Usuario</th>
                    <th>Contraseña</th>
                    <th>Ver</th>
                    <th>Copiar</th>
                    <th>Mesa</td>
                    <th>Editar</th>
                    <th>Eliminar</th>
                </tr>
            </thead>
            <tbody>
                <?php foreach ($interventores as $interventor) { ?>
                    <tr>
                        <td><?= $interventor['usuario']; ?></td>
                        <td class="asteriscos"><input type="password" class="ocultarPass" name="password_<?= $interventor['usuario']; ?>" id="pass_<?= $interventor['usuario']; ?>" value="<?= $interventor['password']; ?>" disabled></td>
                        <td><i class="fa fa-eye-slash ocultar" id="ocultar_<?= $interventor['usuario']; ?>"></i></td>
                        <td><i class="fa-solid fa-copy copiar" id="copiar_<?= $interventor['usuario']; ?>"></i></td>
                        <td><select name="opcionSelect" id="opcionSelect" disabled>
                                <option value="<?= $interventor['idMesa'] == NULL ? "Sin Asignar" : $interventor['idMesa']; ?>" selected="selected"><?= $interventor['idMesa'] == NULL ? "Sin Asignar" : $interventor['idMesa']; ?> </option>
                            </select>
                        </td>
                        <td><i class="fas fa-edit editar" id="editar_<?= $interventor['usuario']; ?>" name="editar_<?= $interventor['usuario']; ?>"></i></td>
                        <td><i class="fa fa-trash remove" id="remove_<?= $interventor['usuario']; ?>" name="remove_<?= $interventor['usuario']; ?>"></i></td>
                    </tr>

                <?php }
                ?>
            </tbody>
        </table>
        <input type="submit" name="guardarCambios" value="Guardar cambios" id="botonGuardarMostrar">
        <input type="submit" name="anadirInterventor" value="Añadir Interventor">
        <?= isset($error) ? "<span style='color:red'>" . $error . "</span>" : "" ?>
    </form>
<?php } else { ?>
    <form method="post">
        <p>No existen interventores, ¿desea añadirlos?</p>
        <input type="submit" name="crearInterventor" value="Crear Interventor">
    </form>
<?php
}
$contenido = ob_get_clean();
include 'base.php'; ?>