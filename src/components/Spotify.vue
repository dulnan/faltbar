<template>
  <div class="spotify">
    <div class="icon"><i class="fab fa-spotify"></i></div>
    <div class="controls">
      <div class="icon" @click="send('prev')">
        <i class="fab fa-step-backward"></i>
      </div>
      <div class="icon" @click="togglePlayback">
        <i class="fab" :class="isPlaying ? 'fa-pause' : 'fa-play'"></i>
      </div>
      <div class="icon" @click="send('next')">
        <i class="fab fa-step-forward"></i>
      </div>
    </div>
    <div>{{ albumArtist.join(', ') }}</div>
    <div>-</div>
    <div>{{ title }}</div>
  </div>
</template>

<script>
import Socket from '@/service/socket'

export default {
  name: 'Workspaces',
  data() {
    return {
      isPlaying: '',
      trackID: '',
      length: '',
      artUrl: '',
      album: '',
      albumArtist: [],
      autoRating: '',
      discNumber: '',
      title: '',
      trackNumber: '',
      url: '',
      canGoNext: false,
      canGoPrevious: false,
      canPlay: false,
      canPause: false,
      canSeek: false,
      canControl: false
    }
  },

  mounted() {
    Socket.on('spotify_update', (data) => {
      Object.keys(data).forEach((key) => {
        this[key] = data[key]
      })
    })
  },

  methods: {
    send(command) {
      Socket.send('spotify_' + command)
    },
    togglePlayback() {
      if (this.isPlaying) {
        Socket.send('spotify_pause')
      } else {
        Socket.send('spotify_play')
      }
    }
  }
}
</script>

<style scoped lang="scss">
.spotify {
  display: flex;
  align-items: center;
  font-weight: 700;
  > .icon {
    color: var(--color2);
  }
  .controls {
    display: flex;
    font-size: 10px;
    width: 3rem;
    justify-content: space-between;
  }
  > div {
    &:not(:first-child) {
      margin-left: 0.5em;
    }
  }
}
</style>
