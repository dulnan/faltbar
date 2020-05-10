<template>
  <div class="networkmanager">
    <connection
      v-for="connection in connections"
      :key="connection.connection.uuid"
      :connection="connection.connection"
      :devices="connection.devices"
      :access-point="connection.accessPoint"
    />
  </div>
</template>

<script>
import Connection from './item.vue'

export default {
  name: 'NetworkManager',

  faltbar: {
    namespaces: {
      networkmanager: ['connections']
    }
  },

  components: {
    Connection
  }
}
</script>

<style scoped lang="scss">
.networkmanager {
  display: flex;
  flex: 0 0 auto;
}
</style>
