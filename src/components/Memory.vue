<template>
  <div class="memory">
    <progress-bar :value="used" :max="total" :label="usedGB" />
  </div>
</template>

<script>
import Socket from '@/service/socket'
import ProgressBar from '@/components/Progress.vue'

export default {
  name: 'Memory',

  components: {
    ProgressBar
  },

  data() {
    return {
      total: 1,
      free: 1
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

  mounted() {
    Socket.on('memory_update', (memory) => {
      this.total = memory.MemTotal
      this.free = memory.MemFree
    })
  },

  methods: {
    onClick(id) {
      Socket.send('i3_switch', id)
    }
  }
}
</script>

<style scoped lang="scss">
.memory {
  margin-left: auto;
  display: flex;

  .pill {
    > div {
    }
  }
}
</style>
