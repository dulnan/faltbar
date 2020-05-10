import Vue from 'vue'
import Faltbar from './Faltbar.vue'
import Icon from './components/Icon.vue'
import store from './store'
import socket from './service/socket'
import state from './plugins/state'

import NetworkManager from './components/NetworkManager.vue'
import Workspaces from './components/Workspaces.vue'
// import Spotify from './components/Spotify.vue'
import Memory from './components/Memory.vue'
import DateTime from './components/Time.vue'
import FocusedWindow from './components/FocusedWindow.vue'
import CPU from './components/CPU.vue'
import Temperature from './components/Temperature.vue'
import './assets/fonts.scss'

Vue.config.productionTip = false
Vue.component('icon', Icon)

Vue.use(state)

const barsSetting = {
  top: [
    FocusedWindow,
    // Spotify,
    Memory,
    CPU,
    Temperature,
    NetworkManager,
    DateTime
  ],
  bottom: [Workspaces]
}

socket.connect().then(() => {
  Vue.prototype.$socket = socket

  const RootApp = Vue.extend(Faltbar)
  new RootApp({
    propsData: {
      barsSetting
    },
    store
  }).$mount('#app')
})
