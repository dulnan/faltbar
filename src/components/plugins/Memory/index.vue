<template>
  <div class="memory">
    <f-progress :value="used" :max="total" :label="usedGB" />
  </div>
</template>

<script>
export default {
  name: 'Memory',

  faltbar: {
    namespaces: {
      memory: {
        total: 'MemTotal',
        free: 'MemFree'
      }
    }
  },

  computed: {
    used() {
      return this.total - this.free
    },

    usedGB() {
      return Math.round((this.used / 1024 / 1024) * 10) / 10 + ' GB'
    }
  },

  methods: {
    onClick(id) {
      this.$socket.send('i3_switch', id)
    }
  }
}
</script>

<style scoped lang="scss">
.memory {
  display: flex;

  .pill {
    > div {
    }
  }
}
</style>
