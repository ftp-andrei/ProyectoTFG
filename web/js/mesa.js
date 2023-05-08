// JS Gestion Mesas (Admin)

document.addEventListener("DOMContentLoaded", function () {
  const guardarCambios = document.getElementById("guardarCambios");

  const idEditarMesa = document.getElementsByClassName("editar");
  const idCopy = document.getElementsByClassName("copiar");
  const nombreMesas = document.getElementsByClassName("nombreMesa");
  for (let i = 0; i < nombreMesas.length; i++) {
    // Copia el nombre de mesa al portapapeles
    idCopy[i].addEventListener("click", function () {
      copiarNombreMesa(nombreMesas[i]);
    });
    // Habilita los campos para editar el Mesa
    idEditarMesa[i].addEventListener("click", function () {
      editarNombreMesa(nombreMesas[i]);
    });
  }

  guardarCambios.addEventListener("click", function () {
    guardadoExitoso();
  });
});
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

function editarNombreMesa(nombre) {
  if (nombre.disabled) {
    nombre.disabled = false;
    nombre.select();
  } else {
    nombre.disabled = true;
  }
}

// Guardado con éxito
function guardadoExitoso() {
  let span = document.getElementById("copiado");
  span.textContent = "Guardado con éxito";
}
