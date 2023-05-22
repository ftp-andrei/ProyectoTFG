document.addEventListener("DOMContentLoaded", function () {
  const windowWidth = window.innerWidth; // Tamaño ventana
  refresh();
  window.addEventListener("resize", scrollVertical(windowWidth));
});
// Metodo para refrescar los datos cada 30segundos
function refresh() {
  var meta = document.createElement("meta");
  meta.setAttribute("http-equiv", "refresh");
  meta.setAttribute("content", "30");

  document.head.appendChild(meta);
}

function scrollVertical(windowWidth) {
  const div = document.getElementById("scrollable");
  const numeroInterventores = document.getElementsByClassName("numeroMesaV");

  let limiteElementos;

  if (windowWidth <= 480) {
    limiteElementos = 5;
  } else if (windowWidth < 780 && windowWidth > 480) {
    limiteElementos = 8;
  } else if (windowWidth < 1600 && windowWidth > 780) {
    limiteElementos = 10;
  } else {
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
