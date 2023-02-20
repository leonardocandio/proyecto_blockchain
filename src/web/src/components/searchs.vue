<template>

  <div class="container section">
    <h4><center>Busqueda dentro del Blockchain</center></h4>
    <div id="select" class="input-field col s12">
    <select @change="BuscarBlock($event)">
      <option value = "">Seleccione</option>
      <optgroup label="seleccion simple">
        <option value = "1">Minimo valor</option>
        <option value = "2">Maximo valor</option>
      </optgroup>
      <!--<optgroup label="ingresar texto">
        <option value="3">ingresa un key</option>
        <option value="4">inicia con ...</option>
        <option value="5">Esta contenido dentro de ...</option>
      </optgroup>
      <optgroup label="ingresar rango">
        <option value="6">Ingresa un rango</option>
      </optgroup>-->
    </select>
    <label>Ingresa el tipo de búsqueda</label>
  </div>

  <!--<div id = "input_text" class="input-field col s12">
        <input id="input" type="text" class="validate">
        <label for="input">Ingrese el parametro</label>
  </div>-->

  <!--<div id="test-slider"></div>-->
  <div class="container section">
        <table class="highlight">
            <thead>
                <th>Index</th>
                <th>newbalanceDest</th>
                <th>oldbalanceDest</th>
                <th>nameOrig</th>
                <th>step</th>
                <th>type</th>
                <th>amount</th>
                <th>oldbalanceOrg</th>
                <th>nameDest</th>
                <th>newbalanceOrg</th>
            </thead>
            <tbody v-for="transaction in search" :key="search">
                <tr v-for="tran in transaction.transactions">
                    <td>{{ transaction.index }}</td>
                    <td>{{ tran.newbalanceDest }}</td>
                    <td>{{ tran.oldbalanceDest }}</td>
                    <td>{{ tran.nameOrig }}</td>
                    <td>{{ tran.step }}</td>
                    <td>{{ tran.type }}</td>
                    <td>{{ tran.amount }}</td>
                    <td>{{ tran.oldbalanceOrg }}</td>
                    <td>{{ tran.nameDest }}</td>
                    <td>{{ tran.newbalanceOrig }}</td>
                </tr>
            </tbody>
        </table>
</div>
  </div>
</template>

<script>
import Services from "@/services/Services";
import M from "materialize-css";

export default {
  data() {
    return {
      block1: {
        key: "min",
      },

      block2: {
        key: "max",
      },

      search : [],
    };
  },

  mounted(){
      M.AutoInit();
      var elems = document.querySelectorAll("select");
      this.select_instances = M.FormSelect.init(elems, null);
  },

  methods: {
      BuscarBlock: function(event){
        if(event.target.value == "1"){
          const transaction = { ...this.block1 };
          console.log("body: ", transaction);
          Services.searchBlock(transaction).then((response) => {
          this.search = response.data.search;
          });
        }
        else if(event.target.value == "2"){
          const transaction = { ...this.block2 };
          console.log("body: ", transaction);
          Services.searchBlock(transaction).then((response) => {
          this.search = response.data.search;
          });
        }
        }
      },
  }
</script>

