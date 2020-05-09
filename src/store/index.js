import Vue from 'vue'
import Vuex from 'vuex'

Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    iconMapping: {
      Alacritty: 'fas fa-dollar-sign',
      Navigator: 'fab fa-firefox',
      chromium: 'fab fa-chrome',
      gitkraken: 'fab fa-code-branch',
      DBeaver: 'fab fa-database',
      spotify: 'fab fa-spotify',
      slack: 'fab fa-slack-hash',
      'telegram-desktop': 'fab fa-telegram-plane',
      nemo: 'fab fa-folder-open'
    }
  },
  mutations: {},
  actions: {},
  modules: {}
})
