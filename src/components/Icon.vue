<template>
  <div class="icon">
    <span :class="icon"></span>
  </div>
</template>

<script>
export default {
  name: 'Icon',

  props: {
    icon: {
      type: String,
      required: true
    }
  }
}
</script>

<style lang="scss">
.icon {
  line-height: 1;

  > i {
    vertical-align: middle;
  }
}
</style>
