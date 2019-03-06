#include "openalsoftaudioengine.h"

OpenAlSoftAudioEngine::OpenAlSoftAudioEngine()
{
    //Initialize sound setup variables to point to nullptr
    gAudioDevice = nullptr;
    alContext = nullptr;

    //initialize listener position
    listener_position_vector.resize(3);

    //initialize listener orientation
    listener_orientation_vector.resize(6);
    OpenAlSoftAudioEngine::initOpenALSoft();

    //clear testHRTF Results string
    testHRTF_Results.clear();
    loadSound_Results.clear();
}

OpenAlSoftAudioEngine::~OpenAlSoftAudioEngine()
{
    OpenAlSoftAudioEngine::close_openALSoft();
}

bool OpenAlSoftAudioEngine::initOpenALSoft()
{
    //function to initialize openal soft

    //use default audio device
    gAudioDevice = alcOpenDevice(NULL);
    if(gAudioDevice == NULL)
    {
        std::cout << "OpenAL Soft was unable to initialize! \n";
        std::cout << "Unable to initialize default audio device! \n";
        return false;
    }

    //create context
    alContext = alcCreateContext(gAudioDevice, NULL);
    if(alContext == NULL)
    {
        std::cout << "OpenAL Soft was unable to initialize! \n";
        std::cout << "Unable to initialize OpenAL context! \n";
        return false;
    }
    else{alcMakeContextCurrent(alContext);}

    /* Check if an error occured, and clean up if so. */
    ALenum err; //variable for error flag
    err = alGetError();
    if(err != AL_NO_ERROR)
    {
        //fprintf(stderr, "OpenAL Error: %s\n", alGetString(err));
        std::cout << "OpenAL Soft was unable to initialize! \n";
        std::cout << "OpenAL Error in initializing OpenAL Soft: ";
        std::cout << alGetString(err);
        std::cout << "\n";
        return false;
    }

    //define listener, what is hearing the sound, with initial values

    //Initialize Listener position
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);//is at the origin
    alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);//is not moving in 3d space

    //Set Listener orientation
    float vec[6];
    //set to just facing the screen

    //set where head is facing
    vec[0] = 0.0f; //forward vector x value
    vec[1] = 0.0f; //forward vector y value
    vec[2] = -1.0f; //forward vector z value
    //set where top of head surface vector
    vec[3] = 0.0f; //up vector x value
    vec[4] = 1.0f; //up vector y value
    vec[5] = 0.0f; //up vector z value

    //set current listener orientation
    alListenerfv(AL_ORIENTATION, vec);

    std::cout << " Open AL Soft Initialized! \n";
    return true;
}

void OpenAlSoftAudioEngine::close_openALSoft()
{
    alcDestroyContext(alContext);	//delete context
    alcCloseDevice(gAudioDevice);	//close device
}

//Listener Position Functions

void OpenAlSoftAudioEngine::setListenerPositionX(float x)
{
    //if x is different from listener position x
    if(listener_position_vector[POSITION_INDEX::X] != x)
    {
        listener_position_vector[POSITION_INDEX::X] = x; //assign z to listener position z
        alListener3f(AL_POSITION, listener_position_vector[POSITION_INDEX::X], listener_position_vector[POSITION_INDEX::Y], listener_position_vector[POSITION_INDEX::Z]);//change OpenAL Soft internal listener position
    }
}

float OpenAlSoftAudioEngine::getListenerPositionX(){return listener_position_vector[POSITION_INDEX::X];}

void OpenAlSoftAudioEngine::setListenerPositionY(float y)
{
    //if y is different from listener position y
    if(listener_position_vector[POSITION_INDEX::Y] != y)
    {
        listener_position_vector[POSITION_INDEX::Y] = y; //assign z to listener position y
        alListener3f(AL_POSITION, listener_position_vector[POSITION_INDEX::X], listener_position_vector[POSITION_INDEX::Y], listener_position_vector[POSITION_INDEX::Z]);//change OpenAL Soft internal listener position
    }
}

float OpenAlSoftAudioEngine::getListenerPositionY(){return listener_position_vector[POSITION_INDEX::Y];}

