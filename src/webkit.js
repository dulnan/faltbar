// postMessage: function(msg) {
// }
//
const handlers = ['faltbar', 'faltbar_bar']

    const messageHandlers = handlers.reduce(
        (acc, item) => {
          acc[item] =
          {
            postMessage: function(msg) {
              console.log(`postMessage to handler ${item}: ${msg}`)
            }
          }

          return acc
        },
        {})

export const webkit = window.webkit || {
  messageHandlers
}

export const faltbarMonitors = window.faltbarMonitors || [
  {name: 'DP-1', x: 3120, y: 0, w: 1920, h: 1080}, {name: 'DP-0', x: 0, y: 0, w: 600, h: 960},
  {name: 'DP-2.2', x: 2520, y: 0, w: 600, h: 960}, {name: 'DP-2.3', x: 600, y: 0, w: 1920, h: 1080}
]
