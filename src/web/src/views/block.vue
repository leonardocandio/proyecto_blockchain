<template>
  <div>
    <h1></h1>
    <blocks />
  </div>
</template>
  
<script>
  // @ is an alias to /src
import blocks from "@/components/blocks.vue";
  
export default {
  name: "Blocks",
  components: {
      blocks,
  },
};
</script>