void OpenAlSoftAudioEngine::setListenerPositionZ(float z)
{
    //if z is different from listener position z
    if(listener_position_vector[POSITION_INDEX::Z] != z)
    {
        listener_position_vector[POSITION_INDEX::Z] = z; //assign z to listener position z
        alListener3f(AL_POSITION, listener_position_vector[POSITION_INDEX::X], listener_position_vector[POSITION_INDEX::Y], listener_position_vector[POSITION_INDEX::Z]);//change OpenAL Soft internal listener position
    }
}

float OpenAlSoftAudioEngine::getListenerPositionZ(){return listener_position_vector[POSITION_INDEX::Z];}

//Listener Orientation Functions

void OpenAlSoftAudioEngine::setListenerForwardX(float x)
{
    //if x is different from listener Forward x
    if(listener_orientation_vector[ORIENTATION_INDEX::FORWARD_X] != x)
    {
        listener_orientation_vector[ORIENTATION_INDEX::FORWARD_X] = x;
        alListenerfv(AL_ORIENTATION, listener_orientation_vector.data());//change OpenAL Soft internal listener orientation
    }
}

float OpenAlSoftAudioEngine::getListenerForwardX(){return listener_orientation_vector[ORIENTATION_INDEX::FORWARD_X];}

void OpenAlSoftAudioEngine::setListenerForwardY(float y)
{
    //if y is different from listener Forward x
    if(listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Y] != y)
    {
        listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Y] = y;
        alListenerfv(AL_ORIENTATION, listener_orientation_vector.data());//change OpenAL Soft internal listener orientation
    }
}

float OpenAlSoftAudioEngine::getListenerForwardY(){return listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Y];}

void OpenAlSoftAudioEngine::setListenerForwardZ(float z)
{
    //if z is different from listener Forward z
    if(listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Z] != z)
    {
        listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Z] = z;
        alListenerfv(AL_ORIENTATION, listener_orientation_vector.data());//change OpenAL Soft internal listener orientation
    }
}

float OpenAlSoftAudioEngine::getListenerForwardZ(){return listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Z];}

void OpenAlSoftAudioEngine::setListenerUpX(float x)
{
    //if x is different from listener Forward x
    if(listener_orientation_vector[ORIENTATION_INDEX::UP_X] != x)
    {
        listener_orientation_vector[ORIENTATION_INDEX::UP_X] = x;
        alListenerfv(AL_ORIENTATION, listener_orientation_vector.data());//change OpenAL Soft internal listener orientation
    }
}

float OpenAlSoftAudioEngine::getListenerUpX(){return listener_orientation_vector[ORIENTATION_INDEX::UP_X];}

void OpenAlSoftAudioEngine::setListenerUpY(float y)
{
    //if y is different from listener Forward x
    if(listener_orientation_vector[ORIENTATION_INDEX::UP_Y] != y)
    {
        listener_orientation_vector[ORIENTATION_INDEX::UP_Y] = y;
        alListenerfv(AL_ORIENTATION, listener_orientation_vector.data());//change OpenAL Soft internal listener orientation
    }
}

float OpenAlSoftAudioEngine::getListenerUpY(){return listener_orientation_vector[ORIENTATION_INDEX::UP_Y];}

void OpenAlSoftAudioEngine::setListenerUpZ(float z)
{
    //if z is different from listener Forward z
    if(listener_orientation_vector[ORIENTATION_INDEX::UP_Z] != z)
    {
        listener_orientation_vector[ORIENTATION_INDEX::UP_Z] = z;
        alListenerfv(AL_ORIENTATION, listener_orientation_vector.data());//change OpenAL Soft internal listener orientation
    }
}

float OpenAlSoftAudioEngine::getListenerUpZ(){return listener_orientation_vector[ORIENTATION_INDEX::UP_Z];}

//HRTF
//define functions for hrtf
static LPALCGETSTRINGISOFT alcGetStringiSOFT;
static LPALCRESETDEVICESOFT alcResetDeviceSOFT;


