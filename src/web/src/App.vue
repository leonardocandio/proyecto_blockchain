<template>
  <HeaderBar>
    <nav>
    <div class="nav-wrapper blue darken-2">
      <a href="" class="brand-logo right"
        >BlockChain
        <img
          src="https://i.imgur.com/kzh10NY.png"
          height="30"
          style="vertical-align: right"
          class="circle z-depth-2"
        />
      </a>
      <ul id="nav-mobile" class="left hide-on-med-and-down">
        <li><router-link to="/">Inicio</router-link></li>
      </ul>
    </div>
  </nav>
  </HeaderBar>
  <div class="content">
    <router-view></router-view>
  </div>
</template>

<script>
import M from 'materialize-css'

export default {
  mounted () {
    M.AutoInit()
},
}
</script>
