<template>
  <div class="faltbar" :style="style">
    <div class="faltbar-displays">
      <div
        v-for="display in visibleDisplays"
        class="faltbar-display"
        :key="display.name"
        :style="getDisplayStyle(display)"
        @click="emitRects"
      >
        <bar
          v-for="bar in display.bars"
          :key="bar.name"
          :name="bar.name"
          :modules="bar.modules"
          :gravity="bar.gravity"
          :output="display.name"
          ref="bars"
        />
      </div>
    </div>
  </div>
</template>

<script>
import Vue from 'vue'
import Bar from './components/app/Bar.vue'
import { mapState } from 'vuex'
import { webkit } from './webkit'

export default Vue.extend({
  name: 'Faltbar',

  components: {
    Bar
  },

  props: {
    bars: {
      type: Array,
      default: () => {
        return []
      }
    },
    displays: {
      type: Array,
      default: () => []
    }
  },

  mounted() {
    this.$socket.on('subscribed', (data) => {
      this.$store.dispatch('socket/register', data.data)
    })
    this.$socket.on('show', ({ data, namespace }) => {
      if (namespace === 'faltbar') {
        this.$store.commit('setLauncherVisible', true)
      }
    })
    this.$socket.on('update', ({ data, namespace }) => {
      if (this.$store.state.socket[namespace]) {
        this.$store.commit(`socket/${namespace}/update`, data)
      }
    })
  },

  // mounted() {
  //   Socket.on('init_namespace', this.init.bind(this))
  //   Socket.on('update', this.onUpdate.bind(this))
  //
  //   // const modules = Object.keys(this.barsSetting)
  //   //   .map((key) => this.barsSetting[key])
  //   //   .flat()
  //   //
  //   // const namespaces = [
  //   //   ...new Set(modules.map((m) => (m.faltbar || {}).namespaces).flat())
  //   // ]
  //   // namespaces.filter(Boolean).forEach((namespace) => {
  //   //   Socket.send('falter', 'subscribe', namespace)
  //   // })
  // },

  methods: {
    emitRects() {
      const rects = this.getRects()
      webkit.messageHandlers.faltbar_bar.postMessage(rects)
    },
    getRects() {
      return this.$refs.bars.map((bar) => {
        const { x, y, width, height } = bar.$el.getBoundingClientRect()
        return [x, y, width, height]
      })
    },

    getDisplayStyle({ x, y, w, h }) {
      return {
        width: w + 'px',
        height: h + 'px',
        left: x + 'px',
        top: y + 'px'
      }
    },

    buildColor(obj) {
      return Object.keys(obj).reduce((acc, name) => {
        acc.push({ name, value: obj[name] })
        return acc
      }, [])
    }

    // onUpdate({ namespace, data }) {
    //   this.$store.commit(`socket/${namespace}/update`, data)
    // },
  },

  computed: {
    ...mapState(['theme']),

    displayMap() {
      return this.displays.reduce((acc, display) => {
        acc[display.name] = display
        return acc
      }, {})
    },

    visibleDisplays() {
      return this.displays
        .map((display) => {
          const bars = this.bars.filter((bar) => bar.display === display.name)

          return { ...display, bars }
        })
        .filter((display) => display.bars.length)
    },

    style() {
      return Object.keys(this.theme)
        .reduce((acc, key) => {
          const colors = this.buildColor(this.theme[key])
          acc.push(...colors)
          return acc
        }, [])
        .reduce((acc, color) => {
          acc['--' + color.name] = color.value
          return acc
        }, {})
    }
  }
})
</script>

<style lang="scss">
html {
}
body {
  padding: 0;
  margin: 0;
  /* user-select: none; */
  cursor: default;
  text-transform: uppercase;
  font-weight: normal;
  letter-spacing: 0.15em;
  font-size: 12px;
  height: 100vh;
  /* background: rgba(0, 0, 255, 0); */
  /* background: rgba(black, 0); */
}
a {
  cursor: pointer;
}
:root {
  --border: rgba(255, 255, 255, 0.08);
}
.faltbar {
  font-family: 'DIN', Kayak, Inter, Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: var(--foreground);
  background: var(--background);
  background: #ff0000;
  height: 100%;
}

* {
  box-sizing: border-box;
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

.faltbar-module-focusedwindow {
  margin-right: auto;
}

.faltbar-container {
  height: 100%;
  display: flex;
  flex-direction: column;
}

.faltbar-bar {
  overflow: hidden;
  height: 32px;
  width: 100%;
}

.faltbar-bar-top {
  border-bottom: 1px solid var(--border);
  z-index: 1000;
  flex: 0 0 32px;
}

.faltbar-bar-center {
  flex: 1;
}
.faltbar-bar-bottom {
  border-top: 1px solid var(--border);
  flex: 0 0 32px;
}

#test {
  position: fixed;
  z-index: 100000;
  background: blue;
  width: 40px;
  height: 32px;
  bottom: 120px;
  left: 0;
}

.faltbar-display {
  position: absolute;
  box-shadow: 0 0 0 1px black;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 3rem;
  font-weight: bold;
}
</style>