void OpenAlSoftAudioEngine::testHRTF()
{

    //call after initOpenALSoft

    ALCint hrtf_state; //state of hrtf, enabled or disabled
    ALCint num_hrtf; //variable for number of hrtf avaiable

    /* Check for HRTF support. */

    if(!alcIsExtensionPresent(gAudioDevice, "ALC_SOFT_HRTF"))
    {
        //fprintf(stderr, "Error: ALC_SOFT_HRTF not supported\n");
        testHRTF_Results.append("Error: ALC_SOFT_HRTF not supported! \n");
    }
    else
    {
        testHRTF_Results.append(" ALC_SOFT_HRTF is supported! \n");

        /* Define a macro to help load the function pointers. */
        #define LOAD_PROC_alcGetStringiSOFT(d, x)  ((x) = (LPALCGETSTRINGISOFT)alcGetProcAddress((d), #x))
            LOAD_PROC_alcGetStringiSOFT(gAudioDevice, alcGetStringiSOFT);
        #undef LOAD_PROC__alcGetStringiSOFT

        #define LOAD_PROC_alcResetDeviceSOFT(d, x)  ((x) = (LPALCRESETDEVICESOFT)alcGetProcAddress((d), #x))
            LOAD_PROC_alcResetDeviceSOFT(gAudioDevice, alcResetDeviceSOFT);
        #undef LOAD_PROC_alcResetDeviceSOFT

        /* Check for the AL_EXT_STEREO_ANGLES extension to be able to also rotate
         * stereo sources.
         */
        ALboolean has_angle_ext = alIsExtensionPresent("AL_EXT_STEREO_ANGLES");

        //printf("AL_EXT_STEREO_ANGLES%s found\n", has_angle_ext?"":" not");
        if(has_angle_ext )
        {
            testHRTF_Results.append("AL_EXT_STEREO_ANGLES support found. Stereo sources can be rotated. \n");
        }
        else
        {
            testHRTF_Results.append("AL_EXT_STEREO_ANGLES support not found. Stereo sources cannot be rotated. \n");
        }


        /* Enumerate available HRTFs, and reset the device using one. */
        alcGetIntegerv(gAudioDevice, ALC_NUM_HRTF_SPECIFIERS_SOFT, 1, &num_hrtf);
        if(!num_hrtf)
        {
            testHRTF_Results.append("No HRTFs found. \n");
        }
        else
        {
            ALCint i; //iterator

            testHRTF_Results.append("Available HRTFs:\n");
            for(i = 0;i < num_hrtf;i++)
            {
                const ALCchar *name = alcGetStringiSOFT(gAudioDevice, ALC_HRTF_SPECIFIER_SOFT, i);

                testHRTF_Results.append(name);
                testHRTF_Results.append(" ");
                testHRTF_Results.append(std::to_string(i));
                testHRTF_Results.append(" \n");
            }
        }

        /* Check if HRTF is enabled, and show which is being used. */
        alcGetIntegerv(gAudioDevice, ALC_HRTF_SOFT, 1, &hrtf_state);
        if(!hrtf_state)
        {
            
            testHRTF_Results.append("HRTF not enabled!\n");
        }
        else
        {
            const ALchar *name = alcGetString(gAudioDevice, ALC_HRTF_SPECIFIER_SOFT);
            
            testHRTF_Results.append("HRTF enabled, using ");
            testHRTF_Results.append(name);
            testHRTF_Results.append("\n");
        }
    }
}

std::string OpenAlSoftAudioEngine::getHRTFTestResult(){return testHRTF_Results;}

void OpenAlSoftAudioEngine::clear_testHRTFResults(){testHRTF_Results.clear();}




