<template>
  <div class="container section">
    <h4><center>Vistas de los bloques dentro de la API</center></h4>
    <div class="row">
      <center>
      <div class="col s4">
      <center>
        <div class="card sticky-action large" v-for="block in blocks" :key="blocks">
          <div class="card-image waves-effect waves-block waves-light">
            <img class="activator" src="https://i.imgur.com/oXZ9FeNh.png">
          </div>
          <div class="card-content">
            <span class="card-title activator grey-text text-darken-4">HASH: {{ block.hash }}<i class="material-icons right">more_vert</i></span>
          </div>
          <div class="card-action">
            <a v-on:click="Click(block.index)">Transacciones</a>
            <button class="btn waves-effect waves-light" v-on:click="Click(block.index)">Transacciones
              <i class="material-icons right">send</i>
              <router-link to="/transactions"></router-link>
            </button>
          </div>
          <div class="card-reveal">
            <span class="card-title grey-text text-darken-4">HASH: {{ block.hash }}<i class="material-icons right">close</i></span>
            <p>Nonce: {{ block.nonce }}</p>
            <p>Index: {{ block.index }}</p>
            <p>Previus Hash: {{ block.prevhash }}</p>
            <p>timestamp: {{ block.timestamp }}</p>
          </div>
        </div>
      </center></div>
    </center></div>
  </div>
</template>

<script>
import Services from "@/services/Services";
import M from "materialize-css";
const charge = localStorage.getItem('loading');
var charge_num = parseInt(charge);

export default{
    data() {
    return {
      blocks : [],
        };
    },

    created() {
    this.getBlocks();
    },

    mounted(){
        var elems = document.querySelectorAll("select");
        this.select_instances = M.FormSelect.init(elems, null);
        this.TransacctionsView();
    },

    methods: {
        getBlocks() {
        Services.getBlocks().then((response) => {
        this.blocks = response.data.blocks;
          })
        },

        Click(index) {
          if(localStorage.getItem('Index') != null){
            localStorage.removeItem('Index')
          }
          localStorage.setItem('Index', index)
        },

        TransacctionsView(){
          if(charge_num != 0){
            localStorage.removeItem('loading')
            window.location.reload()
          }
          localStorage.setItem('loading', 0)
        },
    }
}


</script>
