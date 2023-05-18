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
