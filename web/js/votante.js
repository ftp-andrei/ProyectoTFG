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
  //Bucle para editar campos de la mesa/Borrar
  for (let i = 0; i < nifVotante.length; i++) {
    // Edita los campos de la mesa
    idEditarVotante[i].addEventListener("click", function () {
      editarVotante(nifVotante[i], mesaNombre[i], voto[i], nombreCentro[i], codCentro[i], nombre[i], apellido1[i], apellido2[i]);
    });

    eliminaVotante[i].addEventListener("click", function () {
      borradoExitoso();
    });

    icono[i].addEventListener("mouseover", function () {
      // Cambia la clase del icono
      icono.classList.add("fa-fade");
    });

    // Agrega el evento de 'mouseout' (cuando el mouse sale del icono)
    icono[i].addEventListener("mouseout", function () {
      // Elimina la nueva clase y vuelve a la clase original
      icono.classList.remove("fa-fade");
    });
  }
  // Bucle para ordenar los th de la tabla
  for (let index = 0; index < 10; index++) {}
  // Guarda los cambios
  guardarCambios.addEventListener("click", function () {
    guardadoExitoso();
  });
});
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
  } else {
    nif.disabled = true;
    document.getElementById(idMesa.id).disabled = true;
    document.getElementById(idVoto.id).disabled = true;
    nombreCentro.disabled = true;
    codCentro.disabled = true;
    nombre.disabled = true;
    apellido1.disabled = true;
    apellido2.disabled = true;
  }
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
function ordenarTabla(columna, ascendente) {
  var table, rows, switching, i, x, y, shouldSwitch;
  table = document.getElementById("miTabla");
  switching = true;

  while (switching) {
    switching = false;
    rows = table.rows;

    for (i = 1; i < rows.length - 1; i++) {
      shouldSwitch = false;
      x = rows[i].getElementsByTagName("td")[columna];
      y = rows[i + 1].getElementsByTagName("td")[columna];

      if (ascendente) {
        if (x.innerHTML.toLowerCase() > y.innerHTML.toLowerCase()) {
          shouldSwitch = true;
          break;
        }
      } else {
        if (x.innerHTML.toLowerCase() < y.innerHTML.toLowerCase()) {
          shouldSwitch = true;
          break;
        }
      }
    }

    if (shouldSwitch) {
      rows[i].parentNode.insertBefore(rows[i + 1], rows[i]);
      switching = true;
    }
  }
}
