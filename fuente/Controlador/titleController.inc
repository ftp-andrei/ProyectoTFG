<?php

namespace app\EleccionesSindicales\controlador;

class TitleController
{
    // Funcion para cambiar el titulo de la pagina
    public function setTitle($title)
    {
        echo '<script>document.title = "' . $title . '";</script>';
    }
}
