import EventEmitter from 'eventemitter3'

class Socket extends EventEmitter {
  constructor(url) {
    super()
    this.socket = new WebSocket(url)
    this.socket.onmessage = this.receive.bind(this)
  }

  receive(message) {
    const { event, data } = JSON.parse(message.data)
    this.emit(event, data)
  }

  send(event, data) {
    const message = JSON.stringify({ event, data })

    this.socket.send(message)
  }

  connect() {
    return new Promise((resolve) => {
      this.socket.onopen = function() {
        resolve()
      }
    })
  }
}

const instance = new Socket('ws://localhost:9000')

export default instance
