// JS Gestion Afiliados (Admin)

document.addEventListener("DOMContentLoaded", function () {
  const guardarCambios = document.getElementById("guardarCambios");
  //   const anadirMesa = document.getElementById("anadir");
  const eliminaAfiliado = document.getElementsByClassName("eliminar");
  const idEditar = document.getElementsByClassName("editar");
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

  for (let i = 0; i < nombre.length; i++) {
    // Habilita los campos para editar el Mesa
    idEditar[i].addEventListener("click", function () {
      editarNombreMesa(nombre[i], apellido1[i], apellido2[i], nif[i], telf[i], direccion[i], email[i], codcentro[i], nomcentro[i], voto[i].id);
    });

    eliminaAfiliado[i].addEventListener("click", function () {
      borradoExitoso();
    });
  }

  guardarCambios.addEventListener("click", function () {
    guardadoExitoso();
  });
});

// Funcion que habilita los campos para editar la Mesa
function editarNombreMesa(nombre, apellido1, apellido2, nif, telf, direccion, email, codcentro, nomcentro, voto) {
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
  } else {
    nombre.disabled = true;
    apellido1.disabled = true;
    apellido2.disabled = true;
    nif.disabled = true;
    telf.disabled = true;
    direccion.disabled = true;
    email.disabled = true;
    codcentro.disabled = true;
    nomcentro.disabled = true;
    opVoto.disabled = true;
  }
}

// Guardado con éxito
function guardadoExitoso() {
  let span = document.getElementById("copiado");
  span.textContent = "Guardando...";
}
// Borrado con éxito
function borradoExitoso() {
  let span = document.getElementById("copiado");
  span.style.color = "red";
  span.textContent = "Borrando...";
}
// Añadido con exito SIN USAR
function AnadidoExitoso() {
  let span = document.getElementById("copiado");
  span.textContent = "Añadiendo...";
}
