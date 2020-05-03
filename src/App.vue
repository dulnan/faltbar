<template>
  <div id="app" :style="style">
    <div class="inner">
      <div class="inner-top">
        <spotify />
        <focused-window />
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
import Socket from '@/service/socket'

import gruvbox from '@/themes/ayu.json'

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
body {
  padding: 0;
  margin: 0;
  user-select: none;
  cursor: default;
  /* background: rgba(0, 0, 255, 0); */
  /* background: rgba(black, 0); */
}
a {
  cursor: pointer;
}
#app {
  font-family: Inter, Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: var(--foreground);
  font-size: 13px;
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
  border-bottom: 1px solid rgba(white, 0.1);
}

.inner-top,
.inner-bottom {
  display: flex;
  align-items: center;
  flex: 1;
  position: relative;
}
.inner-top {
  border-bottom: 1px solid rgba(white, 0.1);
  padding: 0 0.5em;

  > div {
    padding: 0 0.5rem;
  }
}

.icon {
  font-size: 1.25em;
  line-height: 1;

  > i {
    vertical-align: middle;
  }
}

.pill {
  font-weight: 700;
  text-transform: uppercase;
  font-size: 12px;
  border-radius: 3px;
  padding: 0 0.2em;
  display: flex;
  align-items: center;

  &.is-progress {
    min-width: 8rem;
    border: 1px solid var(--cursor);
    position: relative;
    justify-content: flex-end;
    > div {
      position: absolute;
      top: 0;
      left: 0;
      width: 100%;
      height: 100%;
      transform-origin: left;
      background: var(--cursor);
    }
  }
}
</style>
