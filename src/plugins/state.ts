import { mapState } from 'vuex'
import Vue, { ComponentOptions } from 'vue'
import {
  FaltbarVue,
  FaltbarComponentOptions,
  FaltbarOptions
} from './../global.d'

interface NamespaceProperty {
  [key: string]: string
}

function hasOptions(options: FaltbarComponentOptions) {
  return options.faltbar && typeof options.faltbar === 'object'
}

function addComputed(
  component: Vue,
  namespace: string,
  properties: Record<string, string>
) {
  const mapped = Object.keys(properties).reduce<Record<string, Function>>(
    (acc, local) => {
      const store = properties[local]
      acc[local] = (state) => state[store]
      return acc
    },
    {}
  )
  component.$options.computed = {
    ...(component.$options.computed || {}),
    ...mapState('socket/' + namespace, mapped)
  }
}

function getAllProperties(component: Vue, namespace: string) {
  return Object.keys(component.$store.state.socket[namespace]).reduce<
    NamespaceProperty
  >((acc, store) => {
    acc[store] = store
    return acc
  }, {})
}

function getSomeProperties(
  properties: Array<string> | NamespaceProperty | Array<NamespaceProperty>
): NamespaceProperty {
  if (Array.isArray(properties)) {
    return properties.reduce<NamespaceProperty>((acc, property) => {
      acc[property] = property
      return acc
    }, {})
  }

  return properties
}

function attach(component: FaltbarVue) {
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
