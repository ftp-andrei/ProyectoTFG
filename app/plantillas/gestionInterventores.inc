<?php
/*´ Pagina ver y gestionar interventores admin
*/
// Hecho: Añadir campos con posibles errores al añadir/borrar/modificar
// Hecho: Añadir campo select con las opciones de las mesas.
// Hecho: Editar los interventores (pass + mesa)
// TODO: Refactorizar
// ARREGLADO: Interventor puede acceder por URL a las paginas del admin. Averiguar como quitarlo.
?>
<?php ob_start();
if (isset($_SESSION['admin'])) {
    if (!empty($interventores)) {
?>
        <form method="post">
            <span id="copiado"></span>
            <br>
            <table>
                <caption>Gestión de interventores</caption>
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
                            <td><input type="text" name="user_<?= $interventor['usuario']; ?>" value="<?= $interventor['usuario']; ?>" disabled></td>
                            <td><input type="password" class="ocultarPass" name="password_<?= $interventor['usuario']; ?>" id="pass_<?= $interventor['usuario']; ?>" value="<?= $interventor['password']; ?>" disabled></td>
                            <td><i class="fa fa-eye-slash ocultar" id="ocultar_<?= $interventor['usuario']; ?>"></i></td>
                            <td><i class="fa-solid fa-copy copiar" id="copiar_<?= $interventor['usuario']; ?>"></i></td>
                            <td><select name="optSelect_<?= $interventor['usuario']; ?>" class="optSelect" id="optSelect_<?= $interventor['usuario']; ?>" disabled>
                                    <?php
                                    foreach ($mesas as $mesa) {
                                        if ($mesa['idMesa'] == $interventor['idMesa']) { ?>
                                            <option value="<?= $mesa['idMesa'] ?>" selected="selected"><?= $mesa['nombre'] ?> </option>
                                        <?php
                                        } else { ?>
                                            <option value="<?= $mesa['idMesa'] ?>"><?= $mesa['nombre'] ?> </option>
                                    <?php   }
                                    }
                                    ?>
                                </select>
                            </td>
                            <td><i class="fas fa-edit editar" name="editar_<?= $interventor['usuario']; ?>"></i></td>
                            <td>
                                <button type="submit" name="remove_<?= $interventor['usuario']; ?>" class="eliminar">
                                    <i class="fa fa-trash remove"></i>
                                </button>
                            </td>
                        </tr>
                    <?php } ?>
                </tbody>
            </table>
            <br>
            <input type="submit" name="guardarCambios" value="Guardar cambios" class="boton" id="guardarCambios">
            <input type="submit" name="anadirInterventor" value="Añadir Interventor" class="boton">
            <?= isset($guardaInterventor) ? "<span style='color:red'>" . $error . "</span>" : "" ?>
            <?= isset($nuevoInterventor) ? "<span style='color:red'>" . $error . "</span>" : "" ?>
            <?= isset($borraInterventor) ? "<span style='color:red'>" . $error . "</span>" : "" ?>
        </form>
        <!-- En caso de que no existan interventores, le saldrá un mensaje y un boton para añadir de 1 en 1 -->
    <?php

    } else { ?>
        <form method="post">
            <p>No existen interventores, ¿desea añadirlos?</p>
            <input type="submit" name="crearInterventor" value="Crear un Interventor" class="boton">
        </form>
    <?php
    }
} else { ?>
    <h1 id="errPerms">No tienes los permisos suficientes para acceder a esta página</h1>
<?php
}
$contenido = ob_get_clean();
include 'base.php'; ?>