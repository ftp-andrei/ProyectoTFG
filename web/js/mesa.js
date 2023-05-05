// JS Gestion Mesas (Admin)

document.addEventListener("DOMContentLoaded", function () {
  const idEditarMesa = document.getElementsByClassName("editar");
  const idCopy = document.getElementsByClassName("copiar");
  const nombreMesas = document.getElementsByClassName("nombreMesa");
  for (let i = 0; i < nombreMesas.length; i++) {
    const clickCopy = idCopy[i];
    const editarMesa = idEditarMesa[i];
    const nombre = nombreMesas[i];
    // Copia el nombre de mesa al portapapeles
    clickCopy.addEventListener("click", function () {
      copiarNombreMesa(nombre);
    });
    // Habilita los campos para editar el Mesa
    editarMesa.addEventListener("click", function () {
      editarNombreMesa(nombre);
    });
  }
});
// Copia la contrasena al portapapeles
function copiarNombreMesa(nombre) {
  navigator.clipboard
    .writeText(nombre.value)
    .then(() => {
      alert("Nombre de mesa copiado al portapapeles: " + nombre.value);
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
