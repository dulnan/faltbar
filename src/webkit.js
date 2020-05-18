if (!window.webkit) {
  window.webkit = {
    messageHandlers: {
      faltbar: {
        postMessage(msg) {
          console.log('postMessage to handler faltbar: ' + msg)
        }
      }
    }
  }
}
