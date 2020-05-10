import EventEmitter from 'eventemitter3'

class Socket extends EventEmitter {
  private socket: WebSocket

  constructor(url: string) {
    super()
    this.socket = new WebSocket(url)
    this.socket.onmessage = this.receive.bind(this)
  }

  receive(message: MessageEvent) {
    const { event, data, namespace } = JSON.parse(message.data)
    this.emit(event, { namespace, data })
  }

  send(namespace: string, event: string, data: object | string) {
    const message = JSON.stringify({
      namespace,
      event,
      data
    })

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
