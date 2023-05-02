document.addEventListener("DOMContentLoaded", function () {
  const idVerImgs = document.getElementsByClassName("ocultar");
  const idVerPass = document.getElementsByClassName("ocultarPass");
  const idCopy = document.getElementsByClassName("copiar");
  for (let i = 0; i < idVerImgs.length; i++) {
    const idVerImg = idVerImgs[i];
    const idPass = idVerPass[i];
    const clickCopy = idCopy[i];
    // Agregar un evento click para mostrar las contraseñas
    idVerImg.addEventListener("click", function () {
      mostrarContrasena(idVerImg.id, idPass.id);
    });
    // Copia la contrasena al portapapeles
    clickCopy.addEventListener("click", function () {
      copiarContrasena(idPass.id);
    });
  }
});
// Funcion que muestra y oculta las contraseñas
function mostrarContrasena(idVerImg, idPass) {
  let img = document.getElementById(idVerImg);
  let pass = document.getElementById(idPass);
  if (pass.type === "password") {
    img.className = "fa fa-eye mostrar";
    pass.type = "text";
    // pass.disabled = false;
  } else {
    // pass.disabled = true;
    img.className = "fa fa-eye-slash ocultar";
    pass.type = "password";
  }
}
// Copia la contrasena al portapapeles
function copiarContrasena(idPass) {
  let contrasena = document.getElementById(idPass).value;
  navigator.clipboard
    .writeText(contrasena)
    .then(() => {
      alert("Contraseña copiada al portapapeles: " + contrasena);
    })
    .catch((error) => {
      console.error("Error al copiar al portapapeles: ", error);
    });
}
