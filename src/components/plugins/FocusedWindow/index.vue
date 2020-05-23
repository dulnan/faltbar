<template>
  <div class="focused-window">
    <span>{{ focused.className }}</span>
    <span> - </span>
    <span>{{ focused.title }}</span>
  </div>
</template>

<script>
export default {
  name: 'FocusedWindow',

  faltbar: {
    namespaces: {
      wm: ['focused']
    }
  }
}
</script>

<style lang="scss">
.focused-window {
  margin-right: auto;
  overflow: hidden;
  min-width: 0;
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
}
</style>
