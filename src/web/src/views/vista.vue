<template>
    <div>
      <h1></h1>
      <vistas />
    </div>
  </template>
  
  <script>
  // @ is an alias to /src
  import vistas from "@/components/vistas.vue";
  
  export default {
    name: "Vista",
    components: {
      vistas,
    },
  };
  </script>