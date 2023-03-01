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
          <option value="4">Identificador</option>
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
    <div id="idInputStep" class="input-field col s6" hidden="hidden">
      <input
        v-model="searchStep"
        id="input"
        type="number"
        class="validate"
        required>
      <label for="input">Ingrese step</label>
    </div>
    <div id="idInputNameOrig" class="input-field col s6" hidden="hidden">
      <input
        v-model="searchNameOrig"
        id="input"
        type="text"
        class="validate"
        required>
      <label for="input">Ingrese nameOrig</label>
    </div>
    <div id="idInputNameDest" class="input-field col s6" hidden="hidden">
      <input
        v-model="searchNameDest"
        id="input"
        type="text"
        class="validate"
        required>
      <label for="input">Ingrese nameDest</label>
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
        <th>step</th>
        <th>type</th>
        <th>amount</th>
        <th>nameOrig</th>
        <th>oldbalanceOrg</th>
        <th>newbalanceOrig</th>
        <th>nameDest</th>
        <th>oldbalanceDest</th>
        <th>newbalanceDest</th>
        </thead>
        <tbody v-for="transaction in search" :key="search">
        <tr v-for="tran in transaction">
          <td>{{ tran.step }}</td>
          <td>{{ tran.type }}</td>
          <td>{{ tran.amount }}</td>
          <td>{{ tran.nameOrig }}</td>
          <td>{{ tran.oldbalanceOrg }}</td>
          <td>{{ tran.newbalanceOrig }}</td>
          <td>{{ tran.nameDest }}</td>
          <td>{{ tran.oldbalanceDest }}</td>
          <td>{{ tran.newbalanceDest }}</td>
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
      searchStep: "",
      searchNameOrig: "",
      searchNameDest: "",
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
        document.getElementById("paramSelect").removeAttribute("hidden");
        document.getElementById("idInputStep").setAttribute("hidden", "hidden");
        document.getElementById("idInputNameOrig").setAttribute("hidden", "hidden");
        document.getElementById("idInputNameDest").setAttribute("hidden", "hidden");

        this.searchQuery.type = "min";
      } else if (event.target.value === "2") {
        document.getElementById("limitInput").removeAttribute("hidden");
        document.getElementById("rangeInputHigh").setAttribute("hidden", "hidden");
        document.getElementById("rangeInputLow").setAttribute("hidden", "hidden");
        document.getElementById("paramSelect").removeAttribute("hidden");
        document.getElementById("idInputStep").setAttribute("hidden", "hidden");
        document.getElementById("idInputNameOrig").setAttribute("hidden", "hidden");
        document.getElementById("idInputNameDest").setAttribute("hidden", "hidden");

        this.searchQuery.type = "max";
      } else if (event.target.value === "3") {
        document.getElementById("limitInput").setAttribute("hidden", "hidden");
        document.getElementById("rangeInputHigh").removeAttribute("hidden");
        document.getElementById("rangeInputLow").removeAttribute("hidden");
        document.getElementById("paramSelect").removeAttribute("hidden");
        document.getElementById("idInputStep").setAttribute("hidden", "hidden");
        document.getElementById("idInputNameOrig").setAttribute("hidden", "hidden");
        document.getElementById("idInputNameDest").setAttribute("hidden", "hidden");

        this.searchQuery.type = "range";
      } else if (event.target.value === "4") {
        document.getElementById("paramSelect").setAttribute("hidden", "hidden");
        document.getElementById("limitInput").setAttribute("hidden", "hidden");
        document.getElementById("rangeInputHigh").setAttribute("hidden", "hidden");
        document.getElementById("rangeInputLow").setAttribute("hidden", "hidden");
        document.getElementById("idInputStep").removeAttribute("hidden");
        document.getElementById("idInputNameOrig").removeAttribute("hidden");
        document.getElementById("idInputNameDest").removeAttribute("hidden");
        this.searchQuery.param = "all";
      }
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
      if (this.searchQuery.param === "all") {
        this.searchQuery.type = this.searchStep + this.searchNameOrig + this.searchNameDest;
      }
      const transaction = { ...this.searchQuery };
      console.log("body: ", transaction);
      Services.searchBlock(transaction).then((response) => {
        this.search = response.data;
      });
      let element = document.getElementById("tabla");
      element.removeAttribute("hidden");
    }
  }
};
</script>