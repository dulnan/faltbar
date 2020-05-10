<template>
  <div class="networkmanager-connection" v-if="type">
    <div class="type pill" :class="'is-' + type">
      <span>{{ type }}</span>
    </div>
    <div class="label">{{ label }}</div>
  </div>
</template>

<script>
const TYPE = {
  WIFI: 'wifi',
  VPN: 'vpn'
}

export default {
  name: 'NetworkManagerConnection',

  props: {
    connection: {
      type: Object,
      default: () => {
        return {}
      }
    },
    accessPoint: {
      type: Object,
      default: () => {
        return {}
      }
    },
    devices: {
      type: Array,
      default: () => {
        return []
      }
    }
  },

  methods: {},

  computed: {
    type() {
      if (this.connection.type === 'vpn') {
        return TYPE.VPN
      } else if (this.connection.type.includes('wireless')) {
        return TYPE.WIFI
      }

      return ''
    },

    label() {
      if (this.type === TYPE.WIFI) {
        return this.accessPoint.ssid
      }

      return this.connection.id
    }
  }
}
</script>

<style scoped lang="scss">
.networkmanager-connection {
  display: flex;
  align-items: center;
  color: var(--cursor);
  .pill {
    padding: 0 0.2em;
    margin-right: 0.5em;
    background: var(--cursor);
    color: black;
  }
  .label {
  }
}
</style>
