<template>
  <div class="memory">
    <progress-bar :value="used" :max="total" :label="usedGB" />
  </div>
</template>

<script>
import ProgressBar from '@/components/Progress.vue'

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

  components: {
    ProgressBar
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
