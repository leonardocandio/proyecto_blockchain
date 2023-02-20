n<template>
    <div class="container section">
    <h4><center>Agregar registro</center></h4>
    <form class="col s12" @submit.prevent="AgregarBlock">
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
          <input 
          v-model = "block.step"
          type="number"
          class="validate"
          required>
          <label for="transaction">step</label>
        </div>
      </div>
    
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
            <input 
            v-model = "block.type"
            type="text"
            class="validate"
            required>
          <label for="transaction">type</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
            <input 
            v-model = "block.amount"
            type="number"
            class="validate"
            required>
          <label for="transaction">amount</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
            <input 
          v-model = "block.nameOrig"
          type="text"
          class="validate"
          required>
          <label for="transaction">nameOrig</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
            <input 
          v-model = "block.oldbalanceOrg"
          type="number"
          class="validate"
          required>
          <label for="transaction">oldbalanceOrg</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
            <input 
          v-model = "block.newbalanceOrig"
          type="number"
          class="validate"
          required>
          <label for="transaction">newbalanceOrig</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
            <input 
          v-model = "block.nameDest"
          type="text"
          class="validate"
          required>
          <label for="transaction">nameDest</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
            <input 
          v-model = "block.oldbalanceDest"
          type="number"
          class="validate"
          required>
          <label for="transaction">oldbalanceDest</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
            <input 
          v-model = "block.newbalanceDest"
          type="number"
          class="validate"
          required>
          <label for="transaction">newbalanceDest</label>
        </div>
      </div>
      <button class="btn waves-effect waves-light" type="submit" name="enviar">Subir
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

<script>
import Services from "@/services/Services";
import M from "materialize-css";

export default {
  data() {
    return {
      block: {
        step: "",
        type: "",
        amount: "",
        nameOrig: "",
        oldbalanceOrg: "",
        newbalanceOrig: "",
        nameDest: "",
        oldbalanceDest: "",
        newbalanceDest: "",
      },

      blocks : [],
    };
  },

  created() {
    this.getBlocks();
    },

    mounted(){
        var elems = document.querySelectorAll("select");
        this.select_instances = M.FormSelect.init(elems, null);
    },

    methods: {
        getBlocks() {
        Services.getBlocks().then((response) => {
        this.blocks = response.data.blocks;
          });
        },

        AgregarBlock(){
          const block = { ...this.block };
          console.log("body: ", block);
          Services.postPost(block).then((response) => {
          this.blocks = response.data.blocks;
          });
        },
    }
}
</script>
