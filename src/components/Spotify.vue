<template>
  <div class="spotify">
    <div>{{ albumArtist.join(', ') }}</div>
    <div>-</div>
    <div>{{ title }}</div>
    <div class="controls">
      <div class="pill" @click="send('prev')">
        <div class="icon">
          <i class="fab fa-step-backward"></i>
        </div>
      </div>
      <div class="pill" @click="togglePlayback">
        <div class="icon">
          <i class="fab" :class="isPlaying ? 'fa-pause' : 'fa-play'"></i>
        </div>
      </div>
      <div class="pill" @click="send('next')">
        <div class="icon">
          <i class="fab fa-step-forward"></i>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import Socket from '@/service/socket'

export default {
  name: 'Spotify',

  faltbar: {
    icon: {
      fa: 'fab fa-spotify'
    }
  },

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
