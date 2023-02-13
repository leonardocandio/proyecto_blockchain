<template>
  <div class="container section">
    <h4><center>Busqueda dentro del Blockchain</center></h4>
  <div id="select" class="input-field col s12">
    <select>
      <optgroup label="seleccion simple">
        <option value="1">Minimo valor</option>
        <option value="2">Maximo valor</option>
      </optgroup>
      <optgroup label="ingresar texto">
        <option value="3">ingresa un key</option>
        <option value="4">inicia con ...</option>
        <option value="5">Esta contenido dentro de ...</option>
      </optgroup>
      <optgroup label="ingresar rango">
        <option value="6">Ingresa un rango</option>
      </optgroup>
    </select>
    <label>Ingresa el tipo de búsqueda</label>
  </div>

  <div id = "input_text" class="input-field col s12">
        <input id="input" type="text" class="validate">
        <label for="input">Ingrese el parametro</label>
  </div>

  <div id="test-slider"></div>
  
  </div>
</template>

<script>
export default {
  mounted(){
    M.AutoInit();
    var slider = document.getElementById('test-slider');
  noUiSlider.create(slider, {
   start: [0, 100],
   connect: true,
   step: 1,
   orientation: 'horizontal', // 'horizontal' or 'vertical'
   range: {
     'min': 0,
     'max': 100
   },
   format: wNumb({
     decimals: 0
   })
  });
  },
}
</script>

