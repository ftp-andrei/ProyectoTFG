// JS Gestion Interventor (Admin)

document.addEventListener("DOMContentLoaded", function () {
  const guardarCambios = document.getElementById("guardarCambios");
  const anadirInter = document.getElementById("anadir");
  const eliminarInter = document.getElementsByClassName("eliminar");
  const idVerImgs = document.getElementsByClassName("ocultar");
  const idVerPass = document.getElementsByClassName("ocultarPass");
  const idCopy = document.getElementsByClassName("copiar");
  const idEditarInterventor = document.getElementsByClassName("editar");
  const user = document.getElementsByClassName("usuario");
  const idMesaInterventor = document.getElementsByClassName("optSelect");
  const windowWidth = window.innerWidth; // Tamaño ventana
  for (let i = 0; i < idVerImgs.length; i++) {
    const idVerImg = idVerImgs[i];
    const idMesa = idMesaInterventor[i];
    // Agregar un evento click para mostrar las contraseñas
    idVerImg.addEventListener("click", function () {
      mostrarContrasena(idVerImg.id, idVerPass[i].id);
    });
    // Copia la contrasena al portapapeles
    idCopy[i].addEventListener("click", function () {
      copiarContrasena(idVerPass[i].id);
    });
    // Habilita los campos para editar el interventor
    idEditarInterventor[i].addEventListener("click", function () {
      editarInterventorInterventor(idVerPass[i].id, idMesa.id, idVerImg.id, user[i].id);
    });

    eliminarInter[i].addEventListener("click", function () {
      borradoExitoso();
    });
  }
  window.addEventListener("resize", scrollVertical(windowWidth));

  guardarCambios.addEventListener("click", function () {
    guardadoExitoso();
  });

  anadirInter.addEventListener("click", function () {
    AnadidoExitoso();
  });
});

function scrollVertical(windowWidth) {
  const div = document.getElementById("scrollable");
  const numeroInterventores = document.getElementsByClassName("usuario");

  let limiteElementos;

  // Definir los límites de elementos en función del ancho de la ventana
  if (windowWidth < 480) {
    // Si el ancho es menor que 600px
    limiteElementos = 5;
  } else if (windowWidth < 1600 && windowWidth > 780) {
    // Si el ancho es menor que 900px
    limiteElementos = 10;
  } else {
    // Si el ancho es mayor o igual a 900px
    limiteElementos = 15;
  }
  // Verificar si existen 10 elementos
  if (numeroInterventores.length >= limiteElementos) {
    // Iterar sobre los elementos
    div.classList.add("scrollable");
  } else {
    // Si no hay 15 elementos, puedes realizar otra acción o dejarlo sin cambios
    if (div.classList.contains("scrollable")) {
      div.classList.remove("scrollable");
    }
  }
}
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
function editarInterventorInterventor(idPass, idMesa, idVerImg, usuario) {
  let img = document.getElementById(idVerImg);
  let contrasena = document.getElementById(idPass);
  let mesa = document.getElementById(idMesa);
  let user = document.getElementById(usuario);
  console.log(user);
  if (contrasena.type === "password") {
    img.className = "fa fa-eye mostrar";
    contrasena.type = "text";
    contrasena.disabled = false;
    mesa.disabled = false;
    user.disabled = false;
    contrasena.select();
  } else {
    img.className = "fa fa-eye-slash ocultar";
    contrasena.type = "password";
    contrasena.disabled = true;
    mesa.disabled = true;
    user.disabled = true;
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
