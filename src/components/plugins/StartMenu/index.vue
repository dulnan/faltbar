<template>
  <div class="start-menu" data-faltbar-window="popup">
    <div class="start-menu-trigger">
      <div
        class="start-menu-button"
        @click="isVisible = !isVisible"
        :class="{ 'is-focused': isVisible }"
      >
        <div class="start-menu-button-icon"></div>
        <div class="start-menu-button-text">Start</div>
      </div>
    </div>
    <f-dropdown v-if="isVisible" :items="menu" align="bottom" />
  </div>
</template>

<script>
export default {
  name: 'StartMenu',

  inject: ['observer'],

  components: {},

  data() {
    return {
      isVisible: true,
      menu: [
        {
          label: 'Linux Update',
          icon: 'update',
          action: 'update',
          children: []
        },
        {
          separator: true
        },
        {
          label: 'Programs',
          icon: 'programs',
          action: '',
          children: [
            {
              label: 'Applications',
              icon: 'folder',
              children: []
            },
            {
              label: 'System',
              icon: 'folder',
              children: []
            },
            {
              label: 'Multimedia',
              icon: 'folder',
              children: []
            },
            {
              label: 'Multimedia',
              icon: 'folder',
              children: []
            }
          ]
        },
        {
          label: 'Documents',
          icon: 'documents',
          action: 'documents',
          children: []
        },
        {
          label: 'Settings',
          icon: 'settings',
          action: 'settings',
          children: []
        },
        {
          label: 'Search',
          icon: 'search',
          action: 'search',
          children: []
        },
        {
          label: 'Help',
          icon: 'help',
          action: 'help',
          children: []
        },
        {
          label: 'Run...',
          icon: 'run',
          action: 'run',
          children: []
        },
        {
          separator: true
        },
        {
          label: 'Shut Down...',
          icon: 'shutdown',
          action: 'shut_down',
          children: []
        }
      ]
    }
  },

  mounted() {
    this.observer.observe(this.$el)
  },

  destroy() {
    this.observer.unobserve(this.$el)
  },

  methods: {}
}
</script>

<style lang="scss">
.start-menu {
  position: relative;
}

.start-menu-button {
  display: flex;
  align-items: center;
}
</style>
