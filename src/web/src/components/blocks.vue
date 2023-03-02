<template>
  <div class="container section">
    <h4>
      <center>Agregar registro</center>
    </h4>
    <form class="col s12" @submit.prevent="AgregarBlock">
      <div class="row">
        <div class="input-field col s12">
          <i class="material-icons prefix">add_circle</i>
          <input
            v-model="transaction.newbalanceDest"
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
            v-model="transaction.oldbalanceDest"
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
            v-model="transaction.nameOrig"
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
            v-model="transaction.step"
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
            v-model="transaction.type"
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
            v-model="transaction.amount"
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
            v-model="transaction.oldbalanceOrg"
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
            v-model="transaction.nameDest"
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
            v-model="transaction.newbalanceOrig"
            type="number"
            step="0.01"
            class="validate"
            required>
          <label for="transaction">newbalanceOrig</label>
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
          <i class="material-icons prefix">add_circle</i>
          <input disabled v-model="post.hash" type="text">
        </div>
      </div>
      <div class="row">
        <div class="input-field col s12">
          <i class="material-icons prefix">add_circle</i>
          <input disabled v-model="post.nonce" type="number">
        </div>
      </div>
      <button class="btn waves-effect waves-light" type="submit" name="enviar">Subir
        <i class="material-icons right">open_in_browser</i>
      </button>
    </form>
  </div>
</template>

<script>
import Services from "@/services/Services";
import M from "materialize-css";

export default {
  data() {
    return {
      transaction: {
        step: 0,
        type: "",
        amount: 0,
        nameOrig: "",
        oldbalanceOrg: 0,
        newbalanceOrig: 0,
        nameDest: "",
        oldbalanceDest: 0,
        newbalanceDest: 0
      },

      transactions: [],
      post: []
    };
  },

  created() {
    this.getBlocks();
  },

  mounted() {
    let elems = document.querySelectorAll("select");
    this.select_instances = M.FormSelect.init(elems, null);
  },

  methods: {
    getBlocks() {
      Services.getBlocks().then((response) => {
        this.blocks = response.data.blocks;
      });
    },

    AgregarBlock() {
      this.transactions.push(this.transaction);
      Services.postBlock({"transactions" : this.transactions}).then((response) => {
        this.post = response.data.newBlock;
        console.log(response.data.newBlock)
      });
    }
  }
};
</script>
