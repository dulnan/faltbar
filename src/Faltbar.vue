<template>
  <div class="faltbar" :style="style">
    <div class="faltbar-displays">
      <div
        v-for="display in visibleDisplays"
        class="faltbar-display"
        :key="display.name"
        :style="getDisplayStyle(display)"
      >
        <bar
          v-for="bar in display.bars"
          :key="bar.name"
          :name="bar.name"
          :modules="bar.modules"
          :gravity="bar.gravity"
          :base-size="bar.baseSize"
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
import './themes/layout/wendis_2000/index.scss'

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

  data() {
    return {
      observer: null,
      timeout: null
    }
  },

  provide: function() {
    return {
      observer: new ResizeObserver(this.onObserverNotify.bind(this))
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

  methods: {
    onObserverNotify(entries) {
      // clearTimeout(this.timeout)
      const rects = this.getRects()
      webkit.messageHandlers.faltbar_bar.postMessage(rects)

      // this.timeout = setTimeout(() => {
      //
      // }, 1000)
    },

    getRects() {
      const elements = this.$el.querySelectorAll('[data-faltbar-window]')
      return Array.from(elements).map((el) => {
        const { x, y, width, height } = el.getBoundingClientRect()
        const windowType = el.dataset.faltbarWindow === 'dock' ? 1 : 0
        return [windowType, x, y, width, height].map((v) => Math.round(v))
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
body {
  padding: 0;
  margin: 0;
  cursor: default;
  font-weight: normal;
  height: 100vh;
}

a {
  cursor: pointer;
}

:root {
  --border: rgba(255, 255, 255, 0.08);
}

.faltbar {
  font-family: sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: var(--foreground);
  background: var(--background);
  height: 100%;
  background: black;
}

* {
  box-sizing: border-box;
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
  width: 100%;
}

.faltbar-display {
  position: absolute;
  box-shadow: 0 0 0 1px black;
}
</style>
