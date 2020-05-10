<template>
  <div class="pill is-progress">
    <div :style="style"></div>
    <span>{{ label }}</span>
  </div>
</template>

<script>
export default {
  name: 'Progress',

  props: {
    value: {
      type: Number,
      default: 0
    },
    max: {
      type: Number,
      default: 1
    },
    label: {
      type: String,
      default: ''
    }
  },

  computed: {
    style() {
      return {
        transform: `scaleX(${this.value / this.max})`
      }
    }
  }
}
</script>

<style scoped lang="scss"></style>
