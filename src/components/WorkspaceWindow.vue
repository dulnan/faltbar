<template>
  <div class="workspace-window">
    <span class="icon" v-if="icon"><i :class="icon"></i></span>
    <span v-else class="label">{{ instance }}</span>
    <span class="title">{{ mappedTitles.join(', ') }}</span>
  </div>
</template>

<script>
const ICONS = {
  Alacritty: 'fas fa-greater-than',
  Navigator: 'fab fa-firefox',
  chromium: 'fab fa-chrome',
  gitkraken: 'fab fa-git',
  spotify: 'fab fa-spotify',
  slack: 'fab fa-slack-hash'
}

export default {
  name: 'WorkspaceWindow',
  props: {
    instance: {
      type: String,
      default: ''
    },
    titles: {
      type: Array,
      default: () => []
    }
  },

  computed: {
    icon() {
      return ICONS[this.instance] || ''
    },

    mappedTitles() {
      return this.titles.map((title) => {
        if (title.includes('npm')) {
          return 'NPM'
        }

        if (title.includes('nvim')) {
          return 'nvim'
        }

        if (this.instance === 'chromium') {
          return title.replace('- Chromium', '')
        }

        if (this.instance === 'spotify') {
          return 'Spotify'
        }

        return title
      })
    }
  }
}
</script>

<style scoped lang="scss">
.workspace-window {
  display: flex;
  align-items: center;
  flex: 1 1 auto;
  overflow: hidden;

  .icon {
    margin-right: 0.25em;
    position: relative;
    z-index: 0;
  }

  .label {
    text-transform: uppercase;
    position: relative;
    z-index: 3;
  }

  .title {
    font-size: 13px;
    min-width: 0;
    white-space: nowrap;
    overflow: hidden;
    text-overflow: ellipsis;
  }
}
</style>