void OpenAlSoftAudioEngine::loadSound(ALuint* buffer, const std::string& filename)
{
    /*Code modified from Chris Robinson's OpenAL-Soft example for loading sound file.*/
    
    ALuint tempBuffer;
    ALenum err; //variable for error flag
    ALenum format; //ALenum variable for format of sound sample e.g. 8-bit 16-bit
    ALsizei slen; //Size in bytes of the buffer data.
    ALsizei frequency; //Sample rate of the buffer data

	
	//libsndfile code below adapted from sfprocess.c of libsndfile example on github.
	
	//libsndfile file handle for input file
	SNDFILE	*infile;

	/* A pointer to an SF_INFO struct is passed to sf_open.
	** On read, the library fills this struct with information about the file.
	*/
	SF_INFO	sfinfo;
	const char	*infilename = filename.c_str();

	/* The SF_INFO struct must be initialized before using it.
	*/
	memset (&sfinfo, 0, sizeof (sfinfo)) ;

	/* Here's where we open the input file. We pass sf_open the file name and
	** a pointer to an SF_INFO struct.
	** On successful open, sf_open returns a SNDFILE* pointer which is used
	** for all subsequent operations on that file.
	** If an error occurs during sf_open, the function returns a NULL pointer.
	**
	*/

	if (! (infile = sf_open (infilename, SFM_READ, &sfinfo)))
	{
		/* Open failed so print an error message. */
		loadSound_Results.append("Not able to open input file "); loadSound_Results.append(infilename); loadSound_Results.append(".\n");
		/* Print the error message from libsndfile. */
		loadSound_Results.append(sf_strerror (NULL)) ;
		return;
	 }

	if (sfinfo.channels > MAX_CHANNELS)
	{	loadSound_Results.append("Not able to process more than "); 
		loadSound_Results.append(std::to_string(MAX_CHANNELS)); 
		loadSound_Results.append("%d channels.\n");
		return;
	}

	/* Get the sound format, and figure out the OpenAL format */

	//check for number of channels
	//if audio sample has only 1 channel
	if(sfinfo.channels == 1)
	{
		//if audio sample format is 8-bit, set ALenum format variable to mono 8-bit
		if( (sfinfo.format & SF_FORMAT_SUBMASK) == SF_FORMAT_PCM_S8 ||
				(sfinfo.format & SF_FORMAT_SUBMASK) == SF_FORMAT_PCM_U8){format = AL_FORMAT_MONO8;}
		//if audio sample format is 16-bit, set ALenum format variable to mono 8-bit
		else if( (sfinfo.format & SF_FORMAT_SUBMASK) == SF_FORMAT_PCM_16){format = AL_FORMAT_MONO16;}
		//else notify that sample format is unsupported
		else
		{
			loadSound_Results.append("Unsupported sample format for mono. Must be 8-bit or 16-bit");
			return;
		}

	}
	//else if audio sample has 2 channels
	else if(sfinfo.channels == 2)
	{
		//if audio sample format is 8-bit, set ALenum format variable to stereo 8-bit
		if( (sfinfo.format & SF_FORMAT_SUBMASK) == SF_FORMAT_PCM_S8 ||
			(sfinfo.format & SF_FORMAT_SUBMASK) == SF_FORMAT_PCM_U8){format = AL_FORMAT_STEREO8; }
		//if audio sample format is 16-bit, set ALenum format variable to stereo 8-bit
		else if( (sfinfo.format & SF_FORMAT_SUBMASK) == SF_FORMAT_PCM_16){format = AL_FORMAT_STEREO16;}
		//else notify that sample format is unsupported
		else
		{
			loadSound_Results.append("Unsupported sample format for stereo. Must be 8-bit or 16-bit.");
			return;
		}

	}
	//else notify that channel count is unsupported
	else
	{
		loadSound_Results.append("Unsupported channel count. Must be 1 or 2 channels.\n");
		return;
	}

	/* Decode the whole audio stream to a buffer. */

	frequency = sfinfo.samplerate;
	std::cout << "Sample Rate: " << frequency << "\n";

	//setup data for buffer
	std::vector<uint16_t> data;
	std::vector<int16_t> read_buf(BUFFER_LEN);
	size_t read_size = 0;
	while((read_size = sf_read_short(infile, read_buf.data(), read_buf.size())) != 0)
	{
		data.insert(data.end(), read_buf.begin(), read_buf.begin() + read_size);
	}

	slen = data.size() * sizeof(uint16_t); //get size of data in bytes

	std::cout << "Size of data in bytes: " << slen << "\n";
	//if sample buffer is null or size of buffer data is zero, notify of error
	if(slen == 0)
	{
		loadSound_Results.append("Failed to read audio from file.\n");
		return;
	}

	double seconds = (1.0 * sfinfo.frames) / sfinfo.samplerate ;
	std::cout << "Duration of sound:" << seconds << "s. \n";

	/* Buffer the audio data into a new buffer object, then free the data and
	 * close the file. */
	tempBuffer = 0; //initialize temp buffer
	alGenBuffers(1, &tempBuffer);//request 1 buffer
	//set buffer data
	//alBufferData(buffer, format, data, slen, frequency);
	alBufferData(tempBuffer, format,&data.front(), data.size() * sizeof(uint16_t), sfinfo.samplerate);

	/* Check if an error occured, and clean up if so. */
	err = alGetError();
	if(err != AL_NO_ERROR)
	{
		//fprintf(stderr, "OpenAL Error: %s\n", alGetString(err));
		loadSound_Results.append("OpenAL Error in loading sound: ");
		loadSound_Results.append(alGetString(err));
		loadSound_Results.append("\n");
		if(tempBuffer && alIsBuffer(tempBuffer)){alDeleteBuffers(1, &tempBuffer);}
		return;
	}
	loadSound_Results.append("Loaded "); loadSound_Results.append(filename); loadSound_Results.append(" successfully! \n");
	*buffer = tempBuffer; //assign temp buffer to buffer

	/* Close input files. */
	sf_close (infile);
       
}





