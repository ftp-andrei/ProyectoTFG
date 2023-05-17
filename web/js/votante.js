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
    // Elimina un votante
    eliminaVotante[i].addEventListener("click", function () {
      borradoExitoso();
    });
  }
  // Bucle para ordenar los th de la tabla
  for (let index = 0; index < icono.length; index++) {
    const icon = icono[index];
    // icono[index].addEventListener("mouseover", function () {
    //   // Cambia la clase del icono
    //   icono[index].classList.add("fa-fade");
    // });

    // icono[index].addEventListener("mouseout", function () {
    //   // Elimina la nueva clase y vuelve a la clase original
    //   icono[index].classList.remove("fa-fade");
    // });
    // Si hace click se cambia de icono y lista
    icon.addEventListener("click", function () {
      ordenarTabla(icon.id);
    });
  }
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
function ordenarTabla(icono) {
  let elementoIcono = document.getElementById(icono);

  if (elementoIcono.classList.contains("fa-sharp")) {
    elementoIcono.classList.remove("fa-sharp");
    elementoIcono.classList.remove("fa-sort");
    elementoIcono.classList.add("fa-sort-up");
  } else if (elementoIcono.classList.contains("fa-sort-up")) {
    elementoIcono.classList.remove("fa-sort-up");
    elementoIcono.classList.add("fa-sort-down");
  } else if (elementoIcono.classList.contains("fa-sort-down")) {
    elementoIcono.classList.remove("fa-sort-down");
    elementoIcono.classList.add("fa-sharp");
    elementoIcono.classList.add("fa-sort");
  }
}
