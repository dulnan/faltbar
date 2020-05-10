<template>
  <div
    class="faltbar-module"
    :class="'faltbar-module-' + name.toLowerCase()"
    v-if="isReady"
  >
    <div v-if="icon" class="faltbar-module-icon">
      <f-icon :icon="icon" />
    </div>
    <div class="faltbar-module-content">
      <component :is="module" />
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
    module: {
      type: Object,
      required: true
    },
    settings: {
      type: Object,
      default: () => {
        return {
          namespaces: []
        }
      }
    }
  },

  computed: {
    ...mapState(['iconFont']),

    isReady() {
      return this.namespaces.every((namespace) => {
        return !!this.$store.state.socket[namespace]
      })
    },

    namespaces() {
      return Object.keys((this.module.faltbar || {}).namespaces || {})
    },

    icon() {
      const icon = this.settings.icon || {}

      if (icon[this.iconFont]) {
        return icon[this.iconFont]
      }

      return ''
    }
  },

  mounted() {
    this.namespaces.forEach((namespace) => {
      this.$store.dispatch('socket/subscribe', namespace)
    })
  },

  beforeDestroy() {
    this.namespaces.forEach((namespace) => {
      this.$store.commit('socket/decrement', namespace)
    })
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
