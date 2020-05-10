import Vue from 'vue'
import Faltbar from './Faltbar.vue'
import store from './store'
import socket from './service/socket'
import state from './plugins/state'

import NetworkManager from './components/plugins/NetworkManager/index.vue'
import Workspaces from './components/plugins/Workspaces/index.vue'
// import Spotify from './components/Spotify.vue'
import Memory from './components/plugins/Memory/index.vue'
import DateTime from './components/plugins/Time/index.vue'
import FocusedWindow from './components/plugins/FocusedWindow/index.vue'
import CPU from './components/plugins/CPU/index.vue'
import Temperature from './components/plugins/Temperature/index.vue'
import './assets/fonts.scss'

import FIcon from './components/global/Icon.vue'
import FProgress from './components/global/Progress.vue'

Vue.config.productionTip = false
Vue.component('f-icon', FIcon)
Vue.component('f-progress', FProgress)

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
