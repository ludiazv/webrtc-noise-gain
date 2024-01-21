#include <webrtc_noise_gain_c.h>
#include <webrtc-audio-processing-1/modules/audio_processing/include/audio_processing.h>


// ----------------------------------------------------------------------------
// Private impl

class AudioProcessor {
private:
  webrtc::AudioProcessing *apm = NULL;
  webrtc::AudioProcessing::Config audio_config;
  webrtc::StreamConfig stream_config;

public:
  AudioProcessor(int auto_gain, int noise_suppression,float preamp,int vad);
  ~AudioProcessor();

  AudioProcessResult_t Process10ms(int16_t *samples,int16_t *samples_out);
  void Reset();
};

// auto_gain: 0 = disabled, max 31
// noise_suppression: 0 = disabled, max 4
AudioProcessor::AudioProcessor(int auto_gain, int noise_suppression,float preamp,int vad)
    : stream_config(16000, 1, false) {
  this->apm = webrtc::AudioProcessingBuilder().Create();

  this->audio_config.echo_canceller.enabled = false;

  if (preamp != 0 ) {
    this->audio_config.pre_amplifier.enabled = true;
    this->audio_config.pre_amplifier.fixed_gain_factor = preamp;
  }

  if (auto_gain > 0) {
    this->audio_config.gain_controller1.enabled = true;
    this->audio_config.gain_controller1.target_level_dbfs = auto_gain;
    this->audio_config.gain_controller2.enabled = true;
  }

  this->audio_config.high_pass_filter.enabled = true;
  this->audio_config.voice_detection.enabled = (vad != 0) ? true : false;

  if (noise_suppression > 0) {
    this->audio_config.noise_suppression.enabled = true;
    if (noise_suppression == 1) {
      this->audio_config.noise_suppression.level =
          webrtc::AudioProcessing::Config::NoiseSuppression::Level::kLow;
    } else if (noise_suppression == 2) {
      this->audio_config.noise_suppression.level =
          webrtc::AudioProcessing::Config::NoiseSuppression::Level::kModerate;
    } else if (noise_suppression == 3) {
      this->audio_config.noise_suppression.level =
          webrtc::AudioProcessing::Config::NoiseSuppression::Level::kHigh;
    } else if (noise_suppression >= 4) {
      this->audio_config.noise_suppression.level =
          webrtc::AudioProcessing::Config::NoiseSuppression::Level::kVeryHigh;
    }
  }

  this->apm->ApplyConfig(audio_config);
}

AudioProcessResult_t AudioProcessor::Process10ms(int16_t *samples,int16_t *samples_out) {

  this->apm->ProcessStream(samples,this->stream_config, this->stream_config,samples_out);
  return this->apm->GetStatistics().voice_detected.value_or(false) ? SPEECH : NO_SPEECH; 

}

AudioProcessor::~AudioProcessor() { delete this->apm; }
AudioProcessor::Reset()           { this->apm->Initialize(); }

// ----------------------------------------------------------------------------
// PUBLIC C API WRAPPER
//

AudioProcessor_t AudioProcessorCreate(int auto_gain, int noise_supression,float preamp,int vad) {
  
 try {
  auto ap=new AudioProcessor(auto_gain,noise_supression,preamp,vad);
  return (AudioProcessor_t)ap;
 } catch(...) {
    return NULL;
 }

}
void AudioProcessorReset(AudioProcessor_t a) {
  if(a) reinterpret_cast<AudioProcessor *>(a)->Reset();   
}

void AudioProcessorDelete(AudioProcessor_t a) {
  if(a) delete reinterpret_cast<AudioProcessor *>(a);  
}

AudioProcessResult_t AudioProcessorProcess10ms(AudioProcessor_t a,int16_t *samples,int16_t *samples_out) {
  return reinterpret_cast<AudioProcessor *>(a)->Process10ms(samples,samples_out);
}
