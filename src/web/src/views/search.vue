<template>
    <div>
      <h1></h1>
      <search />
    </div>
  </template>
  
  <script>
  // @ is an alias to /src
  import search from "@/components/searchs.vue";
  
  export default {
    name: "Search",
    components: {
      search,
    },
  };
  </script>