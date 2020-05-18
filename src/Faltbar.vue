<template>
  <div class="faltbar" :style="style">
    <div class="faltbar-container">
      <bar
        v-for="bar in bars"
        :key="bar.name"
        :name="bar.name"
        :modules="bar.modules"
      />
    </div>
  </div>
</template>

<script>
import Vue from 'vue'
import Bar from './components/app/Bar.vue'
import { mapState } from 'vuex'

export default Vue.extend({
  name: 'Faltbar',

  components: {
    Bar
  },

  props: {
    barsSetting: {
      type: Object,
      default: () => {
        return {}
      }
    }
  },

  data() {
    return {}
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

    bars() {
      return Object.keys(this.barsSetting).map((name) => {
        return {
          name,
          modules: this.barsSetting[name]
        }
      })
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
</style>
