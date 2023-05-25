// JS Gestion Interventor (Admin)

document.addEventListener("DOMContentLoaded", function () {
  // Boton guardar cambios
  const guardarCambios = document.getElementById("guardarCambios");
  // Boton añadir
  const anadirInter = document.getElementById("anadir");
  // Boton eliminar
  const eliminarInter = document.getElementsByClassName("eliminar");
  // Ojo img
  const idVerImgs = document.getElementsByClassName("ocultar");
  // Boton copiar
  const idCopy = document.getElementsByClassName("copiar");
  // Boton editar
  const idEditarInterventor = document.getElementsByClassName("editar");
  // Valores tabla
  const idVerPass = document.getElementsByClassName("ocultarPass");
  const user = document.getElementsByClassName("usuario");
  const idMesaInterventor = document.getElementsByClassName("optSelect");
  // Tamaño ventana
  const windowWidth = window.innerWidth;

  for (let i = 0; i < idVerImgs.length; i++) {
    const idVerImg = idVerImgs[i];
    const idMesa = idMesaInterventor[i];
    // Agregar un evento click para mostrar las contraseñas
    idVerImg.addEventListener("click", function () {
      mostrarContrasena(idVerImg.id, idVerPass[i].id, user[i].id);
    });
    // Copia la contrasena al portapapeles
    idCopy[i].addEventListener("click", function () {
      copiarContrasena(idVerPass[i].id);
    });
    // Habilita los campos para editar el interventor
    idEditarInterventor[i].addEventListener("click", function () {
      editarInterventorInterventor(idVerPass[i].id, idMesa.id, idVerImg.id, user[i].id);
    });
    // Elimina un interventor
    eliminarInter[i].addEventListener("click", function () {
      confirmacion(eliminarInter[i].id);
    });
  }
  // Añade scroll vertical si lo necesita.
  window.addEventListener("resize", scrollVertical(windowWidth));
  // Mensaje de confirmación de guardado
  guardarCambios.addEventListener("click", function () {
    guardadoExitoso();
  });
  // Mensaje de confirmación de añadir
  anadirInter.addEventListener("click", function () {
    AnadidoExitoso();
  });
});

function scrollVertical(windowWidth) {
  const div = document.getElementById("scrollable");
  const numeroInterventores = document.getElementsByClassName("usuario");

  let limiteElementos;

  // Definir los límites de elementos en función del ancho de la ventana
  // if (windowWidth <= 480) {
  //   limiteElementos = 5;
  // } else if (windowWidth <= 769 && windowWidth > 480) {
  //   limiteElementos = 7;
  if (windowWidth <= 1600 && windowWidth >= 770) {
    limiteElementos = 9;
  } else {
    limiteElementos = 15;
  }
  // Verificar los elementos
  if (numeroInterventores.length >= limiteElementos || windowWidth <= 700) {
    div.classList.add("scrollableInterventores");
  } else {
    if (div.classList.contains("scrollableInterventores")) {
      div.classList.remove("scrollableInterventores");
    }
  }
}
// Funcion que muestra la contraseña (sin editarla)
function mostrarContrasena(idVerImg, idPass, usuario) {
  let user = document.getElementById(usuario);
  let img = document.getElementById(idVerImg);
  let pass = document.getElementById(idPass);
  if (user.disabled) {
    if (pass.type === "password") {
      img.className = "fa fa-eye mostrar";
      pass.type = "text";
      //pass.disabled = false; // Evita editar la contraseña
    } else {
      img.className = "fa fa-eye-slash ocultar";
      pass.type = "password";
      pass.disabled = true;
    }
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
  }
  // else {
  //   img.className = "fa fa-eye-slash ocultar";
  //   contrasena.type = "password";
  //   contrasena.disabled = true;
  //   mesa.disabled = true;
  //   user.disabled = true;
  // }
}

// Mensaje de que se ha guardado con éxito el interventor
function guardadoExitoso() {
  let span = document.getElementById("copiado");
  span.textContent = "Guardando...";
}
// Añadido con exito
function AnadidoExitoso() {
  let span = document.getElementById("copiado");
  span.textContent = "Añadiendo...";
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
