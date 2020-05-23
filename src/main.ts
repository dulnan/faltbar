import './assets/fonts.scss'

import Vue from 'vue'

import FIcon from './components/global/Icon.vue'
import FProgress from './components/global/Progress.vue'
import CPU from './components/plugins/CPU/index.vue'
import FocusedWindow from './components/plugins/FocusedWindow/index.vue'
import Launcher from './components/plugins/Launcher/index.vue'
import Memory from './components/plugins/Memory/index.vue'
import NetworkManager from './components/plugins/NetworkManager/index.vue'
import Spotify from './components/plugins/Spotify/index.vue'
import Temperature from './components/plugins/Temperature/index.vue'
import DateTime from './components/plugins/Time/index.vue'
import Workspaces from './components/plugins/Workspaces/index.vue'
import Faltbar from './Faltbar.vue'
import state from './plugins/state'
import socket from './service/socket'
import store from './store'
import {faltbarMonitors} from './webkit.js'

Vue.config.productionTip = false
Vue.component('f-icon', FIcon)
Vue.component('f-progress', FProgress)

Vue.use(state)

const bars = [
  {
    name: 'top',
    gravity: 'top-left',
    display: 'DP-2.3',
    modules: [FocusedWindow, Spotify, Memory, CPU, Temperature, NetworkManager, DateTime]
  },
  {name: 'left-bottom', gravity: 'bottom-left', display: 'DP-0', modules: [Workspaces]},
  {name: 'middle-bottom', gravity: 'bottom-left', display: 'DP-2.3', modules: [Workspaces]},
  {name: 'right-bottom', gravity: 'bottom-left', display: 'DP-2.2', modules: [Workspaces]},
  {name: 'oled-bottom', gravity: 'bottom-left', display: 'DP-1', modules: [Workspaces]}
]

socket.connect().then(() => {
  Vue.prototype.$socket = socket

  const RootApp = Vue.extend(Faltbar)
  new RootApp({
    propsData: {
      bars,
      displays: faltbarMonitors
    },
    store
  }).$mount('#app')
})
