import { createRouter, createWebHistory } from "vue-router";

const routes = [
  {
    path: "/",
    name: "home",
    component: () =>
      import(/* webpackChunkName: "Home" */ "../components/Home.vue"),
  },

  {
    path: "/blocks",
    name: "blocks",
    component: () =>
      import(/* webpackChunkName: "Blocks" */ "../components/blocks.vue"),
  },

  {
    path: "/search",
    name: "searchs",
    component: () =>
      import(/* webpackChunkName: "Search" */ "../components/searchs.vue"),
  },

  {
    path: "/view",
    name: "Vista",
    component: () =>
      import(/* webpackChunkName: "Search" */ "../components/vistas.vue"),
  },
  
  {
    path: "/transactions",
    name: "Transaction",
    component: () =>
      import(/* webpackChunkName: "Transaction" */ "../components/transactions.vue"),
  },
  //{
  //  path: "/about",
  //  name: "about",
    // route level code-splitting
    // this generates a separate chunk (about.[hash].js) for this route
    // which is lazy-loaded when the route is visited.
  //  component: () =>
  //    import(/* webpackChunkName: "about" */ "../views/AboutView.vue"),
  //},
];

const router = createRouter({
  history: createWebHistory(),
  routes,
});

export default router;
