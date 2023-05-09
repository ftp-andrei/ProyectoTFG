// JS Gestion Interventor (Admin)

document.addEventListener("DOMContentLoaded", function () {
  const guardarCambios = document.getElementById("guardarCambios");
  const anadirInter = document.getElementById("anadir");
  const eliminarInter = document.getElementsByClassName("eliminar");
  const idVerImgs = document.getElementsByClassName("ocultar");
  const idVerPass = document.getElementsByClassName("ocultarPass");
  const idCopy = document.getElementsByClassName("copiar");
  const idEditarInterventor = document.getElementsByClassName("editar");
  const idMesaInterventor = document.getElementsByClassName("optSelect");
  for (let i = 0; i < idVerImgs.length; i++) {
    const idVerImg = idVerImgs[i];
    const idPass = idVerPass[i];
    const clickCopy = idCopy[i];
    const editarInterventor = idEditarInterventor[i];
    const idMesa = idMesaInterventor[i];
    // Agregar un evento click para mostrar las contraseñas
    idVerImg.addEventListener("click", function () {
      mostrarContrasena(idVerImg.id, idPass.id);
    });
    // Copia la contrasena al portapapeles
    clickCopy.addEventListener("click", function () {
      copiarContrasena(idPass.id);
    });
    // Habilita los campos para editar el interventor
    editarInterventor.addEventListener("click", function () {
      editarInterventorInterventor(idPass.id, idMesa.id, idVerImg.id);
    });

    eliminarInter[i].addEventListener("click", function () {
      borradoExitoso();
    });
  }

  guardarCambios.addEventListener("click", function () {
    guardadoExitoso();
  });

  anadirInter.addEventListener("click", function () {
    AnadidoExitoso();
  });
});
// Funcion que muestra la contraseña (sin editarla)
function mostrarContrasena(idVerImg, idPass) {
  let img = document.getElementById(idVerImg);
  let pass = document.getElementById(idPass);
  if (pass.type === "password") {
    img.className = "fa fa-eye mostrar";
    pass.type = "text";
    // pass.disabled = false; // Evita editar la contraseña
  } else {
    img.className = "fa fa-eye-slash ocultar";
    pass.type = "password";
    pass.disabled = true;
  }
}
// Copia la contraseña al portapapeles y muestra un mensaje en la pantalla
function copiarContrasena(idPass) {
  let contrasena = document.getElementById(idPass).value;
  navigator.clipboard
    .writeText(contrasena)
    .then(() => {
      let span = document.getElementById("copiado");
      span.textContent = "¡Contraseña copiada al portapapeles!";
      setTimeout(function cambiarTexto() {
        span.textContent = "";
      }, 2000);
    })
    .catch((error) => {
      console.error("Error al copiar al portapapeles: ", error);
    });
}

// Funcion que habilita los campos para editar el interventor
function editarInterventorInterventor(idPass, idMesa, idVerImg) {
  let img = document.getElementById(idVerImg);
  let contrasena = document.getElementById(idPass);
  let mesa = document.getElementById(idMesa);
  if (contrasena.type === "password") {
    img.className = "fa fa-eye mostrar";
    contrasena.type = "text";
    contrasena.disabled = false;
    mesa.disabled = false;
    contrasena.select();
  } else {
    img.className = "fa fa-eye-slash ocultar";
    contrasena.type = "password";
    contrasena.disabled = true;
    mesa.disabled = true;
  }
}

// Mensaje de que se ha guardado con éxito el interventor
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
// Añadido con exito
function AnadidoExitoso() {
  let span = document.getElementById("copiado");
  span.textContent = "Añadiendo...";
}
