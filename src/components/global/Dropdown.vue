<template>
  <div class="dropdown" data-faltbar-window="popup" :class="'is-' + align">
    <div class="dropdown-inner">
      <div class="dropdown-list">
        <template v-for="(item, index) in items">
          <div
            v-if="item.separator"
            class="dropdown-list-separator"
            :key="index"
          ></div>
          <div v-else :key="index" class="dropdown-list-item">
            <div
              class="dropdown-list-item-button"
              @click="onClick(item, index)"
            >
              <div class="dropdown-list-item-icon" :class="'is-' + item.icon">
                <span></span>
              </div>
              <div class="dropdown-list-item-label">{{ item.label }}</div>
            </div>
            <f-dropdown
              v-if="
                item.children && item.children.length && childVisible === index
              "
              :items="item.children"
            />
          </div>
        </template>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'Dropdown',

  inject: ['observer'],

  props: {
    align: {
      type: String,
      default: 'left'
    },
    items: {
      type: Array,
      default: () => {
        return []
      }
    }
  },

  data() {
    return {
      childVisible: -1
    }
  },

  mounted() {
    this.observer.observe(this.$el)
  },

  destroy() {
    this.observer.unobserve(this.$el)
  },

  methods: {
    onClick(item, index) {
      let childVisible = -1

      if (item.children && item.children.length) {
        if (this.childVisible !== index) {
          childVisible = index
        }
      }

      this.childVisible = childVisible
    }
  }
}
</script>

<style lang="scss">
.dropdown {
  position: absolute;
  text-align: left;

  &.is-left {
    top: 0;
    left: 100%;
  }
  &.is-right {
    top: 0;
    right: 100%;
  }
  &.is-bottom {
    bottom: 100%;
    left: 0;
  }
  &.is-top {
    top: 100%;
    left: 0;
  }
}

.dropdown-inner {
  height: 100%;
}

.dropdown-list-item-button {
  display: flex;
  align-items: center;
}
</style>
