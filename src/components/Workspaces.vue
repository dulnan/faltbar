<template>
  <!-- <transition&#45;group name="list&#45;complete" tag="div" class="workspaces"> -->
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
  <!-- </transition&#45;group> -->
</template>

<script>
import Workspace from '@/components/Workspace.vue'

export default {
  name: 'Workspaces',

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
.flip-list-move {
  transition: transform 0.2s;
}

.list-complete-item {
  transition: all 1s;
  display: inline-block;
  margin-right: 10px;
}
.list-complete-enter, .list-complete-leave-to
/* .list-complete-leave-active below version 2.1.8 */ {
  /* transform: translateY(100px); */
}
.list-complete-leave-active {
  /* position: absolute; */
}
</style>
