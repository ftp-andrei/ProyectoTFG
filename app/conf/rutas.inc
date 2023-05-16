<?php
// Vector multidimensional con rutas a controlador y método que debe atender cada enlace
/* formato:
    Primera dimension: nombre del enlace pasado mediante variable GET 'ctl'
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
    // Pagina inicial - Home Admin
    'gestionVotantes' => ['controller' => 'app\EleccionesSindicales\controlador\VotantesController', 'action' => 'verVotantes'],
    // Gestion Interventores - Admin
    'gestionInterventores' => ['controller' => 'app\EleccionesSindicales\controlador\InterventorController', 'action' => 'verInterventores'],
    // Gestion Mesas - Admin
    'gestionMesas' => ['controller' => 'app\EleccionesSindicales\controlador\MesasController', 'action' => 'verMesas'],
    // Gestion Afiliados - Admin
    'gestionAfiliados' => ['controller' => 'app\EleccionesSindicales\controlador\AfiliadosController', 'action' => 'verAfiliados'],
    // Estadisticas - Admin
    'estadisticas' => ['controller' => 'app\EleccionesSindicales\controlador\EstadisticasController', 'action' => 'verEstadisticas'],
    // Pagina inicial - Home Interventores
    'inicioInterventor' => ['controller' => 'app\EleccionesSindicales\controlador\InterventorController', 'action' => 'inicioInterventor'],
];
