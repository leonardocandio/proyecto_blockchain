<template>
<h4><center>Transacciones dentro del bloque</center></h4>
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
            <tbody v-for="transaction in blocks" :key="blocks">
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

    },
}

</script>