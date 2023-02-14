<template>
  <div class="container section">
    <div class="row">
      <div class="col s3">
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
    </div>
  </div>
</template>

<!-- Add "scoped" attribute to limit CSS to this component only -->