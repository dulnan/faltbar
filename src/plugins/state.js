import { mapState } from 'vuex'

function hasOptions(options) {
  return options.faltbar && typeof options.faltbar === 'object'
}

function addComputed(component, namespace, properties) {
  const mapped = Object.keys(properties).reduce((acc, local) => {
    const store = properties[local]
    acc[local] = (state) => state[store]
    return acc
  }, {})
  component.$options.computed = {
    ...(component.$options.computed || {}),
    ...mapState('socket/' + namespace, mapped)
  }
}

function getAllProperties(component, namespace) {
  return Object.keys(component.$store.state.socket[namespace]).reduce(
    (acc, store) => {
      acc[store] = store
      return acc
    },
    {}
  )
}

function getSomeProperties(properties) {
  if (Array.isArray(properties)) {
    return properties.reduce((acc, property) => {
      acc[property] = property
      return acc
    }, {})
  }

  return properties
}

function attach(component) {
  const namespaces = component.$options.faltbar.namespaces || {}

  Object.keys(namespaces).forEach((namespace) => {
    const properties =
      namespaces[namespace] === true
        ? getAllProperties(component, namespace)
        : getSomeProperties(namespaces[namespace])

    addComputed(component, namespace, properties)
  })
}

const plugin = {
  install(Vue) {
    Vue.mixin({
      beforeCreate: function() {
        if (hasOptions(this.$options)) {
          attach(this)
        }
      },

      beforeDestroy: function() {
        if (hasOptions(this.$options)) {
          console.log('destroy')
        }
      },

      methods: {
        send(namespace, event, data) {
          this.$socket.send(namespace, event, data)
        }
      }
    })
  }
}

export default plugin
