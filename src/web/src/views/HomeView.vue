<template>
  <div class="home">
    <Home />
  </div>
</template>

<script>
// @ is an alias to /src
import Home from "@/components/Home.vue";

export default {
  name: "Home",
  components: {
    Home,
  },
};
</script>

<style>
body{
  height: 100%;
  width: 100%;
}
</style>
