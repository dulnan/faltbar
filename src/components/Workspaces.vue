<template>
  <div class="workspaces">
    <workspace
      v-for="workspace in workspaces"
      :key="workspace.id"
      :is-focused="workspace.focused"
      :is-visible="workspace.visible"
      :is-urgent="workspace.urgent"
      :num="workspace.num"
      :name="workspace.name"
      :windows="workspace.windows"
    />
  </div>
</template>

<script>
import Workspace from '@/components/Workspace.vue'
import Socket from '@/service/socket'

export default {
  name: 'Workspaces',
  components: {
    Workspace
  },
  data() {
    return {
      workspaces: []
    }
  },

  mounted() {
    Socket.on('i3_update', (workspaces) => {
      this.workspaces = workspaces
    })
  },

  methods: {
    onClick(id) {
      Socket.send('i3_switch', id)
    }
  }
}
</script>

<style scoped lang="scss">
.workspaces {
  display: flex;
  height: 100%;
  align-items: center;
  width: 100%;
}
</style>
