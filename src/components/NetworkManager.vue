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
import Socket from '@/service/socket'
import NetworkManagerConnection from '@/components/NetworkManagerConnection.vue'

export default {
  name: 'NetworkManager',
  components: {
    NetworkManagerConnection
  },
  data() {
    return {
      connections: []
    }
  },

  mounted() {
    Socket.on('networkmanager_update', (connections) => {
      this.connections = connections
    })
  },

  methods: {}
}
</script>

<style scoped lang="scss">
.networkmanager {
  display: flex;
  flex: 0 0 auto;
}
</style>
