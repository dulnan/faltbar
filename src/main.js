import Vue from 'vue'
import Faltbar from './Faltbar.vue'
import Icon from './components/Icon.vue'
import Module from './components/Module.vue'
import store from './store'

import NetworkManager from './components/NetworkManager.vue'
import Workspaces from './components/Workspaces.vue'
import Spotify from './components/Spotify.vue'
import Memory from './components/Memory.vue'
import DateTime from './components/Time.vue'
import FocusedWindow from './components/FocusedWindow.vue'
import CPU from './components/CPU.vue'
import Temperature from './components/Temperature.vue'
import './assets/fonts.scss'

Vue.config.productionTip = false
Vue.component('icon', Icon)
Vue.component('module', Module)

const RootApp = Vue.extend(Faltbar)
new RootApp({
  propsData: {
    barsSetting: {
      top: [
        FocusedWindow,
        Spotify,
        Memory,
        CPU,
        Temperature,
        NetworkManager,
        DateTime
      ],
      bottom: [Workspaces]
    }
  },
  store
}).$mount('#app')
