import Vue, {ComponentOptions, VueConstructor} from 'vue'

export interface FaltbarOptions {
  namespaces: Record<string, string|boolean|Array<string>|Record<string, string>>
}

export interface FaltbarComponentOptions extends ComponentOptions<Vue> {
  faltbar: FaltbarOptions
}

export interface FaltbarVue extends Vue {
  $options: FaltbarComponentOptions
}

export interface FaltbarVueConstructor extends VueConstructor {
  $options: FaltbarComponentOptions
}
