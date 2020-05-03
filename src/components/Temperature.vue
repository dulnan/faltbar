<template>
  <div class="temperature">
    <progress-bar :value="average" :max="100" :label="label" />
  </div>
</template>

<script>
import Socket from '@/service/socket'
import ProgressBar from '@/components/Progress.vue'

export default {
  name: 'Temperature',

  components: {
    ProgressBar
  },

  data() {
    return {
      sensors: []
    }
  },

  computed: {
    average() {
      return (
        this.sensors.reduce((acc, v) => {
          return acc + v.value / 1000
        }, 0) / this.sensors.length
      )
    },

    label() {
      return Math.round(this.average) + '°C'
    }
  },

  mounted() {
    Socket.on('temperature_update', (temperature) => {
      this.sensors = Object.keys(temperature).map((key) => {
        return { key, value: temperature[key] }
      })
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

<style scoped lang="scss"></style>
