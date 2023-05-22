// JS Gestion Votantes (Admin)

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
  //Bucle para editar campos de la mesa/Borrar
  for (let i = 0; i < nifVotante.length; i++) {
    // Edita los campos de la mesa
    idEditarVotante[i].addEventListener("click", function () {
      editarVotante(nifVotante[i], mesaNombre[i], voto[i], nombreCentro[i], codCentro[i], nombre[i], apellido1[i], apellido2[i]);
    });
    // Elimina un votante
    eliminaVotante[i].addEventListener("click", function () {
      borradoExitoso();
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
      // let columna = document.getElementsByClassName("apellido2Votante");
      // columna
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
  if (windowWidth < 480) {
    limiteElementos = 5;
  } else if (windowWidth < 1600 && windowWidth > 780) {
    limiteElementos = 10;
  } else {
    limiteElementos = 15;
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

// Borrado con éxito SIN USAR TODAVIA
function borradoExitoso() {
  let span = document.getElementById("copiado");
  span.style.color = "red";
  span.textContent = "Borrando..";
}
// Metodo para ordenar los th de la tabla
// columna
function ordenarTabla(icono) {
  let elementoIcono = document.getElementById(icono);
  // let table = document.getElementsByClassName(tabla);
  // let filas = Array.from(table.getElementsByTagName("tr"));
  if (elementoIcono.classList.contains("fa-fade")) {
    elementoIcono.classList.remove("fa-fade");
  }
  if (elementoIcono.classList.contains("fa-sharp")) {
    elementoIcono.classList.remove("fa-sharp");
    elementoIcono.classList.remove("fa-sort");
    elementoIcono.classList.add("fa-sort-up");
    // Ordenar de forma ascendente
    // filas.sort(function (a, b) {
    //   var valorA = obtenerValorColumna(a, columna);
    //   var valorB = obtenerValorColumna(b, columna);
    //   return valorA.localeCompare(valorB, undefined, { numeric: true });
    // });
  } else if (elementoIcono.classList.contains("fa-sort-up")) {
    elementoIcono.classList.remove("fa-sort-up");
    elementoIcono.classList.add("fa-sort-down");
    // Ordenar de forma descendente
    // filas.sort(function (a, b) {
    //   var valorA = obtenerValorColumna(a, columna);
    //   var valorB = obtenerValorColumna(b, columna);
    //   return valorB.localeCompare(valorA, undefined, { numeric: true });
    // });
  } else if (elementoIcono.classList.contains("fa-sort-down")) {
    elementoIcono.classList.remove("fa-sort-down");
    elementoIcono.classList.add("fa-sharp");
    elementoIcono.classList.add("fa-sort");
    // return;
  }

  // // Volver a agregar las filas ordenadas a la tabla
  // var tbody = tabla.querySelector("tbody");
  // filas.forEach(function (fila) {
  //   tbody.appendChild(fila);
  // });
}

function obtenerValorColumna(fila, columna) {
  var celda = fila.querySelector("td:nth-child(" + columna + ")");
  return celda ? celda.innerText : "";
}
