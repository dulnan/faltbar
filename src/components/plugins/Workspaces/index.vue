<template>
  <div class="workspaces">
    <workspace
      v-for="workspace in workspacesFiltered"
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
import Workspace from './item.vue'

export default {
  name: 'Workspaces',

  props: {
    output: {
      type: String,
      default: ''
    }
  },

  faltbar: {
    namespaces: {
      wm: ['workspaces']
    }
  },

  components: {
    Workspace
  },

  methods: {
    onClick(id) {
      this.$socket.send('wm', 'switch', id)
    }
  },

  computed: {
    workspacesFiltered() {
      return this.workspaces.filter((w) => w.output === this.output)
    }
  }
}
</script>

<style lang="scss">
.workspaces {
  display: flex;
  height: 100%;
  align-items: center;
  width: 100%;
}
</style>
