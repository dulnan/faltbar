import Socket from '@/service/socket'

function buildVuexModule(data) {
  return {
    namespaced: true,
    state: data,
    mutations: {
      update(state, data) {
        Object.keys(data).forEach((key) => {
          state[key] = data[key]
        })
      }
    }
  }
}

export default {
  namespaced: true,
  state: {
    _subscribers: {}
  },
  mutations: {
    increment(state, namespace) {
      state._subscribers[namespace] = (state._subscribers[namespace] || 0) + 1
    },
    decrement(state, namespace) {
      state._subscribers[namespace] = (state._subscribers[namespace] || 1) - 1
    }
  },
  actions: {
    subscribe({ state }, namespace) {
      if (!state._subscribers[namespace]) {
        Socket.send('falter', 'subscribe', namespace)
      }
    },
    register({ commit, state }, { namespace, data }) {
      if (!state._subscribers[namespace]) {
        this.registerModule(['socket', namespace], buildVuexModule(data))
      }

      commit('increment', namespace)
    }
  }
}
