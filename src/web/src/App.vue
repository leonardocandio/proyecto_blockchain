<template>
  {{ blocks }}
</template>

<script>
export default {
  name: "App",

  data() {
    return {
      loading: false,
      blocks: null,
    };
  },
  methods: {
    async getBlocks() {
      this.loading = true;
      const response = await fetch("http://localhost:3000/blocks", {
        method: "GET",
      });
      this.blocks = JSON.parse(await response.text());
      this.loading = false;
    },
  },

  created() {
    this.$watch(
      () => this.$route.params,
      () => {
        this.getBlocks();
      },
      { immediate: true }
    );
  },
};
</script>

<style scoped></style>
