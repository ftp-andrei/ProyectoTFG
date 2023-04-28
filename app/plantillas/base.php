<!-- Vista común a la mayoría (sino todas) las vistas de la aplicación
     Suele contener la imagen corporativa de la apliación Web
     Concretamente esta página contiene el nombre de la empresa
     "Cadena Tiendas Media" y una barra de hiperenlaces con un enalace a la
     página home, llamado "inicio"
     El nombre del archivo es indiferente: layout, comun, etc.
-->
<!DOCTYPE html>
<html>

<head>
  <title>Login - ANPE</title>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <!-- Favicon -->
  <link rel="icon" type="image/jpg" href="web/imagenes/favicon.ico" />
  <!-- CSS -->
  <link rel="stylesheet" type="text/css" href='web/css/resposnive.css' />
  <link rel="stylesheet" type="text/css" href='web/css/ordenador.css' />
  <link rel="stylesheet" type="text/css" href='web/css/tablet.css' />
  <link rel="stylesheet" type="text/css" href='web/css/movil.css' />
  <!-- Boostrap -->
  <!-- <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p" crossorigin="anonymous"></script> -->
  <!-- AwesomeFonts -->
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css" />
</head>

<body>
  <header>
    <h1>ANPE - Elecciones Sindicales</h1>
  </header>
  <nav>
    <hr>
    <!-- Observa cómo el enlace agrega el valor de la variable GET 'ctl'
           que será analizado en la página index.php, en este caso le da el
           valor 'inicio' para que la vista cambie a la página home de la
           aplicación
       -->
    <?php if (isset($_SESSION['admin'])) { ?>
      <a href="index.php?ctl=gestionMesa">Mesa</a> |
      <a href="index.php?ctl=gestionVotantes">Votantes</a> |
      <a href="index.php?ctl=gestionAfiliados">Afiliados</a> |
      <a href="index.php?ctl=gestionInterventores">Interventores</a> |
      <a href="index.php?ctl=panelDeControl">Panel de Control</a> |
      <a href="index.php?ctl=estadisticas">Estadísticas</a> |
      <a href="index.php?ctl=listadosFiltrados">Listados Filtrados</a> |
      <a href="index.php?ctl=logout">Salir</a> |
      <hr>
    <?php  } ?>

    <?php if (isset($_SESSION['interventor'])) { ?>
      <a href="index.php?ctl=votosMesa">Votos de la mesa</a> |
      <a href="index.php?ctl=logout">Salir</a> |
      <hr>
    <?php  } ?>
    <!-- En general, la mayoría de los enlaces serán a la página index.php
           y una asignación a la variable 'ctl'. El valor de la variable deberá
           ser analizada en la página index.php de cara a encontrar la ruta del
           controlador (y método) que debe procesar la petición
      -->
  </nav>
  <div id="contenido">
    <!-- el id css facilita (si se define) la definición del aspecto visual
           de su contenido
           La variable $contenido hará que se muestre la plantilla concreta, el
           contenido concreto, según la solicitud realizada por el usuario
      -->

    <?= $contenido ?>
  </div>
  <footer>
    <hr>
    <p style="text-align:center">- Pie de página -</p>
  </footer>
</body>

</html>