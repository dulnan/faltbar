<template>
  <div class="faltbar-module" :class="'faltbar-module-' + name.toLowerCase()">
    <div v-if="icon" class="faltbar-module-icon">
      <icon :icon="icon" />
    </div>
    <div class="faltbar-module-content">
      <slot></slot>
    </div>
  </div>
</template>

<script>
import { mapState } from 'vuex'

export default {
  name: 'Module',

  props: {
    name: {
      type: String,
      required: true
    },
    settings: {
      type: Object,
      default: () => {
        return {}
      }
    }
  },

  computed: {
    ...mapState(['iconFont']),
    icon() {
      const icon = this.settings.icon || {}

      if (icon[this.iconFont]) {
        return icon[this.iconFont]
      }

      return ''
    }
  }
}
</script>

<style lang="scss">
.faltbar-module {
  display: flex;
  align-items: center;
  padding: 0 0.5em;

  &:first-child:last-child {
    flex: 0 0 100%;
  }
}

.faltbar-module-content {
  height: 100%;
  flex: 1;
  display: flex;
  align-items: center;
}
</style>
