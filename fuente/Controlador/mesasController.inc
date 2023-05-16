<?php

namespace app\EleccionesSindicales\controlador;

use app\EleccionesSindicales\repositorio\MesasRepositorio;

class MesasController
{
    // Paginas que muestra las mesas (solo para el admin)
    public function verMesas()
    {
        $titulo = (new TitleController())->setTitle('Mesas - ANPE');

        $mesas = (new MesasController())->getAllMesas();
        // Crea mesas
        if (isset($_POST['anadirMesa']) || isset($_POST['crearMesa'])) {
            if ($nuevaMesa = (new MesasRepositorio())->generaMesa()) {
                header('Location: index.php?ctl=gestionMesas');
            } else {
                $error = "Error al generar mesa";
            }
        }
        // Elimina una mesa
        foreach ($mesas as $mesa) {
            if (isset($_POST["remove_{$mesa['idMesa']}"])) {
                if ($borraMesa = (new MesasRepositorio())->borraMesa($mesa['idMesa'])) {
                    header('Location: index.php?ctl=gestionMesas');
                } else {
                    $error = "Error al borrar mesa";
                }
            }
        }
        // Guardar cambios
        if (isset($_POST["guardarCambios"])) {
            foreach ($mesas as $mesa) {
                $nombre = $mesa['nombre'];
                // POST user
                if (isset($_POST["nombre_{$mesa['idMesa']}"])) {
                    $nombre = $_POST["nombre_{$mesa['idMesa']}"];
                }

                if ($guardaMesa = (new MesasRepositorio())->guardarCambiosMesa($nombre, $mesa['idMesa'])) {
                    continue;
                } else {
                    $error = "Error al guardar los cambios";
                }
            }
            header('Location: index.php?ctl=gestionMesas');
        }

        require __DIR__ . '/../../app/plantillas/gestionMesas.inc';
    }
    // Funcion que retorna todas las mesas
    public function getAllMesas()
    {
        $mesas = (new MesasRepositorio())->getAllMesas();
        return $mesas;
    }
}
