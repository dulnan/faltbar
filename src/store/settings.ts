import store from './index'
import { Module, VuexModule } from 'vuex-module-decorators'
import gruvbox from '@/themes/srcery.json'

@Module({ dynamic: true, store, name: 'settings' })
export default class SocketModule extends VuexModule {
  theme = gruvbox
  iconFont = 'fa'
  iconMapping = {
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
  moduleIcons = {
    Spotify: ''
  }
}
