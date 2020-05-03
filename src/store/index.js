import Vue from 'vue'
import Vuex from 'vuex'

Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    iconMapping: {
      Alacritty: 'fas fa-greater-than',
      Navigator: 'fab fa-firefox',
      chromium: 'fab fa-chrome',
      gitkraken: 'fab fa-git',
      spotify: 'fab fa-spotify',
      slack: 'fab fa-slack-hash'
    }
  },
  mutations: {},
  actions: {},
  modules: {}
})
