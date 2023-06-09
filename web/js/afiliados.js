// JS Gestion Afiliados
let filasOriginales = [];
document.addEventListener("DOMContentLoaded", function () {
  // Boton guardar cambios
  const guardarCambios = document.getElementById("guardarCambios");
  // Boton eliminar
  const eliminaAfiliado = document.getElementsByClassName("eliminar");
  // Boton editar
  const idEditar = document.getElementsByClassName("editar");
  // Icono ordenacion tabla
  const icono = document.getElementsByClassName("fa-solid fa-sort");
  // Boton reset
  const reset = document.getElementById("resetVotos");
  // Valores tabla
  const nombre = document.getElementsByClassName("nombreVotante");
  const apellido1 = document.getElementsByClassName("apellido1Votante");
  const apellido2 = document.getElementsByClassName("apellido2Votante");
  const nif = document.getElementsByClassName("nifVotante");
  const telf = document.getElementsByClassName("TelefonoVotante");
  const direccion = document.getElementsByClassName("direccionVotante");
  const email = document.getElementsByClassName("emailVotante");
  const codcentro = document.getElementsByClassName("codcentroVotante");
  const nomcentro = document.getElementsByClassName("NombreCentroVotante");
  const voto = document.getElementsByClassName("optSelectVoto");
  // Tamaño ventana
  const windowWidth = window.innerWidth;

  // Añade scroll vertical si lo necesita.
  window.addEventListener("resize", scrollVertical(windowWidth));
  // Metodo que guarda el orden de las filas originales
  guardarFilasOriginales();
  // Filtros
  busquedaFiltro();
  // ResetAlert
  reset.addEventListener("click", function () {
    resetAlert();
  });

  //Bucle para editar campos del afiliado/Borrar
  for (let i = 0; i < nombre.length; i++) {
    // Habilita que se pueda editar los campos
    idEditar[i].addEventListener("click", function () {
      editaAfiliado(nombre[i], apellido1[i], apellido2[i], nif[i], telf[i], direccion[i], email[i], codcentro[i], nomcentro[i], voto[i].id);
    });
    // Elimina un afiliado
    eliminaAfiliado[i].addEventListener("click", function () {
      confirmacion(eliminaAfiliado[i].id);
    });
  }
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

  // Mensaje al guardar los cambios
  guardarCambios.addEventListener("click", function () {
    guardadoExitoso();
  });
});

// Funcion que habilita los campos para editar
function editaAfiliado(nombre, apellido1, apellido2, nif, telf, direccion, email, codcentro, nomcentro, voto) {
  let opVoto = document.getElementById(voto);
  if (nombre.disabled) {
    nombre.disabled = false;
    apellido1.disabled = false;
    apellido2.disabled = false;
    nif.disabled = false;
    telf.disabled = false;
    direccion.disabled = false;
    email.disabled = false;
    codcentro.disabled = false;
    nomcentro.disabled = false;
    opVoto.disabled = false;
  }
}

// Mensaje al guardar con éxito
function guardadoExitoso() {
  let span = document.getElementById("copiado");
  span.textContent = "Guardando...";
}
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
    limiteElementos = 14;
  }
  // Verificar el tamaño de los elementos elementos y asigna o no la clase scrollable
  if (numAfiliados.length >= limiteElementos || windowWidth <= 1600) {
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
  let tabla = document.getElementById("tablaAfiliados");
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
  let tabla = document.getElementById("tablaAfiliados");
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
  var table = document.getElementById("tablaAfiliados");
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

// SweetAlert - Ventana para confirmar que el usuario quiere borrar un votante
function confirmacion(idBorrar) {
  Swal.fire({
    title: "¿Estás seguro?",
    icon: "warning",
    html: `<form method="post" id="confirmarEliminacion">
        <p>Esta acción no se puede deshacer</p>
        <input type="button" name="cancelar" value="Cancelar" id="SA_cancelar">
        <input type="submit" name="borrarVotante" value="Borrar" id="SA_borrar">
      </form>`,
    showConfirmButton: false,
    didOpen: () => {
      // Obtener el botón por su id
      const botonBorrar = document.getElementById("SA_borrar");
      // Verificar si se encontró el botón
      if (botonBorrar) {
        // Establecer el nuevo nombre
        botonBorrar.name = idBorrar;
      }
      const cancelarVotante = document.getElementById("SA_cancelar");
      cancelarVotante.addEventListener("click", function () {
        Swal.close(); // Cerrar SweetAlert
      });
    },
  });
}

function resetAlert() {
  Swal.fire({
    title: "¿Estás seguro?",
    icon: "warning",
    html: `<form method="post" id="confirmarEliminacion">
        <p>Esta acción no se puede deshacer</p>
        <input type="button" name="cancelar" value="Cancelar" id="SA_cancelar">
        <input type="submit" name="resetVotos" value="Resetear votos" id="SA_borrar">
      </form>`,
    showConfirmButton: false,
    didOpen: () => {
      const cancelarReset = document.getElementById("SA_cancelar");
      cancelarReset.addEventListener("click", function () {
        Swal.close(); // Cerrar SweetAlert
      });
    },
  });
}
