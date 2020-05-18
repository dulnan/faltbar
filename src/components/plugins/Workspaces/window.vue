<template>
  <div class="workspace-window">
    <f-icon v-if="icon" :icon="icon" />
    <span v-else class="label">{{ instance }}</span>
    <span class="title">{{ mappedTitles.join(', ') }}</span>
  </div>
</template>

<script>
import { mapState } from 'vuex'

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
    ...mapState(['iconMapping']),
    icon() {
      return this.iconMapping[this.instance] || ''
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
    margin-top: -0.15em;
    position: relative;
    z-index: 0;
    font-size: 1.25em;
  }

  .label {
    text-transform: uppercase;
    position: relative;
    z-index: 3;
  }

  .title {
    min-width: 0;
    white-space: nowrap;
    overflow: hidden;
    text-overflow: ellipsis;
  }
}
</style>
