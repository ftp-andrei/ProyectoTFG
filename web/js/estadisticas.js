document.addEventListener("DOMContentLoaded", function () {
  refresh();
});
// Metodo para refrescar los datos cada 30segundos
function refresh() {
  var meta = document.createElement("meta");
  meta.setAttribute("http-equiv", "refresh");
  meta.setAttribute("content", "30");

  document.head.appendChild(meta);
}
