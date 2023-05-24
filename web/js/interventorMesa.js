// JS Inicio Interventores
let filasOriginales = [];
document.addEventListener("DOMContentLoaded", function () {
  // Icono ordenacion tabla
  const icono = document.getElementsByClassName("fa-solid fa-sort");
  // Tamaño ventana
  const windowWidth = window.innerWidth;

  // Añade scroll vertical si lo necesita.
  window.addEventListener("resize", scrollVertical(windowWidth));
  // Metodo que guarda el orden de las filas originales
  guardarFilasOriginales();
  // Filtros
  busquedaFiltro();
  // Ordenacion th tabla + metodos
  for (let index = 0; index < icono.length; index++) {
    const icon = icono[index];

    // Añade o quita la clase fa-fade
    icon.addEventListener("mouseover", function () {
      icon.classList.add("fa-fade");
    });
    icon.addEventListener("mouseout", function () {
      icon.classList.remove("fa-fade");
    });

    // Si hace click se cambia de icono y ordena la tabla
    icon.addEventListener("click", function () {
      resetearIconos(icon.id);
      ordenarTabla(icon.id);
    });
  }
});

// Metodo que implementa (si lo necesita) el scroll vertical/horizontal
function scrollVertical(windowWidth) {
  let div = document.getElementById("scrollable");
  let numAfiliados = document.getElementsByClassName("NIFVotante");
  let limiteElementos;

  if (windowWidth <= 480) {
    limiteElementos = 5;
  } else if (windowWidth <= 769 && windowWidth > 480) {
    limiteElementos = 7;
  } else if (windowWidth <= 1600 && windowWidth >= 770) {
    limiteElementos = 9;
  } else {
    limiteElementos = 12;
  }
  // Verificar el tamaño de los elementos elementos y asigna o no la clase scrollable
  if (numAfiliados.length >= limiteElementos) {
    div.classList.add("scrollable");
  } else {
    if (div.classList.contains("scrollable")) {
      div.classList.remove("scrollable");
    }
  }
}

// Metodo para ordenar los th de la tabla
function ordenarTabla(icono) {
  let elementoIcono = document.getElementById(icono);
  // Remueve el fade del th
  if (elementoIcono.classList.contains("fa-fade")) {
    elementoIcono.classList.remove("fa-fade");
  }
  // Cambia los iconos
  if (elementoIcono.classList.contains("fa-sharp")) {
    elementoIcono.classList.remove("fa-sharp");
    elementoIcono.classList.remove("fa-sort");
    elementoIcono.classList.add("fa-sort-up");
    ordenarFilas(icono, "asc");
  } else if (elementoIcono.classList.contains("fa-sort-up")) {
    elementoIcono.classList.remove("fa-sort-up");
    elementoIcono.classList.add("fa-sort-down");
    ordenarFilas(icono, "desc");
  } else if (elementoIcono.classList.contains("fa-sort-down")) {
    elementoIcono.classList.remove("fa-sort-down");
    elementoIcono.classList.add("fa-sharp");
    elementoIcono.classList.add("fa-sort");
    ordenarFilas(icono, "default");
  }
}
// Cambia el orden de las filas de la tabla
function ordenarFilas(icono, orden) {
  let tabla = document.getElementById("tablaInterventor");
  let filas = Array.from(tabla.tBodies[0].querySelectorAll("tr"));
  let columnaIndex = obtenerColumnaIndex(icono);

  if (orden === "default") {
    // Restaurar filas originales
    while (tabla.tBodies[0].firstChild) {
      tabla.tBodies[0].removeChild(tabla.tBodies[0].firstChild);
    }
    filasOriginales.forEach(function (fila) {
      tabla.tBodies[0].appendChild(fila);
    });
  } else {
    filas.sort(function (filaA, filaB) {
      let contenidoA = obtenerContenidoColumna(filaA, columnaIndex);
      let contenidoB = obtenerContenidoColumna(filaB, columnaIndex);
      if (orden === "asc") {
        return contenidoA.localeCompare(contenidoB);
      } else {
        return contenidoB.localeCompare(contenidoA);
      }
    });
    // eliminamos todos los elementos hijos
    while (tabla.tBodies[0].firstChild) {
      tabla.tBodies[0].removeChild(tabla.tBodies[0].firstChild);
    }
    // los añadimos ya filtrados
    filas.forEach(function (fila) {
      tabla.tBodies[0].appendChild(fila);
    });
  }
}
// Obtiene el índice de la columna (en la que se encuentra el icono de ordenación)
function obtenerColumnaIndex(icono) {
  let columna = document.getElementById(icono).parentNode;
  let encabezados = Array.from(columna.parentNode.children);
  return encabezados.indexOf(columna);
}
// Obtiene el contenido de una celda específica
function obtenerContenidoColumna(fila, columnaIndex) {
  let celda = fila.children[columnaIndex];
  let input = celda.querySelector("input");
  if (input) {
    return input.value;
  } else {
    return "";
  }
}
// Guarda las filas originales de la tabla para poder resetear el ordenamiento
function guardarFilasOriginales() {
  let tabla = document.getElementById("tablaInterventor");
  let filas = Array.from(tabla.tBodies[0].querySelectorAll("tr"));
  filasOriginales = filas;
}
// Metodo para resetear iconos de forma que solo permita ordenar por 1 columna
function resetearIconos(icono) {
  let elementoIcono = document.getElementById(icono);
  let elementos = Array.from(document.querySelectorAll(".fa-solid")).filter((elemento) => elemento.id !== elementoIcono.id);
  for (var i = 0; i < elementos.length; i++) {
    if (elementos[i].classList.contains("fa-sort-up")) {
      elementos[i].classList.remove("fa-sort-up");
    }
    if (elementos[i].classList.contains("fa-sort-down")) {
      elementos[i].classList.remove("fa-sort-down");
    }
    elementos[i].classList.add("fa-sharp");
    elementos[i].classList.add("fa-sort");
  }
}
// Filtro de la tabla
function busquedaFiltro() {
  var input = document.getElementById("search");
  var table = document.getElementById("tablaInterventor");
  var rows = table.getElementsByTagName("tr");

  input.addEventListener("keyup", function () {
    var filter = removeAccents(input.value.toUpperCase());

    for (var i = 1; i < rows.length; i++) {
      var visible = false;
      var cells = rows[i].getElementsByTagName("td");
      for (var j = 0; j < cells.length; j++) {
        // verifica el contenido de una celda en particular (quitando acentos)
        if (removeAccents(cells[j].innerHTML.toUpperCase()).indexOf(filter) > -1) {
          visible = true;
          break; // No es necesario seguir verificando las demás celdas
        }
      }
      rows[i].style.display = visible ? "" : "none";
    }
  });
}

// Función para eliminar acentos y caracteres especiales
function removeAccents(str) {
  return str.normalize("NFD").replace(/[\u0300-\u036f]/g, "");
}
