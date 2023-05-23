// JS Gestion Votantes (Admin)
// Variables globales para almacenar las filas originales
let filasOriginales = [];
document.addEventListener("DOMContentLoaded", function () {
  const guardarCambios = document.getElementById("guardarCambios");
  const eliminaVotante = document.getElementsByClassName("eliminar");
  const icono = document.getElementsByClassName("fa-solid fa-sort");
  const idEditarVotante = document.getElementsByClassName("editar");
  const nombre = document.getElementsByClassName("nombreVotante");
  const apellido1 = document.getElementsByClassName("apellido1Votante");
  const apellido2 = document.getElementsByClassName("apellido2Votante");
  const nifVotante = document.getElementsByClassName("NIFVotante");
  const codCentro = document.getElementsByClassName("CodCentroVotante");
  const nombreCentro = document.getElementsByClassName("NombreCentroVotante");
  const mesaNombre = document.getElementsByClassName("optSelectMesa");
  const voto = document.getElementsByClassName("optSelectVoto");
  const windowWidth = window.innerWidth; // Tamaño ventana
  guardarFilasOriginales();

  //Bucle para editar campos de la mesa/Borrar
  for (let i = 0; i < nifVotante.length; i++) {
    // Edita los campos de la mesa
    idEditarVotante[i].addEventListener("click", function () {
      editarVotante(nifVotante[i], mesaNombre[i], voto[i], nombreCentro[i], codCentro[i], nombre[i], apellido1[i], apellido2[i]);
    });
    // Elimina un votante
    eliminaVotante[i].addEventListener("click", function () {
      // borradoExitoso();
      confirmacion(eliminaVotante[i].id);
    });
  }
  // Bucle para ordenar los th de la tabla
  for (let index = 0; index < icono.length; index++) {
    const icon = icono[index];
    icon.addEventListener("mouseover", function () {
      // Cambia la clase del icono
      icon.classList.add("fa-fade");
    });

    icon.addEventListener("mouseout", function () {
      // Elimina la nueva clase y vuelve a la clase original
      icon.classList.remove("fa-fade");
    });
    // Si hace click se cambia de icono y lista
    icon.addEventListener("click", function () {
      resetearIconos(icon.id);
      ordenarTabla(icon.id);
    });
  }
  window.addEventListener("resize", scrollVertical(windowWidth, nifVotante));

  // Guarda los cambios
  guardarCambios.addEventListener("click", function () {
    guardadoExitoso();
  });
});

function scrollVertical(windowWidth, nifVotante) {
  const div = document.getElementById("scrollable");
  let limiteElementos;

  // Definir los límites de elementos en función del ancho de la ventana
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
  if (nifVotante.length >= limiteElementos) {
    div.classList.add("scrollable");
  } else {
    if (div.classList.contains("scrollable")) {
      div.classList.remove("scrollable");
    }
  }
}
// Funcion que habilita los campos para editar el votante
function editarVotante(nif, idMesa, idVoto, nombreCentro, codCentro, nombre, apellido1, apellido2) {
  if (nif.disabled) {
    nif.disabled = false;
    document.getElementById(idMesa.id).disabled = false;
    document.getElementById(idVoto.id).disabled = false;
    nombreCentro.disabled = false;
    codCentro.disabled = false;
    nombre.disabled = false;
    apellido1.disabled = false;
    apellido2.disabled = false;
  }
  // else {
  //   nif.disabled = true;
  //   document.getElementById(idMesa.id).disabled = true;
  //   document.getElementById(idVoto.id).disabled = true;
  //   nombreCentro.disabled = true;
  //   codCentro.disabled = true;
  //   nombre.disabled = true;
  //   apellido1.disabled = true;
  //   apellido2.disabled = true;
  // }
}

// Guardado con éxito
function guardadoExitoso() {
  let span = document.getElementById("copiado");
  span.textContent = "Guardando...";
}
// Metodo para ordenar los th de la tabla SIN IMPLEMENTAR TODAVIA
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
  let tabla = document.getElementById("tablaVotantes");
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
    // los añadimos
    filas.forEach(function (fila) {
      tabla.tBodies[0].appendChild(fila);
    });
  }
}
// Obtiene el índice de la columna en la que se encuentra el icono de ordenación
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
  let tabla = document.getElementById("tablaVotantes");
  let filas = Array.from(tabla.tBodies[0].querySelectorAll("tr"));
  filasOriginales = [...filas];
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
