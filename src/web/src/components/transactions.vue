<template>
<h4><center>Transacciones dentro del bloque</center></h4>
<div id="Loading">
    <center>
    <h6>Presione el boton de cargar</h6>    
    <div class="preloader-wrapper big active">
    <div class="spinner-layer spinner-blue-only">
      <div class="circle-clipper left">
        <div class="circle"></div>
      </div><div class="gap-patch">
        <div class="circle"></div>
      </div><div class="circle-clipper right">
        <div class="circle"></div>
      </div>
            </div>
        </div>
    </center>
    <div>
        <center><a class="waves-effect waves-light btn" v-on:click="LoadTransactions()">Cargar</a></center>
    </div>
    </div>
<div class="container section" id="contenido" hidden="true">
    <div class="container section">
    </div>
    <table class="highlight" id="reload">
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
            <tbody v-for="transaction in blocks" :key="blocks">
                <tr v-for="tran in transaction.transactions" v-if="transaction.index === index_number">
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
</template>

<script>
import Services from "@/services/Services";
import M from "materialize-css";
const index = localStorage.getItem('Index');
var index_number = parseInt(index);
const charge = localStorage.getItem('loading');
var charge_num = parseInt(charge);

export default{

    data() {
    return {
      blocks : [],
      index_number
    };
    },

    created() {
    this.getBlocks()
    },

    mounted(){
        M.AutoInit();
        var elems = document.querySelectorAll("select");
        this.select_instances = M.FormSelect.init(elems, null);
        this.TestHidden();
    },

    methods: {
        getBlocks() {
        Services.getBlocks().then((response) => {
        this.blocks = response.data.blocks;
        });
        },

        LoadTransactions(){
            window.location.reload()
            if(charge_num == 0){
                localStorage.setItem('loading',1)
            }
        },

        TestHidden(){
            if(charge_num == 1){
                document.getElementById('Loading').setAttribute('hidden',true)
                document.getElementById('contenido').removeAttribute('hidden')
            }
        }
    },
}

</script>