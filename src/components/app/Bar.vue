<template>
  <div class="faltbar-bar" :class="'faltbar-bar-' + name" :style="style">
    <div class="faltbar-bar-container">
      <module
        v-for="module in modules"
        :key="module.name"
        :name="module.name"
        :settings="module.faltbar"
        :module="module"
        :output="output"
      >
      </module>
    </div>
  </div>
</template>

<script>
import Module from '@/components/app/Module.vue'

export default {
  name: 'Bar',

  components: {
    Module
  },

  props: {
    name: {
      type: String,
      required: true
    },
    output: {
      type: String,
      required: true
    },
    modules: {
      type: Array,
      default: () => {
        return []
      }
    },
    gravity: {
      type: String,
      default: 'top-left'
    },
    fontSize: {}
  },

  methods: {
    emit(msg) {
      window.webkit.messageHandlers.faltbar.postMessage(msg)
      // window.CustomClass.notify('Sending this from string from Javascript To C')
    }
  },

  computed: {
    style() {
      return this.gravity.split('-').reduce((style, direction) => {
        style[direction] = '0'
        return style
      }, {})
    }
  }
}
</script>

<style lang="scss">
.faltbar-bar {
  position: absolute;
  background: var(--background);
}

.faltbar-bar-container {
  display: flex;
  font-size: 10px;
  height: 100%;
}
</style>
