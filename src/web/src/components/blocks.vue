<template>
    <div class="container section">
    <h4><center>Agregar registro</center></h4>
    <form class="col s12">
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
          <input id="transaction" type="text" class="validate">
          <label for="transaction">step</label>
        </div>
      </div>
    
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
          <input id="transaction" type="text" class="validate">
          <label for="transaction">type</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
          <input id="transaction" type="text" class="validate">
          <label for="transaction">nameOrig</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
          <input id="transaction" type="text" class="validate">
          <label for="transaction">oldbalanceOrg</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
          <input id="transaction" type="text" class="validate">
          <label for="transaction">newbalanceOrig</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
          <input id="transaction" type="text" class="validate">
          <label for="transaction">nameDest</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
          <input id="transaction" type="text" class="validate">
          <label for="transaction">oldbalanceDest</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
          <input id="transaction" type="text" class="validate">
          <label for="transaction">newbalanceDest</label>
        </div>
      </div>
      <button class="btn waves-effect waves-light" type="submit" name="action">Subir
        <i class="material-icons right">open_in_browser</i>
        </button>
    </form>  
    <div class="container section">
        <h4><center>O ingrese un archivo de texto</center></h4>
        <form action="#">
            <div class="file-field input-field">
            <div class="btn">
             <span>File</span>
             <input type="file">
            </div>
            <div class="file-path-wrapper">
             <input class="file-path validate" type="text">
            </div>
    </div>
  </form>
      </div>
    </div>
</template>