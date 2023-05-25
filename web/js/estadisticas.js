document.addEventListener("DOMContentLoaded", function () {
  const windowWidth = window.innerWidth; // Tamaño ventana
  refresh();
  window.addEventListener("resize", scrollVertical(windowWidth));

  grafico(datos);
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
  const div2 = document.getElementById("grafo");
  const numeroInterventores = document.getElementsByClassName("numeroMesaV");

  let limiteElementos;

  if (windowWidth <= 480) {
    limiteElementos = 5;
  } else if (windowWidth < 769 && windowWidth > 480) {
    limiteElementos = 8;
  } else if (windowWidth < 1600 && windowWidth > 770) {
    limiteElementos = 10;
  } else {
    limiteElementos = 15;
  }
  if (numeroInterventores.length >= limiteElementos || windowWidth <= 770) {
    div.classList.add("scrollableEstadisticas");
  } else {
    if (div.classList.contains("scrollableEstadisticas")) {
      div.classList.remove("scrollableEstadisticas");
    }
  }
}

function grafico(datosSinFiltrar) {
  // Obtener el contexto del lienzo del gráfico
  var ctx = document.getElementById("grafico").getContext("2d");

  // Filtrar los datos para que no se muestren las mesas sin votantes
  var datos = datosSinFiltrar.filter((e) => e.TotalVotantes != 0);

  // Crear el gráfico de barras
  var chart = new Chart(ctx, {
    type: "bar",
    data: {
      labels: datos.map((e) => "Mesa " + e.idMesa),
      datasets: [
        {
          label: "Total de Votantes",
          data: datos.map((e) => e.TotalVotantes),
          backgroundColor: "#3399CC",
        },
        {
          label: "Votado",
          data: datos.map((e) => e.VotadoV),
          backgroundColor: "#66CCCC",
        },
        {
          label: "No Votado",
          data: datos.map((e) => e.NoVotadoV),
          backgroundColor: "#FF6699",
        },
      ],
    },
    options: {
      responsive: true,
      // Para las lineas del grafico
      scales: {
        x: {
          grid: {
            display: false,
          },
        },
        y: {
          beginAtZero: true,
          grid: {
            display: true,
          },
        },
      },
    },
  });
}
