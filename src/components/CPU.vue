<template>
  <div class="cpu">
    <progress-bar :value="current" :max="100" :label="label" />
  </div>
</template>

<script>
import Socket from '@/service/socket'
import ProgressBar from '@/components/Progress.vue'

export default {
  name: 'CPU',

  components: {
    ProgressBar
  },

  data() {
    return {
      readings: new Array(10).fill(0),
      prev: {}
    }
  },

  computed: {
    current() {
      return this.readings[this.readings.length - 1]
    },

    label() {
      return Math.round(this.current) + '%'
    }
  },

  mounted() {
    Socket.on('cpu_update', (cpu) => {
      if (!this.prev.active) {
        this.prev = this.calculate(cpu)
        return
      }

      const current = this.calculate(cpu)
      const percentage = this.getPercentage(this.prev, current)
      this.prev = current
      this.readings = [...this.readings.slice(1), percentage]
    })
  },

  methods: {
    calculate({ user, system, nice, softirq, steal, idle, iowait }) {
      const active = user + system + nice + softirq + steal
      const total = active + idle + iowait

      return { active, total }
    },

    getPercentage(prev, current) {
      return (
        ((current.active - prev.active) / (current.total - prev.total)) * 100
      )
    }
  }
}
</script>

<style scoped lang="scss">
.cpu {
}
</style>
