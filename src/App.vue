<template>
  <div id="app" :style="style">
    <div class="inner">
      <div class="inner-top">
        <focused-window />
        <spotify />
        <memory />
        <CPU />
        <temperature />
        <network-manager />
        <date-time />
      </div>
      <div class="inner-bottom">
        <workspaces />
      </div>
    </div>
    <!-- <dashboard /> -->
  </div>
</template>

<script>
import NetworkManager from './components/NetworkManager.vue'
import Workspaces from './components/Workspaces.vue'
import Spotify from './components/Spotify.vue'
import Memory from './components/Memory.vue'
import DateTime from './components/Time.vue'
import FocusedWindow from './components/FocusedWindow.vue'
import CPU from './components/CPU.vue'
import Temperature from './components/Temperature.vue'
// import Dashboard from './components/Dashboard.vue'
import Socket from '@/service/socket'

import gruvbox from '@/themes/srcery.json'

export default {
  name: 'App',

  components: {
    Workspaces,
    Spotify,
    Memory,
    DateTime,
    FocusedWindow,
    NetworkManager,
    CPU,
    // Dashboard,
    Temperature
  },

  data() {
    return {
      colors: gruvbox
    }
  },

  mounted() {
    Socket.connect().then(() => {})
  },

  methods: {
    buildColor(obj) {
      return Object.keys(obj).reduce((acc, name) => {
        acc.push({ name, value: obj[name] })
        return acc
      }, [])
    }
  },

  computed: {
    style() {
      return Object.keys(this.colors)
        .reduce((acc, key) => {
          const colors = this.buildColor(this.colors[key])
          acc.push(...colors)
          return acc
        }, [])
        .reduce((acc, color) => {
          acc['--' + color.name] = color.value
          return acc
        }, {})
    }
  }
}
</script>

<style lang="scss">
/* @font-face { */
/*   font-family: 'DIN'; */
/*   src: url('/D-DIN.otf'); */
/*   font-weight: normal; */
/* } */
/*  */
/* @font-face { */
/*   font-family: 'DIN'; */
/*   src: url('/D-DIN-Bold.otf'); */
/*   font-weight: bold; */
/* } */
/*  */
/* @font-face { */
/*   font-family: 'DIN Expanded'; */
/*   src: url('/D-DINExp.otf'); */
/*   font-weight: normal; */
/* } */
/*  */
/* @font-face { */
/*   font-family: 'DIN Expanded'; */
/*   src: url('/D-DINExp-Bold.otf'); */
/*   font-weight: bold; */
/* } */
/*  */
/* @font-face { */
/*   font-family: 'DIN Condensed'; */
/*   src: url('/D-DINCondensed.otf'); */
/*   font-weight: normal; */
/* } */
/*  */
/* @font-face { */
/*   font-family: 'DIN Condensed'; */
/*   src: url('/D-DINCondensed-Bold.otf'); */
/*   font-weight: bold; */
/* } */
/*  */
/* @font-face { */
/*   font-family: 'Kayak'; */
/*   src: url('/Kayak Sans Regular.otf'); */
/*   font-weight: normal; */
/* } */
/*  */
/* @font-face { */
/*   font-family: 'Kayak'; */
/*   src: url('/Kayak Sans Bold.otf'); */
/*   font-weight: bold; */
/* } */
/*  */
/* @font-face { */
/*   font-family: 'Kayak'; */
/*   src: url('/Kayak Sans Light.otf'); */
/*   font-weight: 200; */
/* } */

body {
  padding: 0;
  margin: 0;
  user-select: none;
  cursor: default;
  text-transform: uppercase;
  font-weight: normal;
  letter-spacing: 0.15em;
  font-size: 12px;
  /* background: rgba(0, 0, 255, 0); */
  /* background: rgba(black, 0); */
}
a {
  cursor: pointer;
}
:root {
  --border: rgba(255, 255, 255, 0.08);
}
#app {
  font-family: 'DIN', Kayak, Inter, Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: var(--foreground);
  height: 64px;
}

* {
  box-sizing: border-box;
}

.inner {
  background: var(--background);
  display: flex;
  flex-direction: column;
  height: 100%;
  border-bottom: 1px solid var(--border);
}

.inner-top,
.inner-bottom {
  display: flex;
  align-items: center;
  flex: 1;
  position: relative;
}
.inner-top {
  border-bottom: 1px solid var(--border);
  padding: 0 0.5em;

  > div {
    padding: 0 0.5rem;
  }
}

.icon {
  line-height: 1;

  > i {
    vertical-align: middle;
  }
}

.pill {
  font-weight: 800;
  text-transform: uppercase;
  border-radius: 2px;
  padding: 0 0.2em;
  display: flex;
  align-items: center;
  height: 16px;

  &.is-progress {
    min-width: 8rem;
    border: 0.5px solid currentColor;
    position: relative;
    justify-content: flex-end;
    font-weight: normal;
    color: var(--cursor);
    > div {
      position: absolute;
      top: 0;
      left: 0;
      width: 100%;
      height: 100%;
      transform-origin: left;
      background: currentColor;
      opacity: 0.3;
    }
  }
}
</style>
