<template>
  <div class="dashboard">
    <div class="dashboard-workspaces">
      <div
        v-for="workspace in workspaces"
        :key="workspace.id"
        class="dashboard-workspace"
        :style="getStyle(workspace.rect)"
      >
        <div class="windows" :style="getContainerStyle(workspace.rect)">
          <div
            v-for="window in workspace.windows"
            :key="window.id"
            class="window"
            :style="getWindowStyle(window.rect, workspace.rect)"
          >
            <div class="icon">
              <i :class="getIcon(window.properties.instance)" />
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import Socket from '@/service/socket'
import { mapState } from 'vuex'

export default {
  name: 'Dashboard',
  data() {
    return {
      id: '',
      workspaces: []
    }
  },

  computed: {
    ...mapState(['iconMapping'])
  },

  mounted() {
    Socket.on('i3_update', (workspaces) => {
      this.workspaces = workspaces
    })
    Socket.on('i3_focus', (data) => {
      this.focused = data.id
    })
  },

  methods: {
    getIcon(instance) {
      return this.iconMapping[instance]
    },
    getStyle(rect) {
      return {
        width: rect.width / 100 + 'em',
        height: rect.height / 100 + 'em'
      }
    },
    getContainerStyle(rect) {
      return {
        width: rect.width / 100 + 'em',
        height: (rect.height - rect.y) / 100 + 'em',
        top: rect.y / 100 + 'em'
      }
    },
    getWindowStyle(rect, workspaceRect) {
      return {
        width: rect.width / 100 + 'em',
        height: rect.height / 100 + 'em',
        top: (rect.y - 2 * workspaceRect.y) / 100 + 'em',
        left: rect.x / 100 + 'em'
      }
    }
  }
}
</script>

<style scoped lang="scss">
.dashboard {
  font-weight: bold;
  margin-right: auto;
  position: absolute;
  top: 64px;
  left: 0;
  width: 100%;
  bottom: 0;
  background: var(--background);
}

.dashboard-workspaces {
  font-size: 0.5rem;
  display: flex;
  flex-wrap: wrap;
  .windows {
    position: absolute;
    width: 100%;
    .window {
      position: absolute;
      border: 0.5px solid var(--cursor);
      display: flex;
      align-items: center;
      justify-content: center;

      .icon {
        font-size: 4em;
      }
    }
  }
}
.dashboard-workspace {
  border: 0.5px solid var(--cursor);
  margin: 1em;
  position: relative;
}
</style>
