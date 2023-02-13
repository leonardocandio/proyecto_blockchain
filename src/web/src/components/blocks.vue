<template>
    <div class="container section">
    <h4><center>Agregar registro</center></h4>
    <form class="col s12">
      <div class="row">
        <div class="input-field col s12">
          <i class="material-icons prefix">format_list_numbered</i>
          <input disabled value="Aqui va el numero de bloque" id="disabled" type="text" class="validate">
          <label for="disabled"></label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">filter_none</i>
          <input disabled value="Numero de Nonce" id="disabled" type="text" class="validate">
          <label for="disabled"></label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">account_balance</i>
          <input id="transaction" type="text" class="validate">
          <label for="transaction">Transaction</label>
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