<template>
  <div class="dropdown" data-faltbar-window="popup">
    <div class="dropdown-inner">
      <div class="dropdown-aside"></div>
      <div class="dropdown-list"></div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'StartMenuDropdown',

  inject: ['observer'],

  data() {
    return {
      menu: [
        {
          label: '',
          icon: '',
          action: '',
          children: []
        },

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
          icon: 'folder',
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
          id: 'shut-down',
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
.dropdown {
  position: absolute;
  bottom: 100%;
  left: 0;
  height: 32rem;
  width: 10rem;
}

.dropdown-inner {
  height: 100%;
  display: flex;
}
</style>
