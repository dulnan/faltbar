<template>
  <div class="temperature">
    <f-progress :value="average" :max="100" :label="label" />
  </div>
</template>

<script>
export default {
  name: 'Temperature',

  faltbar: {
    namespaces: {
      temperature: {
        cpu: 'x86_pkg_temp'
      }
    }
  },

  data() {
    return {
      sensors: []
    }
  },

  computed: {
    average() {
      return this.cpu / 1000
    },

    label() {
      return Math.round(this.average) + '°C'
    }
  }
}
</script>

<style scoped lang="scss">
.temperature {
}
</style>
