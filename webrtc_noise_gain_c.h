#ifndef _WRTC_NOISE_GAIN_C_S_
#define _WRTC_NOISE_GAIN_C_S_

#include<stdint.h>

#ifdef __cplusplus
  #define EXPORT_C extern "C"
#else
  #define EXPORT_C
#endif

// C Types
typedef enum {
    NO_SPEECH = 0,
    SPEECH = 1,
} AudioProcessResult_t;

typedef void * AudioProcessor_t;

// Protopypes
EXPORT_C  AudioProcessor_t AudioProcessorCreate(int auto_gain, int noise_supression, float preamp,int vad); 
EXPORT_C  void AudioProcessorDelete(AudioProcessor_t a);
EXPORT_C  AudioProcessResult_t AudioProcessorProcess10ms(AudioProcessor_t a,int16_t *samples,int16_t *samples_out);
EXPORT_C  void AudioProcessorReset(AudioProcessor_t a); 

#endif
