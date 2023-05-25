// JS Gestion Mesas (Admin)

document.addEventListener("DOMContentLoaded", function () {
  // Botones
  const guardarCambios = document.getElementById("guardarCambios");
  const anadirMesa = document.getElementById("anadir");
  const eliminaMesa = document.getElementsByClassName("eliminar");
  const idEditarMesa = document.getElementsByClassName("editar");
  const idCopy = document.getElementsByClassName("copiar");
  // Valor Nombre mesa
  const nombreMesas = document.getElementsByClassName("nombreMesa");
  // Tamaño ventana
  const windowWidth = window.innerWidth;
  for (let i = 0; i < nombreMesas.length; i++) {
    // Copia el nombre de mesa al portapapeles
    idCopy[i].addEventListener("click", function () {
      copiarNombreMesa(nombreMesas[i]);
    });
    // Habilita los campos para editar el Mesa
    idEditarMesa[i].addEventListener("click", function () {
      editarNombreMesa(nombreMesas[i]);
    });
    // Elimina una mesa
    eliminaMesa[i].addEventListener("click", function () {
      confirmacion(eliminaMesa[i].id);
    });
  }
  // Añade scroll vertical si lo necesita.
  window.addEventListener("resize", scrollVertical(windowWidth));
  // Mensaje de guardado exitoso
  guardarCambios.addEventListener("click", function () {
    guardadoExitoso();
  });
  // Mensaje de añadido exitoso
  anadirMesa.addEventListener("click", function () {
    AnadidoExitoso();
  });
});
// Metodo para hacer el scroll horizontal/vertical
function scrollVertical(windowWidth) {
  const div = document.getElementById("scrollable");
  const numMesas = document.getElementsByClassName("idMesa");

  let limiteElementos = 0;

  // Definir los límites de elementos en función del ancho de la ventana
  if (windowWidth <= 480) {
    limiteElementos = 5;
  } else if (windowWidth <= 769 && windowWidth > 480) {
    limiteElementos = 7;
  } else if (windowWidth <= 1600 && windowWidth >= 770) {
    limiteElementos = 9;
  } else {
    limiteElementos = 15;
  }
  // Verificar los elementos
  if (numMesas.length >= limiteElementos || windowWidth <= 770) {
    div.classList.add("scrollableMesas");
  } else {
    if (div.classList.contains("scrollableMesas")) {
      div.classList.remove("scrollableMesas");
    }
  }
}
// Copia la contrasena al portapapeles
function copiarNombreMesa(nombre) {
  navigator.clipboard
    .writeText(nombre.value)
    .then(() => {
      let span = document.getElementById("copiado");
      span.textContent = "¡Nombre de mesa copiado al portapapeles!";

      setTimeout(function cambiarTexto() {
        span.textContent = "";
      }, 2000);
    })
    .catch((error) => {
      console.error("Error al copiar al portapapeles: ", error);
    });
}

// Funcion que habilita los campos para editar la Mesa
function editarNombreMesa(nombre) {
  if (nombre.disabled) {
    nombre.disabled = false;
    nombre.select();
  }
}

// Guardado con éxito
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
