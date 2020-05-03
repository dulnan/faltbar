<template>
  <div class="focused-window">
    <span>{{ className }}</span>
    <span> - </span>
    <span>{{ title }}</span>
  </div>
</template>

<script>
import Socket from '@/service/socket'

export default {
  name: 'Workspaces',
  data() {
    return {
      className: '',
      instance: '',
      title: ''
    }
  },

  mounted() {
    Socket.on('i3_focus', (data) => {
      this.className = data.class
      this.instance = data.instance
      this.title = data.title
    })
  }
}
</script>

<style scoped lang="scss">
.focused-window {
  font-weight: bold;
  margin-right: auto;
}
</style>
