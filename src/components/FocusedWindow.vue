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
  position: absolute;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  display: flex;
  align-items: center;
  justify-content: center;
  font-weight: bold;
}
</style>
