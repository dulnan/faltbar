<template>
  <div class="faltbar-bar" :class="'faltbar-bar-' + name">
    <div class="faltbar-bar-container">
      <module
        v-for="module in modules"
        :key="module.name"
        :name="module.name"
        :settings="module.faltbar"
        :module="module"
      >
      </module>
    </div>
  </div>
</template>

<script>
import Module from '@/components/Module.vue'

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
    modules: {
      type: Array,
      default: () => {
        return []
      }
    }
  }
}
</script>

<style lang="scss">
.faltbar-bar {
  flex: 1;
}

.faltbar-bar-container {
  display: flex;
  height: 100%;
}
</style>
