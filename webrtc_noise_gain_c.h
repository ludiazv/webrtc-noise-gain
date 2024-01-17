#ifndef _WRTC_NOISE_GAIN_C_S_
#define _WRTC_NOISE_GAIN_C_S_

#include<stdint.h>

// C Types
typedef enum {
    NO_SPEECH,
    SPEECH,
} AudioProcessResult_t;

typedef void * AudioProcessor_t;

// Protopypes
extern "C" AudioProcessor_t AudioProcessorCreate(int auto_gain, int noise_supression, float preamp); 
extern "C" void AudioProcessorDelete(AudioProcessor_t a);
extern "C" AudioProcessResult_t AudioProcessorProcess10ms(AudioProcessor_t a,int16_t *samples,int16_t *samples_out);


#endif
