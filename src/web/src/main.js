import { createApp } from "vue";
import App from "./App.vue";
import router from "./router";
import axios from 'axios'
import VueAxios from 'vue-axios'
import 'material-design-icons/iconfont/material-icons.css'
import 'materialize-css/dist/css/materialize.css'
createApp(App).use(router, axios, VueAxios).mount("#app");
