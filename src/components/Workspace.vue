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
import WorkspaceWindow from '@/components/WorkspaceWindow.vue'

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
      Socket.send('i3_switch', id)
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

<style scoped lang="scss">
.workspace {
  height: 100%;
  background: var(--background);
  color: var(--cursor);
  display: flex;
  align-items: center;
  font-weight: bold;
  flex: 1;
  padding: 0 0.5em;
  /* justify-content: space-between; */
  /* transition: 0.3s; */
  min-width: 0;
  /* white-space: nowrap; */
  /* overflow: hidden; */
  /* text-overflow: ellipsis; */

  &:not(:last-child) {
    border-right: 1px solid rgba(white, 0.1);
  }

  .windows {
    display: flex;
    overflow: hidden;
  }

  .name {
    background: rgba(white, 0.04);
    border: 1px solid rgba(white, 0.1);
    color: rgba(white, 0.3);
    padding: 0.05em 0.35em;
    border-radius: 2px;
    margin-right: 0.75em;
    display: flex;
    align-items: center;
    font-weight: 500;
    justify-content: center;
    /* border-right: 1px solid rgba(white, 0.1); */
    > div {
    }
  }

  &:hover {
    background: rgba(white, 0.04);
  }

  &.is-focused {
    color: var(--foreground);
    background: rgba(white, 0.03);
    .name {
      background: var(--foreground);
      color: var(--background);
    }
  }
}
</style>
