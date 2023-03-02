<template>
  <div class="container section">
    <h4>
      Vistas de los bloques dentro de la API
    </h4>
    <!--horizontal scrolling cards    -->
    <div class="row-b">
      <div v-for="block in blocks" :key="blocks" class="card-b card sticky-action large">
        <div class="card-image waves-effect waves-block waves-light">
          <img class="activator"
               src="https://www.rentafija.com/wp-content/uploads/2022/02/como-funciona-el-blockchain-1.jpg">
        </div>
        <div class="card-content">
                <span class="activator grey-text text-darken-4">Hash: {{ block.hash }}<i
                  class="material-icons right">more_vert</i></span>
        </div>
        <div class="card-action">
          <p><a href="/transactions" v-on:click="Click(block.index)">Transactions</a></p>
        </div>
        <div class="card-reveal">
          <span class="card-title grey-text text-darken-4">Block<i
            class="material-icons right">close</i></span>
          <p>hash: {{ block.hash }}</p>
          <p>Nonce: {{ block.nonce }}</p>
          <p>Index: {{ block.index }}</p>
          <p>PrevHash: {{ block.prevhash }}</p>
          <p>Timestamp: {{ block.timestamp }}</p>
        </div>
      </div>
    </div>

    <button class="btn waves-effect waves-light" type="submit" name="enviar" v-on:click="Recalculo()">Recalculo
      <i class="material-icons right">open_in_browser</i>
    </button>
  </div>
</template>

<style>
/*
infinite horizontal scrolling cards
*/
.card-b {
  display: inline-block;
  margin: 1rem;
  width: 30rem;
  height: 20rem;
  position: relative;
  overflow: hidden;
}

.row-b {
  overflow-x: auto;
  white-space: nowrap;
}
</style>

<script>
import Services from "@/services/Services";
import M from "materialize-css";

const charge = localStorage.getItem("loading");
let charge_num = parseInt(charge);

export default {
  data() {
    return {
      blocks: []
    };
  },

  created() {
    this.getBlocks();
  },

  mounted() {
    var elems = document.querySelectorAll("select");
    this.select_instances = M.FormSelect.init(elems, null);
    this.TransacctionsView();
  },

  methods: {
    getBlocks() {
      Services.getBlocks().then((response) => {
        this.blocks = response.data.blocks;
      });
    },

    Click(index) {
      if (localStorage.getItem("Index") != null) {
        localStorage.removeItem("Index");
      }
      localStorage.setItem("Index", index);
    },

    TransacctionsView() {
      if (charge_num != 0) {
        localStorage.removeItem("loading");
        window.location.reload();
      }
      localStorage.setItem("loading", 0);
    },

    Recalculo(){
      Services.getRecalculo().then((response) => {
        this.blocks = response.data.blocks;
      });
    }
  }
};


</script>
