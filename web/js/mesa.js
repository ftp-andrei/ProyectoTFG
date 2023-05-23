// JS Gestion Mesas (Admin)

document.addEventListener("DOMContentLoaded", function () {
  const guardarCambios = document.getElementById("guardarCambios");
  const anadirMesa = document.getElementById("anadir");
  const eliminaMesa = document.getElementsByClassName("eliminar");
  const idEditarMesa = document.getElementsByClassName("editar");
  const idCopy = document.getElementsByClassName("copiar");
  const nombreMesas = document.getElementsByClassName("nombreMesa");
  const windowWidth = window.innerWidth; // Tamaño ventana
  for (let i = 0; i < nombreMesas.length; i++) {
    // Copia el nombre de mesa al portapapeles
    idCopy[i].addEventListener("click", function () {
      copiarNombreMesa(nombreMesas[i]);
    });
    // Habilita los campos para editar el Mesa
    idEditarMesa[i].addEventListener("click", function () {
      editarNombreMesa(nombreMesas[i]);
    });

    eliminaMesa[i].addEventListener("click", function () {
      borradoExitoso();
    });
  }
  window.addEventListener("resize", scrollVertical(windowWidth));
  guardarCambios.addEventListener("click", function () {
    guardadoExitoso();
  });

  anadirMesa.addEventListener("click", function () {
    AnadidoExitoso();
  });
});

function scrollVertical(windowWidth) {
  const div = document.getElementById("scrollable");
  const numMesas = document.getElementsByClassName("idMesa");

  let limiteElementos;

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
  if (numMesas.length >= limiteElementos || windowWidth <= 480) {
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
