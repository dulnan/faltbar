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
  name: 'FocusedWindow',

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
  margin-right: auto;
  font-weight: 500;
  overflow: hidden;
  min-width: 0;
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
}
</style>
