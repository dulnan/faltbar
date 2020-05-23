<template>
  <div class="datetime">
    {{ time }}
  </div>
</template>

<script>
export default {
  name: 'Time',
  data() {
    return {
      time: '16:08',
      interval: null
    }
  },

  mounted() {
    clearInterval(this.interval)
    this.interval = window.setInterval(() => {
      const now = new Date()
      this.time = now.toLocaleTimeString([], {
        hour: '2-digit',
        minute: '2-digit'
      })
    }, 1000)
  },

  destroy() {
    clearInterval(this.interval)
  },

  methods: {}
}
</script>

<style lang="scss">
.datetime {
  font-variant-numeric: tabular-nums;
  -moz-font-feature-settings: 'tnum';
  -webkit-font-feature-settings: 'tnum';
  font-feature-settings: 'tnum';
}
</style>
