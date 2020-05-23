<template>
  <a
    @click="onClick(num)"
    role="button"
    class="workspace"
    :class="{
      'is-focused': isFocused,
      'is-visible': isVisible,
      'is-urgent': isUrgent
    }"
  >
    <div class="name">
      <span>{{ name }}</span>
    </div>
    <div class="windows">
      <workspace-window
        v-for="window in grouped"
        :key="window.index"
        :instance="window.instance"
        :titles="window.titles"
      />
    </div>
  </a>
</template>

<script>
import Socket from '@/service/socket'
import WorkspaceWindow from './window.vue'

export default {
  name: 'Workspace',
  components: {
    WorkspaceWindow
  },
  props: {
    name: {
      type: String,
      default: ''
    },
    num: {
      type: Number,
      default: 0
    },
    isFocused: {
      type: Boolean,
      default: false
    },
    isVisible: {
      type: Boolean,
      default: false
    },
    isUrgent: {
      type: Boolean,
      default: false
    },
    windows: {
      type: Array,
      default: () => []
    }
  },

  methods: {
    onClick(id) {
      this.send('wm', 'switch', id)
    }
  },

  computed: {
    grouped() {
      const grouped = this.windows.reduce((acc, w, index) => {
        if (!acc[w.properties.instance]) {
          acc[w.properties.instance] = {
            instance: w.properties.instance,
            index,
            titles: []
          }
        }
        acc[w.properties.instance].titles.push(w.properties.title)
        return acc
      }, {})

      return Object.keys(grouped).map((key) => grouped[key])
    }
  }
}
</script>

<style lang="scss">
.workspace {
  display: flex;
  align-items: center;
  flex: 1;
  padding: 0 0.5em;
  overflow: hidden;
  min-width: 0;

  .windows {
    display: flex;
    overflow: hidden;
    flex: 1;
  }

  &.is-focused {
    // Workspace is focused.
  }

  &.is-urgent {
    // Workspace has urgent state.
  }

  &.is-visible {
    // Workspace is visible.
  }
}
</style>
