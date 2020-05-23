<template>
  <div
    class="faltbar-bar"
    :class="classes"
    :style="style"
    data-faltbar-window="dock"
  >
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

  inject: ['observer'],

  components: {
    Module
  },

  props: {
    name: {
      type: String,
      required: true
    },
    baseSize: {
      type: Number,
      default: 16
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
      return {
        '--px': this.baseSize + 'px'
      }
    },
    gravities() {
      return this.gravity.split('-')
    },

    classes() {
      return [
        ...this.gravities.map((gravity) => {
          return 'is-' + gravity
        }),
        'is-called-' + this.name
      ]
    }
  },

  mounted() {
    this.observer.observe(this.$el)
  },
  beforeDestroy() {
    this.observer.unobserve(this.$el)
  }
}
</script>

<style lang="scss">
.faltbar-bar {
  position: absolute;
  background: var(--background);
  font-size: var(--px);
  height: 2em;

  &.is-bottom {
    bottom: 0;
  }
  &.is-top {
    top: 0;
  }
  &.is-left {
    left: 0;
  }
  &.is-right {
    right: 0;
  }
}

.faltbar-bar-container {
  display: flex;
  height: 100%;
  font-size: 0.75em;
}
</style>
