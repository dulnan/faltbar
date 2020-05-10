<template>
  <div class="networkmanager">
    <network-manager-connection
      v-for="connection in connections"
      :key="connection.connection.uuid"
      :connection="connection.connection"
      :devices="connection.devices"
      :access-point="connection.accessPoint"
    />
  </div>
</template>

<script>
import NetworkManagerConnection from '@/components/NetworkManagerConnection.vue'

export default {
  name: 'NetworkManager',

  faltbar: {
    namespaces: {
      networkmanager: ['connections']
    }
  },

  components: {
    NetworkManagerConnection
  }
}
</script>

<style scoped lang="scss">
.networkmanager {
  display: flex;
  flex: 0 0 auto;
}
</style>
