<template>

  <div class="container section">
    <h4>
      <center>Busqueda dentro del Blockchain</center>
    </h4>
    <div id="select" class="input-field col s12">
      <select @change="changeType($event)">
        <option value="">Seleccione</option>
        <optgroup label="seleccion simple">
          <option value="1">Minimo valor</option>
          <option value="2">Maximo valor</option>
          <option value="3">Rango</option>
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
    <div class="input-field col s6" id="paramSelect" hidden="hidden">
      <select @change="changeParam($event)">
        <option value="">Seleccione</option>
        <optgroup label="seleccion simple">
          <option value="1">amount</option>
          <option value="2">oldbalanceDest</option>
          <option value="3">newbalanceDest</option>
          <option value="4">oldbalanceOrg</option>
          <option value="5">newbalanceOrig</option>
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
      <label>Ingresa el parámetro</label>
    </div>

    <div class="input-field col s6" id="limitInput" hidden="hidden">
      <input
        v-model="searchQuery.limit"
        id="input"
        type="number"
        class="validate"
        required>
      <label for="input">Ingrese la cantidad</label>
    </div>

    <div class="input-field col s6" id="rangeInputLow" hidden="hidden">
      <input
        v-model="searchQuery.rangeLow"
        id="input"
        type="number"
        class="validate"
        required>
      <label for="input">Ingrese el valor minimo</label>
    </div>
    <div id="rangeInputHigh" class="input-field col s6" hidden="hidden">
      <input
        v-model="searchQuery.rangeHigh"
        id="input"
        type="number"
        class="validate"
        required>
      <label for="input">Ingrese el valor maximo</label>
    </div>

    <button class="btn waves-effect waves-light" v-on:click="Busqueda()">Ingresar</button>
    <div class="container section">
      <table id="tabla" class="highlight" hidden="hidden">
        <thead>
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
        <tr v-for="tran in transaction">
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
      searchQuery: {
        param: "",
        limit: "",
        type: "",
        rangeLow: "",
        rangeHigh: ""
      },

      search: []
    };
  },

  mounted() {
    M.AutoInit();
    let elems = document.querySelectorAll("select");
    this.select_instances = M.FormSelect.init(elems, null);
  },

  methods: {
    changeType: function(event) {
      if (event.target.value === "1") {
        document.getElementById("limitInput").removeAttribute("hidden");
        document.getElementById("rangeInputHigh").setAttribute("hidden", "hidden");
        document.getElementById("rangeInputLow").setAttribute("hidden", "hidden");

        this.searchQuery.type = "min";
      } else if (event.target.value === "2") {
        document.getElementById("limitInput").removeAttribute("hidden");
        document.getElementById("rangeInputHigh").setAttribute("hidden", "hidden");
        document.getElementById("rangeInputLow").setAttribute("hidden", "hidden");

        this.searchQuery.type = "max";
      } else if (event.target.value === "3") {
        document.getElementById("limitInput").setAttribute("hidden", "hidden");
        document.getElementById("rangeInputHigh").removeAttribute("hidden");
        document.getElementById("rangeInputLow").removeAttribute("hidden");
        this.searchQuery.type = "range";
      }
      document.getElementById("paramSelect").removeAttribute("hidden");
    },
    changeParam: function(event) {
      if (event.target.value === "1") {
        this.searchQuery.param = "amount";
      } else if (event.target.value === "2") {
        this.searchQuery.param = "oldbalanceDest";
      } else if (event.target.value === "3") {
        this.searchQuery.param = "newbalanceDest";
      } else if (event.target.value === "4") {
        this.searchQuery.param = "oldbalanceOrg";
      } else if (event.target.value === "5") {
        this.searchQuery.param = "newbalanceOrig";
      }
    },
    Busqueda() {
      const transaction = { ...this.searchQuery };
      console.log("body: ", transaction);
      Services.searchBlock(transaction).then((response) => {
        this.search = response.data,
          console.log(response);
      });
      let element = document.getElementById("tabla");
      element.removeAttribute("hidden");
    }
  }
};
</script>