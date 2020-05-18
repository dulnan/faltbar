<template>
  <div class="launcher" v-if="launcherVisible">
    <div class="launcher-container">
      <div class="launcher-header">
        <input ref="input" type="text" v-model="search" />
      </div>
      <div class="launcher-body">
        <div class="launcher-results">
          <div
            v-for="result in results"
            :key="result.name + result.id + result.exec"
            class="launcher-results-item"
          >
            {{ result.name }}
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import MiniSearch from 'minisearch'

const miniSearch = new MiniSearch({
  fields: ['categories', 'desc', 'name', 'id', 'keywords', 'exec'], // fields to index for full-text search
  storeFields: ['id', 'desc', 'name', 'exec']
})

import { mapState } from 'vuex'
export default {
  name: 'Launcher',

  faltbar: {
    namespaces: {
      launcher: true
    }
  },

  data() {
    return {
      search: ''
    }
  },

  computed: {
    ...mapState(['launcherVisible']),

    results() {
      return miniSearch.search(this.search, {
        prefix: true,
        boost: { name: 5, desc: 2, keywords: 2, fuzzy: 0.2 }
      })
    }
  },

  watch: {
    launcherVisible(isVisible) {
      if (isVisible) {
        this.search = ''
        window.webkit.messageHandlers.faltbar.postMessage('full')
        this.$nextTick(() => {
          this.$refs.input.focus()
        })
      }
    }
  },

  mounted() {
    document.addEventListener('keyup', this.onKeyUp.bind(this))
    miniSearch.addAll(
      this.applications.map((item) => {
        const copy = {}
        try {
          copy.name = item.name
          copy.desc = item.desc
          copy.exec = item.exec
          copy.id = item.id
          copy.keywords = (item.keywords || []).join(' ')
          copy.categories = (item.categories || []).join(' ')
        } catch (e) {
          console.log(copy)
        }
        return copy
      })
    )
  },

  beforeDestroy() {
    document.removeEventListener('keyup', this.onKeyUp.bind(this))
  },

  methods: {
    onKeyUp(e) {
      if (e.key === 'Escape') {
        window.webkit.messageHandlers.faltbar.postMessage('small')
        this.$store.commit('setLauncherVisible', false)
      }
    }
  }
}
</script>

<style lang="scss">
.faltbar-module-launcher {
  padding: 0;
}
.launcher {
  height: 100%;
  width: 100%;
  input {
    font-size: 3rem;
    appearance: none;
    background: none;
    border: 0;
    outline: none;
    color: var(--foreground);
    font-family: inherit;
    font-weight: bold;
    width: 100%;
    padding: 1rem 0.5rem 1.25rem;
    border-bottom: 1px solid var(--border);
    text-transform: uppercase;
  }
}

.launcher-container {
  width: 100%;
  height: 100%;
}

.launcher-results-item {
  font-size: 1.5rem;
  text-align: left;
  padding: 1rem;
}
</style>
