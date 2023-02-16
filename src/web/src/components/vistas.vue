<template>
    <h4><center>Vistas de los bloques dentro de la API</center></h4>
    <table class="centered">
        <thead>
          <tr>
              <th>BLOQUE</th>
          </tr>
        </thead>
        <table class="centered">
        <thead>
          <tr>
              <th>Hash</th>
              <th>Nonce</th>
              <th>Index</th>
              <th>prevhash</th>
              <th>transactions</th>
              <th>timestamp</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="block in blocks" :key="blocks">
            <td>{{ block.hash }}</td>
            <td>{{ block.nonce }}</td>
            <td>{{ block.index }}</td>
            <td>{{ block.prevhash }}</td>
            <td><router-link to="/transactions">Acceda al contenido de las transacciones</router-link></td>
            <td>{{ block.timestamp }}</td>
          </tr>
        </tbody>
      </table>
      </table>
</template>

<script>
import Services from "@/services/Services";
import M from "materialize-css";

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
    },

    methods: {
        getBlocks() {
        Services.getBlocks().then((response) => {
        this.blocks = response.data.blocks;
      });
    },
    }
}


</script>
