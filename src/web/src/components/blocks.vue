<template>
    <div class="container section">
    <h4><center>Agregar registro</center></h4>
    <form class="col s12" @submit.prevent="AgregarBlock">
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
          <input 
          v-model = "block.transactions.newbalanceDest"
          type="number"
          step="0.01"
          class="validate"
          required>
          <label for="transaction">newbalanceDest</label>
        </div>
      </div>
    
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
            <input 
            v-model = "block.transactions.oldbalanceDest"
            type="number"
            step="0.01"
            class="validate"
            required>
          <label for="transaction">oldbalanceDest</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
            <input 
            v-model = "block.transactions.nameOrig"
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
          v-model = "block.transactions.step"
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
          v-model = "block.transactions.type"
          type="text"
          class="validate"
          required>
          <label for="transaction">Type</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
            <input 
          v-model = "block.transactions.amount"
          type="number"
          step="0.01"
          class="validate"
          required>
          <label for="transaction">Amount</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
            <input 
          v-model = "block.transactions.oldbalanceOrg"
          type="number"
          step="0.01"
          class="validate"
          required>
          <label for="transaction">oldbalanceOrg</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
            <i class="material-icons prefix">add_circle</i>
            <input 
          v-model = "block.transactions.nameDest"
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
          v-model = "block.transactions.newbalanceOrig"
          type="number"
          step="0.01"
          class="validate"
          required>
          <label for="transaction">newbalanceOrig</label>
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
        transactions: {
        step: "",
        type: "",
        amount: "",
        nameOrig: "",
        oldbalanceOrg: "",
        newbalanceOrig: "",
        nameDest: "",
        oldbalanceDest: "",
        newbalanceDest: "",
        }
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
          Services.postBlock(block).then((response) => {
          this.blocks = response.data;
          });
        },
    }
}
</script>
