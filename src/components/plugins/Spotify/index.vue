<template>
  <div class="spotify">
    <div>{{ albumArtist.join(', ') }}</div>
    <div>-</div>
    <div>{{ title }}</div>
    <div class="controls">
      <div class="pill" @click="send('prev')">
        <f-icon icon="fab fa-step-backward" />
      </div>
      <div class="pill" @click="togglePlayback">
        <f-icon :icon="'fab fa-' + (isPlaying ? 'pause' : 'play')" />
      </div>
      <div class="pill" @click="send('next')">
        <f-icon icon="fab fa-step-forward" />
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'Spotify',

  faltbar: {
    namespaces: {
      spotify: true
    }
  },

  computed: {},

  methods: {
    send(command) {
      this.$socket.send('spotify', command)
    },
    togglePlayback() {
      if (this.isPlaying) {
        this.send('pause')
      } else {
        this.send('play')
      }
    }
  }
}
</script>

<style scoped lang="scss">
.spotify {
  display: flex;
  color: var(--cursor);
  align-items: center;
  flex: 0 0 auto;
  .controls {
    display: flex;
    justify-content: space-between;
    .pill {
      background: var(--cursor);
      color: var(--background);
      opacity: 0.5;
      width: 1.5em;
      cursor: pointer;
      &:hover {
        opacity: 1;
      }
      text-align: center;
      justify-content: center;
      &:not(:first-child):not(:last-child) {
        margin: 0 0.25em;
      }
      .icon i {
        font-size: 1.25em;
      }
    }
  }
  > div {
    &:not(:first-child) {
      margin-left: 0.5em;
    }
  }
}
</style>