std::string OpenAlSoftAudioEngine::getLoadSoundResult(){return loadSound_Results;}

void OpenAlSoftAudioEngine::clear_LoadSoundResults(){loadSound_Results.clear();}


void OpenAlSoftAudioEngine::createSource(ALuint* buffer,ALuint* source)
{
	/* Create the source to play the sound with. */
	
	//if buffer is defined
	if(*buffer != 0)
	{
		alGenSources(1, source);
		alSourcei(*source, AL_SOURCE_RELATIVE, AL_TRUE);
		alSource3f(*source, AL_POSITION, 0.0f, 0.0f, -1.0f);
		alSourcei(*source, AL_BUFFER, *buffer);
		assert(alGetError()==AL_NO_ERROR && "Failed to setup sound source.");
	}
}

void al_nssleep(unsigned long nsec)
{
    struct timespec ts, rem;
    ts.tv_sec = nsec / 1000000000ul;
    ts.tv_nsec = nsec % 1000000000ul;
    while(nanosleep(&ts, &rem) == -1 && errno == EINTR)
        ts = rem;
}

void OpenAlSoftAudioEngine::playSound(ALuint* source)
{
	ALdouble angle;
    ALenum state;
    ALboolean has_angle_ext;
    
    /* Play the sound until it finishes. */
    angle = 0.0;
    alSourcePlay(*source);
    do {
        al_nssleep(10000000);

        /* Rotate the source around the listener by about 1/4 cycle per second,
         * and keep it within -pi...+pi.
         */
        angle += 0.01 * M_PI * 0.5;
        if(angle > M_PI)
            angle -= M_PI*2.0;

        /* This only rotates mono sounds. */
        alSource3f(*source, AL_POSITION, (ALfloat)sin(angle), 0.0f, -(ALfloat)cos(angle));

        if(has_angle_ext)
        {
            /* This rotates stereo sounds with the AL_EXT_STEREO_ANGLES
             * extension. Angles are specified counter-clockwise in radians.
             */
            ALfloat angles[2] = { (ALfloat)(M_PI/6.0 - angle), (ALfloat)(-M_PI/6.0 - angle) };
            alSourcefv(*source, AL_STEREO_ANGLES, angles);
        }

        alGetSourcei(*source, AL_SOURCE_STATE, &state);
    } while(alGetError() == AL_NO_ERROR && state == AL_PLAYING);

}

void OpenAlSoftAudioEngine::error_check(std::string location_str)
{
    /* Check if an error occured, and clean up if so. */
    test_error_flag = alGetError();
    if(test_error_flag != AL_NO_ERROR)
    {
        std::cout << "Error found in " << location_str << ": " << alGetString(test_error_flag) << "\n";
        return;
    }
}
