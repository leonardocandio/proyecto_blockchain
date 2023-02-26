<template>
  <div class="container section">
    <div class="row">
      <div class="col s4">
        <div class="card large">
          <div class="card-image">
            <img src="https://i.imgur.com/oXZ9FeNh.png" />
          </div>
          <div class="card-content activator">
            <p class="card-title">Agregar registro</p>
            <p>Agregue un registro en nuestra base de datos</p>
          </div>
          <div class="card-action">
            <router-link to="/blocks">¡Vamos allá!</router-link>
          </div>
        </div>
      </div>

      <div class="col s4">
        <div class="card large">
          <div class="card-image">
            <img
              src="https://blog.ida.cl/wp-content/uploads/sites/5/2019/10/GoogleBusquedasMonopolio_BLOG-655x470.png"
            />
          </div>
          <div class="card-content activator">
            <p class="card-title">Hacer una busqueda</p>
            <p>Haga consultas dentro de nuestra base de datos</p>
          </div>
          <div class="card-action">
            <router-link to="/search">¡Vamos allá!</router-link>
          </div>
        </div>
      </div>
      <div class="col s4">
        <div class="card large">
          <div class="card-image">
            <img
              src="https://m.economictimes.com/thumb/msid-83710496,width-1000,height-659,resizemode-4,imgsize-552110/cryptocurrency.jpg"
            />
          </div>
          <div class="card-content activator">
            <p class="card-title">Vista de bloques</p>
            <p>Vea los bloques hechos de nuestra API</p>
          </div>
          <div class="card-action">
            <router-link to="/view">¡Vamos allá!</router-link>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>

import M from "materialize-css";

export default {
  mounted(){
    M.AutoInit()
    document.addEventListener('DOMContentLoaded', function() {
    var elems = document.querySelectorAll('.carousel');
    var instances = M.Carousel.init(elems);
    });
}
}
</script>

<style>

body{
  display:ruby;
}

</style>