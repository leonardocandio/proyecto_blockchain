<template>
    <div>
      <h1></h1>
      <transaciones />
    </div>
  </template>
    
  <script>
    // @ is an alias to /src
  import transaciones from "@/components/transactions.vue";
    
  export default {
    name: "Transaction",
    components: {
        transaciones,
    },
  };
  </script>