<?php

// Vector multidimensional con rutas a controlador y método que debe
// atender cada enlace
/* formato:
    Primera dimensaión: nombre del enlace pasado mediante variable GET 'ctl'
     'nombreEnlace' => [] segunda dimesion con información del controlador
                       que atiende esa petición, clave 'controller', y del
                       método concreto que está especializado en su tratamiento,
                       clave 'action'
  Se debe agregar una ruta por cada valor diferente que tome la variable 'ctl'.
  La clave 'inicio' referencia la página home de la aplicación y especifica
    el controlador que debe decidir cuál es la vista que se debe mostrar
*/
$mapeoRutas = [
    // Pagina inicial - Login
    'login' => ['controller' => 'app\EleccionesSindicales\controlador\SessionController', 'action' => 'login'],
    // Logout
    'logout' => ['controller' => 'app\EleccionesSindicales\controlador\SessionController', 'action' => 'logout'],
    // Si tiene exito (como admin), le preguntará si desea generar mesas
    'deseaMesas' => ['controller' => 'app\EleccionesSindicales\controlador\AdminController', 'action' => 'deseaMesas'],
    // Si dice que Si, le preguntará cuantas
    'generaMesas' => ['controller' => 'app\EleccionesSindicales\controlador\MesasController', 'action' => 'generaMesas'],
    // En caso de que no, le preguntará si desea generar interventores
    'deseaInterventor' => ['controller' => 'app\EleccionesSindicales\controlador\AdminController', 'action' => 'deseaInterventores'],
    // En caso afirmativo, le preguntará cuantos
    'generaInterventores' => ['controller' => 'app\EleccionesSindicales\controlador\InterventorController', 'action' => 'generaInterventores'],
    // En caso de que no, le mostrará la página inicial (gestion votantes)
    'gestionVotantes' => ['controller' => 'app\EleccionesSindicales\controlador\VotantesController', 'action' => 'verVotantes'],
    // Funciones admin
    // Gestion Interventores - Lista de Interventores
    'gestionInterventores' => ['controller' => 'app\EleccionesSindicales\controlador\InterventorController', 'action' => 'verInterventores'],
    // Gestion Mesas - Lista de Mesas
    'gestionMesas' => ['controller' => 'app\EleccionesSindicales\controlador\MesasController', 'action' => 'verMesas'],
    // Gestion Interventores - Lista de Interventores
    'gestionAfiliados' => ['controller' => 'app\EleccionesSindicales\controlador\AfiliadosController', 'action' => 'verAfiliados'],
    // Estadisticas (admin)
    'estadisticas' => ['controller' => 'app\EleccionesSindicales\controlador\AdminController', 'action' => 'verEstadisticas'],
    // Pagina Inicial Interventores
    'inicioInterventor' => ['controller' => 'app\EleccionesSindicales\controlador\InterventorController', 'action' => 'inicioInterventor'],
    // Funciones interventor
];
